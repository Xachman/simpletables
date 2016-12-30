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
		dbh.execute(table.createTableSql());
		REQUIRE(false);
		dbh.close();
	}

	SECTION("Test Insert") {
		SqliteDBH dbh = TestSetup::setupDBH();
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

	SECTION("Test Select") {
		SqliteDBH dbh = TestSetup::setupDBH();
		std::string sql = 	"SELECT * FROM clients_table;";
		std::vector<std::map<std::string,std::string> > rows =  dbh.execute(sql);
		for(int i = 0; i < rows.size(); i++) {
			std::map<std::string, std::string> rowMap = rows[i];
			WARN(rowMap["first_name"]);
		}
		INFO(rows.size());
		dbh.execute("DROP TABLE clients_table");
		REQUIRE(false);
		dbh.close();
	}
}
