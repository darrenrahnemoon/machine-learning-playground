#pragma once

#include <vector>

namespace ML {
	template<typename LabelType, typename FeatureType>
	class DataUnit {
		public :
			std::vector<FeatureType>* featureVector;
			LabelType label;
			DataUnit(const int& featureVectorSize = 0);
			~DataUnit();
	};
};

#include "entities/DataUnit.cpp"