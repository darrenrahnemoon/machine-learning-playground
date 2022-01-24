#include <memory>
#include <vector>
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

#include "lib/models/KNN.hpp"
#include "entities/DataPoint.hpp"

TEST_CASE("K Nearest Neighbor Model", "[model][knn]") {
	enum class Class { A = 0, B, C, D };
	auto model = ML::KNN<Class, int>();

	auto getDataPoint = [](std::initializer_list<int> featureVector, Class label = Class::A) {
		ML::DataPoint<Class, int> result(featureVector, label);
		return result;
	};

	auto getDataPointPtr = [](std::initializer_list<int> featureVector, Class label = Class::A) {
		return std::make_shared<ML::DataPoint<Class, int>>(featureVector, label);
	};

	model.dataset = std::make_shared<std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>>(std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>({
		getDataPointPtr({ 1, 2 }, Class::A),
		getDataPointPtr({ 1, 3 }, Class::A),
		getDataPointPtr({ 2, 2 }, Class::A),
		getDataPointPtr({ 1, 4 }, Class::B),
		getDataPointPtr({ 5, 2 }, Class::C)
	}));

	WHEN("k = 1") {
		model.k = 1;
		THEN("Should classify the points correctly") {
			REQUIRE(model.predict(getDataPoint({ 2 ,1 })) == Class::A);
			REQUIRE(model.predict(getDataPoint({ 4 , 3 })) == Class::C);
			REQUIRE(model.predict(getDataPoint({ 100, 100 })) == Class::C);
		}
	}

	WHEN("k = 3") {
		model.k = 3;
		THEN("Should classify the points correctly") {
			REQUIRE(model.predict(getDataPoint({ 4 , 3 })) == Class::C);
		}
	}

	WHEN("k = 4") {
		model.k = 4;
		THEN("Should classify the points correctly") {
			REQUIRE(model.predict(getDataPoint({ 4 , 3 })) == Class::A);
		}
	}
}