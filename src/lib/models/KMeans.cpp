#include <exception>
#include <thread>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>

#include "lib/utils/debug.cpp"
#include "lib/distance/euclidean.hpp"
#include "lib/models/KMeans.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	KMeans<LabelType, FeatureType>::KMeans() : k(2), distanceCalculationMethod(ML::distance::euclideanDistance) {}
	
	template<typename LabelType, typename FeatureType>
	KMeans<LabelType, FeatureType>::~KMeans() {}

	template<typename LabelType, typename FeatureType>
	void KMeans<LabelType, FeatureType>::chooseCentroidsAtRanddom() {
		this->clusters.clear();
		this->clusters.reserve(this->k);

		std::unordered_set<int> usedIndexes(this->k);

		int allocated = 0;
		while (allocated < this->k) {
			int randomIndex = rand() % this->dataset->size();
			if (usedIndexes.find(randomIndex) == usedIndexes.end()) {
				Cluster<LabelType, FeatureType> cluster;
				cluster.centroid = *(this->dataset->at(randomIndex));
				this->clusters.push_back(cluster);
				usedIndexes.insert(randomIndex);
				allocated++;
			}
		}
		//
	}

	template<typename LabelType, typename FeatureType>
	void KMeans<LabelType, FeatureType>::chooseCentroidsUsingKMeansPlusPlus() {
		throw std::runtime_error("not implemented");
	}

	template<typename LabelType, typename FeatureType>
	void KMeans<LabelType, FeatureType>::partition() {
		// Pour the entire dataset into the first cluster to distribute them later in the loop
		this->clusters.at(0).members = *(this->dataset);

		for (auto cluster : this->clusters) {
			this->previousCentroids.push_back(cluster.centroid);
		}

		while (true) {

			for (int currentClusterIndex = 0; currentClusterIndex < this->clusters.size(); currentClusterIndex++) {
				auto& currentCluster = this->clusters[currentClusterIndex];

				for (int pointIndex = 0; pointIndex < currentCluster.members.size(); pointIndex++) {
					auto& point = currentCluster.members.at(pointIndex);

					// Find the closest centroid
					FeatureType closestDistance = this->distanceCalculationMethod(*point, currentCluster.centroid);
					auto* closestCluster = &currentCluster;
					for (auto& potentialDestinationCluster : this->clusters) {
						
						// SHOULD DO: figure out how to not uses shared_ptr everywhere but still get the same optimization
						auto distance = this->distanceCalculationMethod(*point, potentialDestinationCluster.centroid);
						if (distance < closestDistance) {
							closestDistance = distance;
							closestCluster = &potentialDestinationCluster;
						}
					}

					// If the current cluster's centroid isn't the closest to this point
					if (&currentCluster != closestCluster) {
						closestCluster->members.push_back(point);
						currentCluster.members.erase(currentCluster.members.begin() + pointIndex);
					}
				}
			}

			this->ensureClustersCentroidsAreAdjusted();

			// If centroids haven't changed since the last iteration then the algorithm has converged
			int sameCentroidsCount = 0;
			for (int i = 0; i < this->clusters.size(); i++) {
				auto& cluster = this->clusters.at(i);
				auto& previousCentroid = this->previousCentroids.at(i);
				if (previousCentroid.hasSameFeatures(cluster.centroid)) {
					sameCentroidsCount++;
				}
				previousCentroid = cluster.centroid;
			}
			if (sameCentroidsCount == this->clusters.size()) {
				return;
			}
		}
	}

	template<typename LabelType, typename FeatureType>
	void KMeans<LabelType, FeatureType>::ensureClustersCentroidsAreAdjusted(const bool& multithreaded) {

		if (multithreaded) {
			std::thread threads[this->clusters.size()];
			for (int i = 0; i < this->clusters.size(); i++) {
				auto& cluster = this->clusters.at(i);
				threads[i] = std::thread(&Cluster<LabelType, FeatureType>::ensureCentroidIsAdjusted, &cluster);
			}
			for (auto& thread : threads) {
				thread.join();
			}
		}
		else {
			for (auto cluster : this->clusters) {
				cluster.ensureCentroidIsAdjusted();
			}
		}
	}

	template<typename LabelType, typename FeatureType>
	void KMeans<LabelType, FeatureType>::ensureClustersMostFrequentLabelIdentified(const bool& multithreaded) {

		if (multithreaded) {
			std::thread threads[this->clusters.size()];
			for (int i = 0; i < this->clusters.size(); i++) {
				auto& cluster = this->clusters.at(i);
				threads[i] = std::thread(&Cluster<LabelType, FeatureType>::identifyMostFrequentLabel, &cluster);
			}
			for (auto& thread : threads) {
				thread.join();
			}
		}
		else {
			for (auto cluster : this->clusters) {
				cluster.identifyMostFrequentLabel();
			}
		}
	}

	

	template<typename LabelType, typename FeatureType>
	LabelType Cluster<LabelType, FeatureType>::identifyMostFrequentLabel() {
		std::map<LabelType, int> occurrences;
		for (auto point : this->members) {
			LabelType& label = point->label;
			if (occurrences.count(label)) {
				occurrences[label]++;
			}
			else {
				occurrences[label] = 1;
			}
		}

		auto mostFrequent = std::max_element(
			occurrences.begin(),
			occurrences.end(),
			[](std::pair<LabelType, int> occurrence1, std::pair<LabelType, int> occurrence2) {
				return occurrence1.second < occurrence2.second;
			}
		);

		this->centroid.label = mostFrequent->first;

		return mostFrequent->first;
	}

	template<typename LabelType, typename FeatureType>
	void Cluster<LabelType, FeatureType>::ensureCentroidIsAdjusted() {
		// if this cluster is empty there's no way to adjust the centroid	
		if (!this->members.size()) {
			return;
		}

		auto& featureVector = this->centroid.featureVector;
		for (int featureIndex = 0; featureIndex < featureVector.size(); featureIndex++) {
			auto& feature = featureVector.at(featureIndex);
			feature = 0;
			for (auto point : this->members) {
				feature += point->featureVector.at(featureIndex);
			}
			feature = feature / this->members.size();
		}
	}

}