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

	for (int k = 50; k < 1000; k++) {
		auto classifier = ML::KMeans<uint8_t, uint8_t>();
		classifier.dataset = dataHandler.trainingData;
		classifier.k = k;

		classifier.chooseCentroidsAtRanddom();
		classifier.partition();

		classifier.ensureClustersMostFrequentLabelIdentified();

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

		std::cout << "Correct: " << correctPredictionCount << "/" << dataHandler.testingData->size() << std::endl;
		std::cout << "K = " << classifier.k << " | Accuracy: " << (double)correctPredictionCount / (double)(dataHandler.testingData->size()) * 100 << "%";
	}
}