#pragma once

#include <memory>
#include "lib/data-handlers/BaseDataHandler.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class KNN {
		typedef std::shared_ptr<DataPoint<LabelType, FeatureType>> Data;
		public:
			int k;
			FeatureType (*distanceCalculationMethod)(Data, Data);
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> dataset;

			KNN();
			~KNN();

			LabelType predictClass(Data data);
			std::vector<Data> getNearestNeighbors(Data point);
	};

}

#include "lib/classifiers/KNN.cpp"