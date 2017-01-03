#ifndef CLIENTSMOCK_H
#define CLIENTSMOCK_H
#include <string>
#include <vector>

class ClientsTable : public Table {
	public:
		std::vector<Column> columns();
		bool autoincrement();
		std::string tableName();
};

#endif

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


