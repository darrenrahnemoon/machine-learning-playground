#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "lib/models/KMeans.hpp"
#include "lib/distance/euclidean.hpp"

int main() {
	ML::utils::timer timer("KMeansMetrics");
	ML::MNISTDataHandler dataHandler;
	dataHandler.readFromFile("./assets/mnist/train-images-idx3-ubyte", "./assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();

	for (int k = 50; k < 1000; k++) {
		auto model = ML::KMeans<uint8_t, uint8_t>();
		model.dataset = dataHandler.trainingData;
		model.k = k;

		model.chooseCentroidsAtRanddom();
		model.partition();

		model.ensureClustersMostFrequentLabelIdentified();

		int correctPredictionCount = 0;
		for (auto point : *(dataHandler.testingData)) {
			uint8_t closestDistance = ML::distance::euclideanDistance(*point, model.clusters.at(0).centroid);
			auto* closestCluster = &(model.clusters.at(0));
			for (auto cluster : model.clusters) {
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
		std::cout << "K = " << model.k << " | Accuracy: " << (double)correctPredictionCount / (double)(dataHandler.testingData->size()) * 100 << "%";
	}
}