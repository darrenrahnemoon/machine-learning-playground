#pragma once
#include "entities/DataPoint.hpp"

namespace ML {
	namespace distance {
		
		template <typename LabelType, typename FeatureType>
		FeatureType euclideanDistance(DataPoint<LabelType, FeatureType> point1, DataPoint<LabelType, FeatureType> point2);

		template<typename LabelType, typename FeatureType>
		FeatureType minkowskyDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2);

		template<typename LabelType, typename FeatureType>
		FeatureType correllationDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2);

		template<typename LabelType, typename FeatureType>
		FeatureType chiSquareDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2);

	}
}

#include "lib/distance.cpp"