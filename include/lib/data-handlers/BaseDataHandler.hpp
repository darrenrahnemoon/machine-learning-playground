#pragma once

#include <memory>
#include <vector>
#include <map>

#include "entities/DataPoint.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> dataset;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> trainingDataset;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> testingDataset;
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> validationData;

			double trainingDatasetRatio = 0.75;
			double testingDatasetRatio = 0.20;
			double validationDataRatio = 0.05;

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