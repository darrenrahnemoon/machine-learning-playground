#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/utils/log.cpp"
#include "lib/utils/collections.cpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::BaseDataHandler() {
		this->dataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->trainingDataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->testingDataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->validationDataset = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
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

		int datasetSize = this->dataset->size();
		std::unordered_set<int> usedIndexes(datasetSize);

		// Reserve the required space to improve performance
		int trainingDatasetSize = this->dataset->size() * this->trainingDatasetRatio;
		this->trainingDataset->reserve(trainingDatasetSize);

		int testingDatasetSize = this->dataset->size() * this->testingDatasetRatio;
		this->testingDataset->reserve(testingDatasetSize);

		int validationDatasetSize = this->dataset->size() * this->validationDatasetRatio;
		this->validationDataset->reserve(validationDatasetSize);

		utils::collections::allocateAtRandom(*(this->dataset), *(this->trainingDataset), trainingDatasetSize, usedIndexes);
		utils::collections::allocateAtRandom(*(this->dataset), *(this->testingDataset), testingDatasetSize, usedIndexes);
		utils::collections::allocateAtRandom(*(this->dataset), *(this->validationDataset), validationDatasetSize, usedIndexes);
	}
}


