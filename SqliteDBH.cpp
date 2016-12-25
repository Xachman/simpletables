#include <string>



SqliteDBH::SqliteDBH(std::string path) {
	this->dbFilePath = path;

}

void SqliteDBH::openFile() {
//	rc = sqlite3_open(this->dbFilePath, &db);
}
