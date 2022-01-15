#pragma once

#include <vector>
#include <map>

#include "entities/DataUnit.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			std::vector<DataUnit<LabelType, FeatureType>*>* rawData;
			std::vector<DataUnit<LabelType, FeatureType>*>* trainingData;
			std::vector<DataUnit<LabelType, FeatureType>*>* testingData;
			std::vector<DataUnit<LabelType, FeatureType>*>* validationData;

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
			void randomlyDistributeData();
	};
};

#include "lib/data-handlers/BaseDataHandler.cpp"