#include "catch.h"
#include "../SqliteDBH.h"
#include "../database/Table.h"
#include <vector>
#include <map>
#include <string>

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

TEST_CASE( "Test File Open that does not exist", "[open]" ) {
	SqliteDBH dbh("mocks/no-file.db");
	REQUIRE_THROWS(dbh.open());
};

TEST_CASE( "Test File Open", "[open]" ) {
	SqliteDBH dbh("tests/mocks/test.db");
	REQUIRE_NOTHROW(dbh.open());
	dbh.close();
};

TEST_CASE("Test Create table", "[execute]") {
	SqliteDBH dbh("tests/mocks/test.db");
	ClientsTable table;
	dbh.open();
	dbh.execute(table.createTableSql());
	REQUIRE(false);
	dbh.close();
};

TEST_CASE("Test Insert", "[execute]") {
	SqliteDBH dbh("tests/mocks/test.db");
	ClientsTable table;
	dbh.open();
	std::string sql = 	"INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
						"INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
						"INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');";
	std::vector<std::map<std::string,std::string> > rows =  dbh.execute(sql);
	for(int i = 0; i < rows.size(); i++) {
		INFO("Row Loop");
		std::map<std::string, std::string> rowMap;
		INFO(rowMap["first_name"]);
	}
	REQUIRE(false);
	dbh.close();
}

TEST_CASE("Test Select", "[execute]") {
	SqliteDBH dbh("tests/mocks/test.db");
	ClientsTable table;
	dbh.open();
	std::string sql = 	"SELECT * FROM clients_table;";
	std::vector<std::map<std::string,std::string> > rows =  dbh.execute(sql);
	for(int i = 0; i < rows.size(); i++) {
		INFO("Row Loop");
		std::map<std::string, std::string> rowMap;
		INFO(rowMap["first_name"]);
	}
	REQUIRE(false);
	dbh.close();
}
