#include "catch.h"
#include "../SqliteDBH.h"
#include "../database/Table.h"

class ClientsTable : public Table {
	public:
		std::vector<Column> columns();
		bool autoincrement();
		std::string tableName();
};



std::vector<Column> ClientsTable::columns() {
	std::vector<Column> columns;
	columns.push_back(Column("time", "INT"));
	columns.push_back(Column("test_text", "TEXT"));
	return columns;
}

bool ClientsTable::autoincrement() {
	return true;
}

std::string ClientsTable::tableName() {
	return "test_table";
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
	CHECK( dbh.execute(table.createTableSql()) ==  "true");
	dbh.close();
};
