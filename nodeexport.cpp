#include "database/DatabaseHelper.h"
#include "database/Row.h"
#include <iostream>
#include <vector>

#ifdef DATABASEHELPER_H
extern "C" {
#endif


class ClientsTable : public Table {
	public:
		std::vector<Column> columns();
		bool autoincrement();
		std::string tableName();
};


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
const char* simpletable_create_database(const char* path) {
		std::cout << "test" << std::endl;
		std::cout << path << std::endl;
		std::string stringPath(path);
		std::cout << stringPath << std::endl;
		DatabaseHelper dbh(stringPath);
		dbh.open();
		ClientsTable ct;
		dbh.createTable(ct);
		
		Row row;
		row.add(Entry("first_name", "Tim"));
		row.add(Entry("last_name", "Dailey"));
		row.add(Entry("address", "testaddy"));
		row.add(Entry("phone", "1234567890"));

		dbh.insert(row, ct);

		dbh.close();
		return "Insert";
}


const char* simpletable_get(const int id, const char* path) {
		std::string stringPath(path);
		DatabaseHelper dbh(stringPath);
		dbh.open();
		ClientsTable ct;
		
		Row row = dbh.getById(id, ct);
		
		dbh.close();
		std::string rString(row.findEntry("last_name").getValue());

		std::cout << "test" << std::endl;
		char* ca = new char[rString.size()+1];
		std::copy(rString.begin(), rString.end(), ca);
		ca[rString.size()] = '\0';
		return ca;

}


#ifdef DATABASEHELPER_H
}
#endif
