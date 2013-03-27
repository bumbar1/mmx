#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "src/sqlite.hpp"

struct test {
	int id, c0, c1;
	
	friend mmx::sqlite::statement& operator << (mmx::sqlite::statement& sql, const test& t) {
		sql << t.id << t.c0 << t.c1;
		return sql;
	}
	
	friend mmx::sqlite::statement& operator >> (mmx::sqlite::statement& sql, test& t) {
		sql >> t.id >> t.c0 >> t.c1;
		return sql;
	}
	
	friend std::ostream& operator << (std::ostream& os, const test& t) {
		os << t.id << ' ' << t.c0 << ' ' << t.c1;
		return os;
	}

};

struct movie {
	int id;
	int year;
	std::string title;
	std::string url;
	
	friend mmx::sqlite::statement& operator << (mmx::sqlite::statement& sql, const movie& m) {
        sql << m.id << m.title << m.year << m.url;
		return sql;
	}

	friend mmx::sqlite::statement& operator >> (mmx::sqlite::statement& sql, movie& m) {
        sql >> m.id >> m.title >> m.year >> m.url;		
		return sql;
	}
	
	friend std::ostream& operator << (std::ostream& os, const movie& m) {
		os << m.id << ' ' << m.title << " (" << m.year << ") @ " << m.url;
		return os;
	}
};

int main() {
	try {
		mmx::sqlite db;

		db.open("sqlite3.db", SQLITE_OPEN_READONLY);

		//auto results = db.query<movie>("select * from movies_movie limit 5,10");
		//auto results = db.query<int>("select year from movies_movie limit 0,5");
		auto results = db.query<test>("select * from test limit 0,5");

		std::cout << "size: " << results.size() << "\n";
		
		for (const auto& m : results)
			std::cout << m << "\n";

	} catch (const mmx::db_error& e) {
		std::cout << e.what() << "\n";
	} catch (...) {
		std::cout << "serious error?\n";
	}

	return 0;
}
