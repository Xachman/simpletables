#include <string>
#include <sqlite3.h>
#include "SqliteDBH.h"
#include "Util.h"
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

std::string SqliteDBH::execute(std::string sql) {
	char *zErrMsg = 0;
	int rc;
	const char* data;
	rc = sqlite3_exec(this->db, sql.c_str(), this->callback, (void*)data, &zErrMsg);
	if( rc != SQLITE_OK ){
		throw std::invalid_argument( "SQL error: "+ std::string(zErrMsg));
		sqlite3_free(zErrMsg);
	}
	return "true";
}

int SqliteDBH::callback(void *data, int argc, char **argv, char **azColName){
	int i;
//	fprintf("%s: ", (const char*)data);
	for(i=0; i<argc; i++){
//		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
//	printf("\n");
	return 0;
}


void SqliteDBH::close() {
	sqlite3_close(this->db);
}
