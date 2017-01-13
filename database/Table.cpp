#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Table.h"
#include "Column.h"

std::string Table::createTableSql() {
	std::stringstream sql;
	sql << "CREATE TABLE IF NOT EXISTS ";
	sql << this->tableName();
	sql << " (";
	sql << ((this->autoincrement())? "id INTEGER PRIMARY KEY AUTOINCREMENT," : "" );
	std::vector<Column> columns = this->columns();
	for(std::size_t i = 0; i < columns.size(); i++) {
		Column col = columns[i];
		sql << col.name() << " " << col.type();
		if((i+1) < columns.size()) {
			sql << ",";
		}
	}	
	sql << ")";
	return sql.str();
}
