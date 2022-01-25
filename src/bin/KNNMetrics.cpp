#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/models/KNN.hpp"
#include "lib/distance/euclidean.hpp"

int main() {
	using namespace ML;

	utils::timer timer("KNNMetrics");
	MNISTDataHandler dataHandler;
	dataHandler.readFromFile("./assets/mnist/train-images-idx3-ubyte", "./assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();

	for (int k = 1; k < 20; k++) {
		auto model = KNN<uint8_t, uint8_t>();
		model.dataset = dataHandler.trainingDataset;
		model.k = k;

		int correctPredictionCount = 0;
		for (auto point : *(dataHandler.validationDataset)) {
			if (model.predict(*point) == point->label) {
				correctPredictionCount++;
			}
		}

		std::cout << "K: " << model.k << " | ";
		std::cout << "Correct: " << correctPredictionCount << "/" << dataHandler.validationDataset->size() << " | ";
		std::cout << "Accuracy: " << (double)correctPredictionCount / (double)(dataHandler.validationDataset->size()) * 100 << "%" << std::endl;
	}
}