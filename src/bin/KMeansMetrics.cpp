#include "lib/utils/debug.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/classifiers/KMeans.hpp"

int main() {
	ML::debug::timer timer("KMeansMetrics");
	ML::MNISTDataHandler dataHandler;
	dataHandler.readFromFile("./assets/mnist/train-images-idx3-ubyte", "./assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();

	auto classifier = ML::KMeans<uint8_t, uint8_t>();
	classifier.k = 500;

	classifier.dataset = dataHandler.trainingData;

	classifier.chooseCentroidsAtRanddom();
	classifier.partition();

	classifier.ensureClustersMostFrequentLabelIdentified();
}