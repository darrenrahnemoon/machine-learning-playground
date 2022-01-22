#pragma once
#include "entities/DataPoint.hpp"

namespace ML {
	namespace distance {
		
		template <typename LabelType, typename FeatureType>
		FeatureType euclideanDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2);

		template<typename LabelType, typename FeatureType>
		FeatureType minkowskyDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2);

		template<typename LabelType, typename FeatureType>
		FeatureType correllationDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2);

		template<typename LabelType, typename FeatureType>
		FeatureType chiSquareDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2);

	}
}

#include "lib/distance/euclidean.cpp"