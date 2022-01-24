#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/models/KNN.hpp"
#include "lib/distance/euclidean.hpp"

int main() {
	ML::utils::timer timer("Main");

	ML::MNISTDataHandler dataHandler;
	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();

	ML::KNN<uint8_t, uint8_t> model;
	model.k = 2;
	model.distanceCalculationMethod = ML::distance::euclideanDistance;
	model.dataset = dataHandler.trainingDataset;

	double correctPredictionsCount = 0;
	for (int i = 0; i < dataHandler.validationDatasetset->size(); i++) {
		auto point = dataHandler.validationDatasetset->at(i);
		auto prediction = model.predict(*point);
		if (prediction == point->label) {
			correctPredictionsCount++;
		}
		std::cout
			<< "Expected: " << (unsigned)point->label 
			<< ", Predicted: " << (unsigned)prediction
			<< ", Total: "<< i
			<< ", Correct: " << correctPredictionsCount 
			<< std::endl;
	}
	std::cout << correctPredictionsCount / dataHandler.validationDatasetset->size() * 100;
}