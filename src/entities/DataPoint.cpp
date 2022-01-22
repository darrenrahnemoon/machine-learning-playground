#include <vector>
#include "entities/DataPoint.hpp"

namespace ML {
	// SHOULD DO: DRY this out
	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(std::initializer_list<FeatureType> _featureVector, LabelType _label) : label(_label), featureVector(_featureVector) {}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(std::initializer_list<FeatureType> _featureVector) : featureVector(_featureVector) {}

	template<typename LabelType, typename FeatureType>
	DataPoint<LabelType, FeatureType>::DataPoint(const int& featureVectorSize) : featureVector(featureVectorSize){}

	template<typename LabelType, typename FeatureType>
	bool DataPoint<LabelType, FeatureType>::hasSameFeatures(DataPoint<LabelType, FeatureType> point) {
		return this->featureVector == point.featureVector;
	}

}