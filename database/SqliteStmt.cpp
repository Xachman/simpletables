#include "SqliteStmt.h"
#include <string>
#include <sqlite3.h>
#include <stdexcept>

SqliteStmt::SqliteStmt(sqlite3_stmt* stmt, sqlite3* db): stmt(stmt), db(db) {}


void SqliteStmt::bindText(int position, const std::string& text) {
	int rc;
	rc = sqlite3_bind_text(this->stmt, 2, text.c_str(), sizeof(text.c_str()), NULL);
	if(SQLITE_OK != rc) {
		throw "Can't prepare insert statment: " + std::string(sqlite3_errmsg(this->db));
	}
}

sqlite3_stmt* SqliteStmt::getStmt() {
    return this->stmt;	
}
