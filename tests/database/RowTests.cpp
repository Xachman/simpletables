#include "../catch.h"
#include "../../database/Entry.h"
#include "../../database/Row.h"

TEST_CASE("Row Test", "[Rows]") {
	Entry cEntry1("first_name", "Tim");
	Entry cEntry2("last_name", "Dailey");
	Entry cEntry3("address", "123 Gay ST");

	Row row;

	row.add(cEntry1);
	row.add(cEntry2);
	row.add(cEntry3);

	REQUIRE(row.findEntry("first_name").getValue() ==  "Tim");
	REQUIRE(row.findEntry("last_name").getValue() ==  "Dailey");
	REQUIRE(row.findEntry("address").getValue() ==  "123 Gay ST");
}
