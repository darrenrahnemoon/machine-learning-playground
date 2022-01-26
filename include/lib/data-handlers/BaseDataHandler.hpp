#pragma once

#include <memory>
#include <vector>
#include <map>

#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	using Dataset = std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>;

	template<typename LabelType, typename FeatureType>
	class BaseDataHandler {
		public :
			std::shared_ptr<Dataset<LabelType, FeatureType>> dataset;
			std::shared_ptr<Dataset<LabelType, FeatureType>> trainingDataset;
			std::shared_ptr<Dataset<LabelType, FeatureType>> testingDataset;
			std::shared_ptr<Dataset<LabelType, FeatureType>> validationDataset;

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