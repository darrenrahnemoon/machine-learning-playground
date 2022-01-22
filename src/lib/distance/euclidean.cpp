#pragma once

#include <exception>
#include <memory>
#include <cmath>

#include "entities/DataPoint.hpp"

namespace ML {
	namespace distance {
		template <typename LabelType, typename FeatureType>
		FeatureType euclideanDistance(const DataPoint<LabelType, FeatureType>& point1, const DataPoint<LabelType, FeatureType>& point2) {
			if (point1.featureVector.size() != point2.featureVector.size()) {
				throw std::runtime_error("Point 1 and Point 2 have feature vectors with different sizes");
			}
			FeatureType sum = 0;
			for (unsigned int index = 0; index < point1.featureVector.size(); index++) {
				sum += pow(point1.featureVector[index] - point2.featureVector[index], 2);
			}
			return sqrt(sum);
		}
	}
}