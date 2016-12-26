#include "../catch.h"
#include <vector>
#include <string>
#include <iostream>
#include "../../database/Table.h"
#include "../../database/Column.h"

class TestTable : public Table {
	public:
		std::vector<Column> columns();
		bool autoincrement();
		std::string tableName();	
};

std::vector<Column> TestTable::columns() {
	std::vector<Column> columns;
	columns.push_back(Column("time", "INT"));
	columns.push_back(Column("test_text", "TEXT"));
	return columns;
}

bool TestTable::autoincrement() {
	return true;
}

std::string TestTable::tableName() {
	return "test_table";
}

TEST_CASE( "Test Create Sql", "[fileExists]" ) {
	TestTable table;
	INFO( "Table sql: " << table.createTableSql());
	CHECK("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY AUTOINCREMENT,time INT,test_text TEXT)" == table.createTableSql());
};
