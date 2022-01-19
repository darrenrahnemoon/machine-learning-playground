#pragma once

#include <vector>
#include <initializer_list>

namespace ML {
	template<typename LabelType, typename FeatureType>
	class DataPoint {
		public :
			std::vector<FeatureType>* featureVector;
			LabelType label;

			DataPoint(const int& featureVectorSize = 0);
			DataPoint(std::initializer_list<FeatureType> featureVector, LabelType label);
			DataPoint(std::initializer_list<FeatureType> featureVector);
			~DataPoint();
	};
};

#include "entities/DataPoint.cpp"