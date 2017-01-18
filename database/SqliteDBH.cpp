#include <string>
#include <sqlite3.h>
#include <vector>
#include <map>
#include "Row.h"
#include "Entry.h"
#include "SqliteDBH.h"
#include "../Util.h"
#include <stdexcept>

SqliteDBH::SqliteDBH(std::string path) {
	this->filePath = path;
}

void SqliteDBH::open() {
	int rc;
	if(Util::fileExist(this->filePath)) {
		rc = sqlite3_open(this->filePath.c_str(), &this->db);
		if( rc ){
			throw std::invalid_argument("Can't open database: "+std::string(sqlite3_errmsg(this->db)));
		}
	}else{
		throw std::invalid_argument("File not found");
	}
}

 std::vector<Row> SqliteDBH::execute(std::string sql) {
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_exec(this->db, sql.c_str(), this->callback, this, &zErrMsg);
	if( rc != SQLITE_OK ){
		throw std::invalid_argument( "SQL error: "+ std::string(zErrMsg));
		sqlite3_free(zErrMsg);
	}
	return this->rows;
}

SqliteStmt SqliteDBH::prepare(std::string sql) {
	sqlite3_stmt* stmt;	
	int rc;
	rc = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, NULL);
	if(SQLITE_OK != rc) {
		throw std::invalid_argument("Can't prepare insert statment: " + std::string(sqlite3_errmsg(db)));
	}
	return SqliteStmt(stmt, this->db);
}

int SqliteDBH::callback(void *data, int argc, char **argv, char **azColName){
	int i;
	Row row;
	SqliteDBH* dbhObj = reinterpret_cast<SqliteDBH*>(data);
	for(i=0; i<argc; i++){
	   		row.add(Entry(azColName[i], argv[i] ? argv[i] : "NULL")); 
	}
	dbhObj->rows.push_back(row);
	return 0;
}


void SqliteDBH::executeStmt(SqliteStmt stmt) {
	int rc;	
	rc = sqlite3_step(stmt.getStmt());
	sqlite3_finalize(stmt.getStmt());
	if(SQLITE_DONE != rc) {
		throw std::invalid_argument("Can't prepare insert statment: " + std::string(sqlite3_errmsg(this->db)));
	} 
}
sqlite3_int64 SqliteDBH::lastId() {
	return sqlite3_last_insert_rowid(db);
}
void SqliteDBH::close() {
	sqlite3_close(this->db);
}
