#include <memory>
#include <vector>
#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

#include "lib/classifiers/KNN.hpp"
#include "entities/DataPoint.hpp"

TEST_CASE("K Nearest Neighbor Classifier", "[classifier][knn]") {
	enum class Class { A = 0, B, C, D };
	auto classifier = ML::KNN<Class, int>();

	auto getDataPoint = [](std::initializer_list<int> featureVector, Class label = Class::A) {
		return std::make_shared<ML::DataPoint<Class, int>>(featureVector, label);
	};

	classifier.dataset = std::make_shared<std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>>(std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>({
		getDataPoint({ 1 ,2 }, Class::A),
		getDataPoint({ 1 ,3 }, Class::A),
		getDataPoint({ 2 ,2 }, Class::A),
		getDataPoint({ 1 ,4 }, Class::B),
		getDataPoint({ 5 ,2 }, Class::C)
	}));

	SECTION("Should classify the points correctly with k = 1") {
		classifier.k = 1;
		REQUIRE(classifier.predict(getDataPoint({ 2 ,1 })) == Class::A);
		REQUIRE(classifier.predict(getDataPoint({ 4 , 3 })) == Class::C);
		REQUIRE(classifier.predict(getDataPoint({ 100, 100 })) == Class::C);
	}

	SECTION("Should classify the points correctly with k = 3") {
		classifier.k = 3;
		REQUIRE(classifier.predict(getDataPoint({ 4 , 3 })) == Class::C);
	}

	SECTION("Should classify the points correctly with k = 4") {
		classifier.k = 4;
		REQUIRE(classifier.predict(getDataPoint({ 4 , 3 })) == Class::A);
	}


}