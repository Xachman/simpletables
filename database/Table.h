#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include "Column.h"

class Table {
	public:
		std::string createTableSql();
		virtual bool autoincrement() = 0;
		virtual std::string tableName() = 0;
		virtual std::vector<Column> columns() = 0;
};

#endif
