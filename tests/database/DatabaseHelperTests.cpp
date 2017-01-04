#include "../catch.h"
#include "../../database/Row.h"
#include "../../database/DatabaseHelper.h"
#include "../mocks/ClientsTable.h"

TEST_CASE("Test Table CRUD", "[crud]") {

	struct TestSetup {
		ClientsTable table;
		DatabaseHelper setupDBH() {
			DatabaseHelper dbh("tests/mocks/test.db");
			dbh.open();
			return dbh;
		}
	};
	TestSetup ts;
	SECTION("Create Table") {
		DatabaseHelper dbh = ts.setupDBH();
		dbh.createTable(ts.table);
		std::vector<Row> rows = dbh.query("SELECT name FROM sqlite_master WHERE type='table' AND name='"+ts.table.tableName()+"';");
		dbh.close();
		REQUIRE(rows[0].findEntry("name").getValue() == ts.table.tableName());
	}

	SECTION("Insert into table") {
		DatabaseHelper dbh = ts.setupDBH();
		Row row;
		row.add(Entry("first_name", "tim"));
		int id = dbh.insert(row, ts.table);
		Row returnRow  = dbh.getById(id, ts.table);
		dbh.close();
		WARN(id);
		REQUIRE(returnRow.findEntry("first_name").getValue() == "tim");
	}

	SECTION("Get all") {
		DatabaseHelper dbh = ts.setupDBH();
		dbh.getAll(ts.table);
		dbh.query("DROP TABLE IF EXISTS "+ts.table.tableName());
		dbh.close();
		REQUIRE(false);
	}



}

