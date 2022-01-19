#include <iostream>

#include "lib/debug.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/classifiers/KNN.hpp"
#include "lib/distance.hpp"

int main() {
	debug::timer timer("Main");

	ML::MNISTDataHandler dataHandler;
	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();

	ML::KNN<uint8_t, uint8_t> classifier;
	classifier.k = 2;
	classifier.distanceCalculationMethod = ML::distance::euclideanDistance;
	classifier.dataset = dataHandler.trainingData;

	double correctPredictionsCount = 0;
	for (int i = 0; i < dataHandler.testingData->size(); i++) {
		auto point = dataHandler.testingData->at(i);
		auto prediction = classifier.predict(point);
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
	std::cout << correctPredictionsCount / dataHandler.testingData->size() * 100;
}