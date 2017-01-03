#include "../catch.h"
#include "../../database/SqliteDBH.h"
#include "../../database/Table.h"
#include "../../database/Row.h"
#include <vector>
#include <map>
#include <string>
#include "../mocks/ClientsTable.h"

TEST_CASE( "Test File Open", "[fileOpen]" ) {

	SECTION("Test no file") {
		SqliteDBH dbh("mocks/no-file.db");
		REQUIRE_THROWS(dbh.open());
		dbh.close();
	}
	SECTION("Test File Exists") {
		SqliteDBH dbh("tests/mocks/test.db");
		REQUIRE_NOTHROW(dbh.open());
		dbh.close();
	}
};

ClientsTable table;
TEST_CASE("Test sql functions", "[execute]") {
	struct TestSetup {
		static SqliteDBH setupDBH() {
			SqliteDBH dbh("tests/mocks/test.db");
			dbh.open();
			return dbh;
		}
	};
	SECTION("Test Create db") {
		SqliteDBH dbh = TestSetup::setupDBH();
		std::vector<Row> rows = dbh.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='"+table.tableName()+"'");
		for(int i = 0; i < rows.size(); i++) {
			Row row = rows[i];
			REQUIRE(row.findEntry("name").getValue() == "");
		}
		dbh.execute(table.createTableSql());
		rows = dbh.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='"+table.tableName()+"'");
		for(int i = 0; i < rows.size(); i++) {
			Row row = rows[i];
			REQUIRE(row.findEntry("name").getValue() == table.tableName());
		}
		dbh.close();
	}

	SECTION("Test Insert") {
		SqliteDBH dbh = TestSetup::setupDBH();
		std::string sql = 	"INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
							 "INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
							 "INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');";
		std::vector<Row> rows =  dbh.execute(sql);
		REQUIRE(rows.size() == 0);
		dbh.close();
	}

	SECTION("Test Select") {
		SqliteDBH dbh = TestSetup::setupDBH();
		std::string sql = 	"SELECT * FROM clients_table;";
		std::vector<Row> rows =  dbh.execute(sql);
		for(int i = 0; i < rows.size(); i++) {
			Row row = rows[i];
			REQUIRE(row.findEntry("first_name").getValue() == "Tim");
			REQUIRE(row.findEntry("last_name").getValue() == "Dailey");
			REQUIRE(row.findEntry("address").getValue() == "Gay Street");
			REQUIRE(row.findEntry("phone").getValue() == "1234567789");
			REQUIRE(row.findEntry("email").getValue() == "test@test.com");
		}
		INFO(rows.size());
		dbh.execute("DROP TABLE "+table.tableName());
		dbh.close();
	}
}
