#pragma once

#include <vector>

namespace ML {
	template<typename LabelType, typename FeatureType>
	class DataPoint {
		public :
			std::vector<FeatureType>* featureVector;
			LabelType label;
			DataPoint(const int& featureVectorSize = 0);
			~DataPoint();
	};
};

#include "entities/DataPoint.cpp"