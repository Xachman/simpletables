#include <string>
#include <map>
#include <vector>
#include <sqlite3.h>

class SqliteDBH {
	public:
		SqliteDBH(std::string);
		void open();
		std::vector<std::map<std::string,std::string> >	execute(std::string sql);
		void close();
	private:
		sqlite3* db;
		std::vector<std::map<std::string,std::string> > rows;
		std::string filePath;
		static int callback(void *data, int argc, char **argv, char **azColName);
};


