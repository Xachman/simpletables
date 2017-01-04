#include "ClientsTable.h"
#include "../../database/Column.h"
#include <vector>

std::vector<Column> ClientsTable::columns() {
	std::vector<Column> columns;
	columns.push_back(Column("first_name", "TEXT"));
	columns.push_back(Column("last_name", "TEXT"));
	columns.push_back(Column("address", "TEXT"));
	columns.push_back(Column("phone", "TEXT"));
	columns.push_back(Column("email", "TEXT"));
	return columns;
}

bool ClientsTable::autoincrement() {
	return true;
}

std::string ClientsTable::tableName() {
	return "clients_table";
}


