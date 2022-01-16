#pragma once

#include <memory>
#include <vector>
#include <map>

#include "entities/DataUnit.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			std::vector<std::shared_ptr<DataUnit<LabelType, FeatureType>>>* rawData;
			std::vector<std::shared_ptr<DataUnit<LabelType, FeatureType>>>* trainingData;
			std::vector<std::shared_ptr<DataUnit<LabelType, FeatureType>>>* testingData;
			std::vector<std::shared_ptr<DataUnit<LabelType, FeatureType>>>* validationData;

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