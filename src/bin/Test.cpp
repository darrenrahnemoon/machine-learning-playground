#include "tests/distance.cpp"
#include "tests/knn.cpp"
#include "tests/KMeans.cpp"
#include "tests/utils.cpp"


// #include "lib/data-handlers/MNISTDataHandler.hpp"
// #include "lib/models/KNN.hpp"

// TEST_CASE("K Nearest Neighbors", "[knn][model]") {
// 	ML::MNISTDataHandler dataHandler;
// 	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
// 	dataHandler.allocateDataAtRandom();

// 	ML::KNN<uint8_t, uint8_t> model;
// 	model.dataset = dataHandler.trainingDataset;

// 	SECTION("Using Euclidian Distance") {
// 		model.distanceCalculationMethod = ML::KNN<uint8_t, uint8_t>::EuclidianDistance;
// 		model.k = GENERATE(3, 4, 5, 6, 7);
// 		SECTION("K: "s + std::to_string(model.k)) {
// 			int validResults = 0;
// 			for (auto point : *(dataHandler.validationDataset)) {
// 				if (model.predict(point) == point->label) {
// 					validResults++;
// 				}
// 			}

// 			CHECK(validResults > 0.8 * dataHandler.validationDataset->size());
// 		}
// 	}
// }