#include <string>
#include <sqlite3.h>

class SqliteDBH {
	public:
		SqliteDBH(std::string);
		void open();
	private:
		sqlite3* db;
		std::string filePath;
};


