#include <vector>
#include "entities/DataUnit.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	DataUnit<LabelType, FeatureType>::DataUnit() {
		this->featureVector = new std::vector<FeatureType>;
	}

	template<typename LabelType, typename FeatureType>
	DataUnit<LabelType, FeatureType>::~DataUnit() {
		delete this->featureVector;
	}

}