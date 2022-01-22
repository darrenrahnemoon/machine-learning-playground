#include "catch2/catch_test_macros.hpp"

#include "entities/DataPoint.hpp"
#include "lib/distance/euclidean.hpp"

TEST_CASE("Methods for Measuring Distance", "[distance]") {
	SECTION("Euclidean Distance", "[euclidean]") {
		ML::DataPoint<int, int> point1({ 10, 22, 31 });
		ML::DataPoint<int, int> point2({ 22, 33, 41 });
		REQUIRE(ML::distance::euclideanDistance(point1, point2) == 19);
	}
	SECTION("Minkowsky Distance", "[minkowsky]") {
		// SHOULD DO
	}
	SECTION("Correllation Distance", "[correllation]") {
		// SHOULD DO
	}
	SECTION("Chi-Square Distance", "[chi-square]") {
		// SHOULD DO
	}
}
