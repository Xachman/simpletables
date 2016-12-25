#include <string>
#include <vector>
#include "Table.h"
#include "Column.h"

std::string Table::createTableSql() {
	std::string sql;
	std::vector<Column> columns = this->columns();
	for(int i = 0; i < columns.size(); i++) {
		Column col = columns[i];
		sql += col.name()+" "+col.type();
		if((i+1) < columns.size()) {
			sql += ",";
		}
	}	
	return "CREATE TABLE IF NOT EXISTS "+this->tableName()+" (" +
		((this->autoincrement())? "id INTEGER PRIMARY KEY AUTOINCREMENT," : "" ) +
		sql+
		") ";
}
