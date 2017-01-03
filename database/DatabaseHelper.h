#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H
#include "Table.h"
#include "Row.h"
#include "Entry.h"
#include <vector>

class DatabaseHelper {
	public: 
		bool createTable(Table& table)
		Row getById(int id, Table& table);
		int id insert(std::vector<Entry>);
};

#endif
