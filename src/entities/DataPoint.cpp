#include <vector>
#include "entities/DataPoint.hpp"

namespace ML {
	// SHOULD DO: DRY this out
	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(std::initializer_list<FeatureType> _featureVector, LabelType _label) : label(_label) {
		this->featureVector = new std::vector<FeatureType>(_featureVector);
	}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(std::initializer_list<FeatureType> _featureVector) {
		this->featureVector = new std::vector<FeatureType>(_featureVector);
	}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(const int& featureVectorSize) {
		this->featureVector = new std::vector<FeatureType>(featureVectorSize);
	}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::~DataPoint() {
		delete this->featureVector;
	}

}