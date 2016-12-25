#include <string>
#include <sqlite3.h>
#include "SqliteDBH.h"
#include "Util.h"


SqliteDBH::SqliteDBH(std::string path) {
	this->filePath = path;
}

void SqliteDBH::open() {
	if(Util::fileExist(this->filePath)) {
		char *zErrMsg =0;
		int rc;
	}else{

	}
}
