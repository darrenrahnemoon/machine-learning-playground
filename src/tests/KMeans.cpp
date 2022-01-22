#include <iostream>

#include "catch2/catch_test_macros.hpp"

#include "lib/classifiers/KMeans.hpp"

TEST_CASE("K-Means Clustering Algorithm", "[classifier][k-means]") {
	enum class Class { A = 0, B, C, D };
	auto classifier = ML::KMeans<Class, int>();

	auto getDataPoint = [](std::initializer_list<int> featureVector, Class label = Class::A) {
		return std::make_shared<ML::DataPoint<Class, int>>(featureVector, label);
	};

	classifier.dataset = std::make_shared<std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>>(std::vector<std::shared_ptr<ML::DataPoint<Class, int>>>({
		getDataPoint({ 1, 2 }, Class::A),
		getDataPoint({ 1, 3 }, Class::A),
		getDataPoint({ 2, 2 }, Class::A),
		getDataPoint({ 3, 2 }, Class::B),
		getDataPoint({ 3, 3 }, Class::C),

		getDataPoint({ 40, 10 }, Class::C),
		getDataPoint({ 15, 12 }, Class::C),
		getDataPoint({ 10, 20 }, Class::C),
		getDataPoint({ 12, 41 }, Class::C),
	}));

	classifier.k = 4;

	classifier.chooseCentroidsAtRanddom();

	SECTION("Should partition the data correctly") {
		classifier.partition();
	}

}