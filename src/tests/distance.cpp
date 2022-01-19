#include <memory>
#include <initializer_list>
#include "catch2/catch_test_macros.hpp"

#include "entities/DataPoint.hpp"
#include "lib/distance.hpp"

TEST_CASE("Methods for Measuring Distance", "[distance]") {
	SECTION("Euclidean Distance", "[euclidean]") {
		std::shared_ptr<ML::DataPoint<int, int>> point1 = std::make_shared<ML::DataPoint<int, int>>(std::initializer_list<int>{ 10, 22, 31 });
		std::shared_ptr<ML::DataPoint<int, int>> point2 = std::make_shared<ML::DataPoint<int, int>>(std::initializer_list<int>{ 22, 33, 41 });
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
