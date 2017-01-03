#include "../catch.h"
#include "../../database/Row.h"
#include "../../database/DatabaseHelper.h"
#include "../mocks/ClientsTable.h"

ClientsTable clientsTable;
TEST_CASE("Test Create Table", "[create]") {
	dbh DatabaseHelper("../mocks/test.db");
	dbh.createTable(clientsTable);
	REQUIRE(false);

}

TEST_CASE("Test insert", "[insert]") {
	dbh DatabaseHelper("../mocks/test.db");
	Row row;
	row.add(Entry("first_name", "tim"));
	dbh.insert(row, clientsTable);
	REQUIRE(false);
}

TEST_CASE("Test get all" , "[select]") {
	dbh DatabaseHelper("../mocks/test.db");
	dbh.getAll(clientsTable);
	REQUIRE(false);
}

