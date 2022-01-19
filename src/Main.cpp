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
	classifier.k = 4;
	classifier.distanceCalculationMethod = ML::distance::euclideanDistance;
	classifier.dataset = dataHandler.trainingData;
}