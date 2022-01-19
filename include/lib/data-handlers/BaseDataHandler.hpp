#pragma once

#include <memory>
#include <vector>
#include <map>

#include "entities/DataPoint.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> rawData;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> trainingData;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> testingData;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> validationData;

			double trainingDataRatio = 0.75;
			double testingDataRatio = 0.20;
			double validationDataRatio = 0.05;

			std::map<LabelType, int> classToEnumMap;

			BaseDataHandler();
			~BaseDataHandler();

			virtual void readFromFile();
			/**
			 * Split the raw data between training, testing, and validation vector
			 */
			void allocateDataAtRandom();
	};
};

#include "lib/data-handlers/BaseDataHandler.cpp"