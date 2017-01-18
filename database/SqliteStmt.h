#ifndef SQLITESTMT_H
#define SQLITESTMT_H
#include <string>
#include <sqlite3.h>

class SqliteStmt {
	private:
		sqlite3_stmt* stmt;
		sqlite3* db;
	public:
		SqliteStmt(sqlite3_stmt*, sqlite3*);
		void bindText(int, const std::string&);
		sqlite3_stmt* getStmt();
};


#endif
