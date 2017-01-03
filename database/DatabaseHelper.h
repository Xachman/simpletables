#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H
#include "Table.h"
#include "SqliteDBH.h"
#include "Row.h"
#include <vector>

class DatabaseHelper {
	private:
		std::string path;
		SqliteDBH dbh;
	public:
		DatabaseHelper(const std::string& file);
		void open();
		bool createTable(Table& table);
		Row getById(int id, Table& table);
		std::vector<Row> getAll(Table& table);
		std::string insert(Row&, Table&);
		void close();
};

#endif
