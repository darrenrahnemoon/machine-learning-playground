#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "lib/utils/collections.cpp"

TEST_CASE("utils", "[utils]") {
	SECTION("get top k items") {
		std::vector<int> items = { 1, 8, 5, 7, 10, 20 };

		SECTION("should return top 3 largest items") {
			std::vector<int> top3Largest = ML::utils::collections::getTop(3, items, [](const int& item1, const int& item2) { return item1 > item2; });
			REQUIRE(top3Largest.size() == 3);
			REQUIRE(top3Largest[0] == 20);
			REQUIRE(top3Largest[1] == 10);
			REQUIRE(top3Largest[2] == 8);
		}
		SECTION("should return top 3 smallest items") {
			std::vector<int> top3Smallest = ML::utils::collections::getTop(3, items, [](const int& item1, const int& item2) { return item1 < item2; });
			REQUIRE(top3Smallest.size() == 3);
			REQUIRE(top3Smallest[0] == 1);
			REQUIRE(top3Smallest[1] == 5);
			REQUIRE(top3Smallest[2] == 7);
		}

	}
}