#include <string>
#include <sqlite3.h>

class SqliteDBH {
	public:
		SqliteDBH(std::string);
		void open();
		std::string execute(std::string sql);
		void close();
	private:
		sqlite3* db;
		std::string filePath;
		static int callback(void *data, int argc, char **argv, char **azColName);
};


