#include <vector>
#include <unordered_set>

#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataUnit.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::BaseDataHandler() {
		this->rawData = new std::vector<DataUnit<LabelType, FeatureType>*>;
		this->trainingData = new std::vector<DataUnit<LabelType, FeatureType>*>;
		this->testingData = new std::vector<DataUnit<LabelType, FeatureType>*>;
		this->validationData = new std::vector<DataUnit<LabelType, FeatureType>*>;
	}

	template<typename LabelType, typename FeatureType>
	BaseDataHandler<LabelType, FeatureType>::~BaseDataHandler() {
		delete this->rawData;
		delete this->trainingData;
		delete this->testingData;
		delete this->validationData;
	}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::readFromFile() {
		// SHOULD DO: add a NotImplemented exception
		throw std::runtime_error("not implemented");
	}

	template<typename LabelType, typename FeatureType>
	void BaseDataHandler<LabelType, FeatureType>::randomlyDistributeData() {
		std::unordered_set<int> usedIndexes;
		auto& rawData = this->rawData;
		int& rawDataSize = this->rawData->size();
		int trainingDataSize = rawDataSize * this->trainingDataRatio;
		int testingDataSize = rawDataSize * this->testingDataRatio;
		int validationDataSize = rawDataSize * this->validationDataRatio;

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

		allocateAtRandom(trainingData, trainingDataSize);
		allocateAtRandom(testingData, testingDataSize);
		allocateAtRandom(validationData, validationDataSize);
	}
}

