#pragma once

#include <vector>
#include <initializer_list>

namespace ML {
	template<typename LabelType, typename FeatureType>
	class DataPoint {
		public :
			std::vector<FeatureType> featureVector;
			LabelType label;

			DataPoint(const int& featureVectorSize = 0);
			DataPoint(std::initializer_list<FeatureType> featureVector, LabelType label);
			DataPoint(std::initializer_list<FeatureType> featureVector);

			bool hasSameFeatures(DataPoint<LabelType, FeatureType> point);
	};

	template<typename LabelType, typename FeatureType>
	using SharedDataPoint = std::shared_ptr<DataPoint<LabelType, FeatureType>>;
}

#include "entities/DataPoint.cpp"