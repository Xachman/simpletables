#include <string>

class SqliteDBH {
	public:
		SqliteDBH(std::string);
	private:
		std::string dbFilePath;
		void openFile();
}


