#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>

#include "lib/utils/debug.cpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::BaseDataHandler() {
		this->rawData = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->trainingData = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
		this->testingData = std::make_shared<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>>();
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
		debug::timer timer("Allocating data at random");

		auto& rawData = this->rawData;
		int rawDataSize = this->rawData->size();
		std::unordered_set<int> usedIndexes(rawDataSize);

		// Reserve the vector space to improve performance
		int trainingDataSize = rawDataSize * this->trainingDataRatio;
		this->trainingData->reserve(trainingDataSize);

		int testingDataSize = rawDataSize * this->testingDataRatio;
		this->testingData->reserve(testingDataSize);

		int validationDataSize = rawDataSize * this->validationDataRatio;
		this->validationData->reserve(validationDataSize);

		auto allocateAtRandom = [&usedIndexes, &rawData, &rawDataSize](auto& array, int&count) {
			int allocated = 0;
			while (allocated < count) {
				int randomIndex = rand() % rawDataSize;
				if (usedIndexes.find(randomIndex) == usedIndexes.end()) {
					array->push_back((*rawData)[randomIndex]);
					usedIndexes.insert(randomIndex);
					allocated++;
				}
			}
		};

		debug::timer::call("Allocating data points at random to training data", allocateAtRandom, trainingData, trainingDataSize);
		debug::timer::call("Allocating data points at random to testing data", allocateAtRandom, testingData, testingDataSize);
		debug::timer::call("Allocating data points at random to validation data", allocateAtRandom, validationData, validationDataSize);
	}
}

