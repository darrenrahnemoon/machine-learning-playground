#include "tests/distance.cpp"
#include "tests/knn.cpp"

// #include "lib/data-handlers/MNISTDataHandler.hpp"
// #include "lib/classifiers/KNN.hpp"

// TEST_CASE("K Nearest Neighbors", "[knn][classifier]") {
// 	ML::MNISTDataHandler dataHandler;
// 	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
// 	dataHandler.allocateDataAtRandom();

// 	ML::KNN<uint8_t, uint8_t> classifier;
// 	classifier.dataset = dataHandler.trainingData;

// 	SECTION("Using Euclidian Distance") {
// 		classifier.distanceCalculationMethod = ML::KNN<uint8_t, uint8_t>::EuclidianDistance;
// 		classifier.k = GENERATE(3, 4, 5, 6, 7);
// 		SECTION("K: "s + std::to_string(classifier.k)) {
// 			int validResults = 0;
// 			for (auto point : *(dataHandler.testingData)) {
// 				if (classifier.predict(point) == point->label) {
// 					validResults++;
// 				}
// 			}

// 			CHECK(validResults > 0.8 * dataHandler.testingData->size());
// 		}
// 	}
// }