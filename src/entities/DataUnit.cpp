#include <vector>
#include "entities/DataUnit.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	DataUnit<LabelType, FeatureType>::DataUnit(const int& featureVectorSize) {
		if (!featureVectorSize) {
			this->featureVector = new std::vector<FeatureType>;
		}
		else {
			this->featureVector = new std::vector<FeatureType>(featureVectorSize);
		}
	}

	template<typename LabelType, typename FeatureType>
	DataUnit<LabelType, FeatureType>::~DataUnit() {
		delete this->featureVector;
	}

}