#pragma once

#include <exception>
#include <memory>
#include <cmath>

#include "entities/DataPoint.hpp"

namespace ML {
	namespace distance {
		template<typename LabelType, typename FeatureType>
		FeatureType chiSquareDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2) {
			throw std::runtime_error("not implemented");
		}
	}
}