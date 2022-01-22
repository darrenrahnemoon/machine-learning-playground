#include <memory>
#include <exception>
#include <algorithm>

#include "lib/utils/debug.cpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "lib/classifiers/KNN.hpp"
#include "lib/distance/euclidean.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	KNN<LabelType, FeatureType>::KNN() : k(1), distanceCalculationMethod(ML::distance::euclideanDistance) {}
	
	template<typename LabelType, typename FeatureType>
	KNN<LabelType, FeatureType>::~KNN() {}

	template<typename LabelType, typename FeatureType>
	LabelType KNN<LabelType, FeatureType>::predict(const DataPoint<LabelType, FeatureType>& point) {
		std::map<LabelType, int> occurrences;
		for (auto neighbor : this->getNearestNeighbors(point)) {
			LabelType& label = neighbor->label;
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
		
		return mostFrequent->first;
	}

	template<typename LabelType, typename FeatureType>
	std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>> KNN<LabelType, FeatureType>::getNearestNeighbors(const DataPoint<LabelType, FeatureType>& point) {
		std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>> neighbors(this->k);
		std::vector<FeatureType> neighborsDistance(this->k);
		std::vector<FeatureType> allDistances(this->dataset->size());

		std::fill(neighbors.begin(), neighbors.end(), this->dataset->at(0));
		std::fill(neighborsDistance.begin(), neighborsDistance.end(), this->distanceCalculationMethod(point, *(this->dataset->at(0))));

		for (int datasetIndex = 0; datasetIndex < this->dataset->size(); datasetIndex++) {
			allDistances[datasetIndex] = this->distanceCalculationMethod(point, *(this->dataset->at(datasetIndex)));
		}

		for (int kIndex = 0; kIndex < this->k; kIndex++) {
			for (int datasetIndex = 0; datasetIndex < this->dataset->size(); datasetIndex++) {
				if (allDistances[datasetIndex] < neighborsDistance[kIndex] && (kIndex == 0 || neighborsDistance[kIndex - 1] > allDistances[datasetIndex])) {
					neighborsDistance[kIndex] = allDistances[datasetIndex];
					neighbors[kIndex] = this->dataset->at(datasetIndex);
				}
			}
		}

		return neighbors;
	}
}