#include "../catch.h"
#include "../../database/Entry.h"

TEST_CASE("Entry", "[entry]") {
	Entry cEntry("first_name", "Tim");

	REQUIRE(cEntry.getColumnName() == "first_name");
	REQUIRE(cEntry.getValue() == "Tim");
}
