#include <iostream>

#include "lib/utils/debug.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/classifiers/KMeans.hpp"
#include "lib/distance/euclidean.hpp"

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

	std::cout << "Done with training";
	int correctPredictionCount = 0;
	for (auto point : *(dataHandler.testingData)) {
		uint8_t closestDistance = ML::distance::euclideanDistance(*point, classifier.clusters.at(0).centroid);
		auto* closestCluster = &(classifier.clusters.at(0));
		for (auto cluster : classifier.clusters) {
			auto distance = ML::distance::euclideanDistance(*point, cluster.centroid);
			if (distance < closestDistance) {
				closestDistance = distance;
				closestCluster = &cluster;
			}
		}
		if (closestCluster->centroid.label == point->label) {
			correctPredictionCount++;
		}
	}

	std::cout << "K = " << classifier.k << " | Accuracy: " << (double)correctPredictionCount / (double)(dataHandler.testingData->size());
}