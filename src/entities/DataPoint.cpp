#include <vector>
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(const int& featureVectorSize) {
		if (!featureVectorSize) {
			this->featureVector = new std::vector<FeatureType>;
		}
		else {
			this->featureVector = new std::vector<FeatureType>(featureVectorSize);
		}
	}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::~DataPoint() {
		delete this->featureVector;
	}

}