#ifndef SQLITEDBH_H
#define SQLITEDBH_H
#include <string>
#include <map>
#include <vector>
#include <sqlite3.h>
#include "Row.h"
#include "SqliteStmt.h"

class SqliteDBH {
	public:
		SqliteDBH(std::string);
		void open();
		std::vector<Row>	execute(std::string sql);
		void close();
		SqliteStmt prepare(std::string);
		void bindText(int, const std::string&, sqlite3_stmt*);
		void executeStmt(SqliteStmt);
		sqlite3_int64 lastId();
	private:
		sqlite3* db;
		std::vector<Row> rows;
		std::string filePath;
		static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif
