#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "../Util.h"

TEST_CASE( "Test File Exists", "[fileExists]" ) {
	REQUIRE( Util::fileExist("tests/mocks/test-file.txt"));
	REQUIRE_FALSE(Util::fileExist("tests/mocks/no-file.txt"));
};
