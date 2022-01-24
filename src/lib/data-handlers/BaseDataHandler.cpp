#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::BaseDataHandler() {
		this->dataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->trainingDataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->validationDatasetset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->validationData = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
	}

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::~BaseDataHandler() {}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::readFromFile() {
		// SHOULD DO: add a NotImplemented exception
		throw std::runtime_error("not implemented");
	}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::allocateDataAtRandom() {
		utils::timer timer("Allocating data at random");

		auto& dataset = this->dataset;
		int datasetSize = this->dataset->size();
		std::unordered_set<int> usedIndexes(datasetSize);

		// Reserve the vector space to improve performance
		int trainingDatasetSize = datasetSize * this->trainingDatasetRatio;
		this->trainingDataset->reserve(trainingDatasetSize);

		int validationDatasetsetSize = datasetSize * this->validationDatasetsetRatio;
		this->validationDatasetset->reserve(validationDatasetsetSize);

		int validationDataSize = datasetSize * this->validationDataRatio;
		this->validationData->reserve(validationDataSize);

		auto allocateAtRandom = [&usedIndexes, &dataset, &datasetSize](auto& array, int&count) {
			int allocated = 0;
			while (allocated < count) {
				int randomIndex = rand() % datasetSize;
				if (usedIndexes.find(randomIndex) == usedIndexes.end()) {
					array->push_back((*dataset)[randomIndex]);
					usedIndexes.insert(randomIndex);
					allocated++;
				}
			}
		};

		utils::timer::call("Allocating data points at random to training data", allocateAtRandom, trainingDataset, trainingDatasetSize);
		utils::timer::call("Allocating data points at random to testing data", allocateAtRandom, validationDatasetset, validationDatasetsetSize);
		utils::timer::call("Allocating data points at random to validation data", allocateAtRandom, validationData, validationDataSize);
	}
}

