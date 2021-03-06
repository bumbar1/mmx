#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <mmx/sqlite.hpp>

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

int main() {
	try {
		mmx::sqlite db;

		db.open("test.sqlite3", SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE);

		db.query("create table test(id int, c0 int, c1 int);");

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
