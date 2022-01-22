#pragma once
#include "entities/DataPoint.hpp"

namespace ML {
	namespace distance {

		template<typename LabelType, typename FeatureType>
		FeatureType correllationDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2);

	}
}

#include "lib/distance/correllation.cpp"