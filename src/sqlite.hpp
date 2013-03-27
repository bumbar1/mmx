#ifndef MMX_SQLITE_HPP
#define MMX_SQLITE_HPP 1

#include "config.hpp"

#include "ext/sqlite3.h"

#include <string>
#include <vector>
#include <exception>
#include <type_traits>

namespace mmx {

	class db_error : public std::exception {
	public:
		db_error(const std::string& what) : _what(what) {}

		const char* what() const noexcept { return _what.c_str(); }
	private:
		std::string _what;
	};

	/**
	 * todo? add begin, end transaction for large inserts
	 */
	class sqlite {
	public:
		MMX_CONSTEXPR sqlite() : _conn(nullptr) {}

		sqlite(const sqlite& copy) MMX_CLASS_DELETE;
		sqlite& operator = (const sqlite& copy) MMX_CLASS_DELETE;

		~sqlite() { close(); }
		
		/**
		 * valid modes:
		 * SQLITE_OPEN_READONLY
		 * SQLITE_OPEN_READWRITE
		 * SQLITE_OPEN_CREATE 
		 */
		void open(const std::string& db, int mode) {
			close();
			
			if (sqlite3_open_v2(db.c_str(), &_conn, mode, nullptr) != SQLITE_OK)
				throw mmx::db_error(sqlite3_errmsg(_conn));
			
			if (_conn == nullptr)
				throw mmx::db_error("unable to open: " + db);
		}

		void close() {
			if (_conn)
				sqlite3_close_v2(_conn);
			_conn = nullptr;
		}

		/**
		 * T needs to overload operators << and >> as friends :P
		 * 
		 * friend mmx::sqlite::statement& operator << (mmx::sqlite::statement& db, const T& m) {
         *   db << m.field0 << m.field1 << m.field2;
		 *   return db;
		 * }
		 *
		 * friend mmx::sqlite::statement& operator >> (mmx::sqlite::statement& db, T& m) {
         *   db >> m.field0 >> m.field1 >> m.field2;
		 *   return db;
		 * }
		 *
		 */		
		template <class T>
		std::vector<T> query(const std::string& statement) {
			std::vector<T> results;
			
			sqlite::statement sql(_conn);
			
			sql.prepare(statement);
			
			while (sql.has_next()) {
				T temp;
				
				sql >> temp;				
				results.push_back(temp);
				
				sql.reset();
			}
			
			return results;
		}

		/**
		 * for non select statements
		 */
		void query(const std::string& statement) {
			sqlite::statement sql(_conn);
			
			sql.prepare(statement);
		}

		/**
		 * Container needs to support ranged based for (ie, begin(), end(), operators ++ (post, pre), * (dereference)
		 *
		 * template <class Container>
		 * void query(const std::string& statement, Container& c) {
		 *     sqlite::statement sql(_conn);
		 *
		 *     sql.prepare(statement);
		 *
		 *     begin_transaction();
		 *
		 *     for (const auto& el : c)
		 *         sql << el;
		 *     end_transaction();
		 * }
		 */

		bool table_exists(const std::string& name) {
			try {
				auto r = query<std::string>("SELECT name FROM sqlite_master WHERE type='table' AND name='" + name + "'");
				
				// empty, no results
				if (!r.size())
					return false;
				
				return true;
			} catch (mmx::db_error& e) {
				return false;
			}
		}

		class statement {
		public:
			MMX_CONSTEXPR statement(sqlite3* db) : _db(db), _stmt(nullptr), _column(0) {}

			~statement() { finalize(); }

			template <class T>
			typename std::enable_if<
				std::is_integral<T>::value, statement
			>::type& operator << (T n) { sqlite3_bind_int(_stmt, _column++, n); return *this; }

			template <class T>
			typename std::enable_if<
				std::is_floating_point<T>::value, statement
			>::type& operator << (T n) { sqlite3_bind_double(_stmt, _column++, n); return *this; }

			statement& operator << (const std::string& str) {
				sqlite3_bind_text(_stmt, _column++, str.c_str(), str.size(), SQLITE_TRANSIENT);
				return *this;
			}

			template <class T>
			typename std::enable_if<
				std::is_integral<T>::value, statement
			>::type& operator >> (T& n) { n = sqlite3_column_int(_stmt, _column++); return *this; }

			template <class T>
			typename std::enable_if<
				std::is_floating_point<T>::value, statement
			>::type& operator >> (T& n) { n = sqlite3_column_double(_stmt, _column++); return *this; }

			statement& operator >> (std::string& str) {
				str = reinterpret_cast<const char*>(sqlite3_column_text(_stmt, _column++));
				return *this;
			}

			void prepare(const std::string& sql) {
				int code = sqlite3_prepare_v2(_db, sql.c_str(), sql.size(), &_stmt, nullptr);
				
				if (code != SQLITE_OK)
					throw mmx::db_error("error preparing statement (\"" + sql + "\"): " + sqlite3_errmsg(_db));
			}

			void reset() { _column = 0; }
			void finalize() { sqlite3_finalize(_stmt); }
			bool has_next() { return sqlite3_step(_stmt) != SQLITE_DONE; }

		private:
			sqlite3*      _db;
			sqlite3_stmt* _stmt;
			unsigned      _column;
		};

	private:
		sqlite3* _conn;
	};

}           // ~namespace mmx

#endif      // MMX_SQLITE_HPP
