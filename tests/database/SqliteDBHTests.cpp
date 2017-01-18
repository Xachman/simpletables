#include "../catch.h"
#include "../../database/SqliteDBH.h"
#include "../../database/SqliteStmt.h"
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

TEST_CASE("Test sql functions", "[execute]") {
	struct TestSetup {
		static SqliteDBH setupDBH(bool createTable) {
			SqliteDBH dbh("tests/mocks/test.db");
			dbh.open();
			dbh.execute("DROP TABLE IF EXISTS "+TestSetup::table().tableName());
			if(createTable) {
				dbh.execute(TestSetup::table().createTableSql());
			}
			return dbh;
		}
		static ClientsTable table() {
			ClientsTable table;
			return table;
		}
		static void cleanup(SqliteDBH dbh) {
			dbh.execute("DROP TABLE IF EXISTS "+TestSetup::table().tableName());
			dbh.close();
		}
	};
	SECTION("Test Create db") {
		SqliteDBH dbh = TestSetup::setupDBH(false);
		std::vector<Row> rows = dbh.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='"+TestSetup::table().tableName()+"'");
		for(int i = 0; i < rows.size(); i++) {
			Row row = rows[i];
			REQUIRE(row.findEntry("name").getValue() == "");
		}
		dbh.execute(TestSetup::table().createTableSql());
		rows = dbh.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='"+TestSetup::table().tableName()+"'");
		for(int i = 0; i < rows.size(); i++) {
			Row row = rows[i];
			REQUIRE(row.findEntry("name").getValue() == TestSetup::table().tableName());
		}
		TestSetup::cleanup(dbh);
	}
	SECTION("Test Prepared Insert") {
		SqliteDBH dbh = TestSetup::setupDBH(true);
		std::string prep = "INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ( ?, ?, ?, ?, ?)";
		SqliteStmt stmt = dbh.prepare(prep);

		stmt.bindText(1, "Tom");
		stmt.bindText(2, "Daily");
		stmt.bindText(3, "Gay Street");
		stmt.bindText(4, "1234567890");
		stmt.bindText(5, "firsttest@test.com");

		dbh.executeStmt(stmt);

		std::string sql = "SELECT last_insert_rowid();";

		std::vector<Row> rows = dbh.execute(sql);
	//TODO: this is the id (rows[0].findEntryIndex(0).getValue());
		std::string result;
		REQUIRE(result == "Tom");
		TestSetup::cleanup(dbh);
	}
	SECTION("Test Insert") {
		SqliteDBH dbh = TestSetup::setupDBH(true);
		std::string sql = 	"INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
							 "INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');"\
							 "INSERT INTO clients_table (first_name, last_name, address, phone, email) VALUES ('Tim', 'Dailey', 'Gay Street', '1234567789', 'test@test.com');";
		std::vector<Row> rows =  dbh.execute(sql);
		REQUIRE(rows.size() == 0);
		TestSetup::cleanup(dbh);
	}

	SECTION("Test Select") {
		SqliteDBH dbh = TestSetup::setupDBH(true);
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
		TestSetup::cleanup(dbh);
	}
}
