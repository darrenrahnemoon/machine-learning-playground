#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>

#include "lib/utils/timer.cpp"
#include "lib/utils/errors.cpp"
#include "lib/utils/log.cpp"
#include "lib/utils/collections.cpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::BaseDataHandler() {}

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::~BaseDataHandler() {}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::readFromFile() {
		throw errors::NotImplemented();
	}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::allocateDataAtRandom() {
		utils::timer timer("Allocating data at random");
		
		int datasetSize = this->dataset->size();
		std::unordered_set<int> usedIndexes(datasetSize);

		// Reserve the required space to improve performance
		int trainingDatasetSize = this->dataset->size() * this->trainingDatasetRatio;
		int testingDatasetSize = this->dataset->size() * this->testingDatasetRatio;
		int validationDatasetSize = this->dataset->size() * this->validationDatasetRatio;

		this->trainingDataset = std::make_shared<Dataset<LabelType, FeatureType>>(utils::collections::chooseAtRandom(*(this->dataset), trainingDatasetSize, usedIndexes));
		this->testingDataset = std::make_shared<Dataset<LabelType, FeatureType>>(utils::collections::chooseAtRandom(*(this->dataset), testingDatasetSize, usedIndexes));
		this->validationDataset = std::make_shared<Dataset<LabelType, FeatureType>>(utils::collections::chooseAtRandom(*(this->dataset), validationDatasetSize, usedIndexes));
	}
}


