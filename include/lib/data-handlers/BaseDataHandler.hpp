#pragma once

#include <memory>
#include <vector>
#include <map>

#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	using Dataset = std::vector<SharedDataPoint<LabelType, FeatureType>>;

	template<typename LabelType, typename FeatureType>
	using SharedDataset = std::shared_ptr<Dataset<LabelType, FeatureType>>;


	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			SharedDataset<LabelType, FeatureType> dataset;
			SharedDataset<LabelType, FeatureType> trainingDataset;
			SharedDataset<LabelType, FeatureType> testingDataset;
			SharedDataset<LabelType, FeatureType> validationDataset;

			double trainingDatasetRatio = 0.75;
			double testingDatasetRatio = 0.20;
			double validationDatasetRatio = 0.05;

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