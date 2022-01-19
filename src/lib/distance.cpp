#pragma once

#include <exception>
#include <memory>
#include <cmath>

namespace ML {
	namespace distance {

		template <typename LabelType, typename FeatureType>
		FeatureType euclideanDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2) {
			if (point1->featureVector->size() != point2->featureVector->size()) {
				throw std::runtime_error("Point 1 and Point 2 have feature vectors with different sizes");
			}
			FeatureType sum = 0;
			for (unsigned int index = 0; index < point1->featureVector->size(); index++) {
				sum += pow(point1->featureVector[0][index] -  point2->featureVector[0][index], 2);
			}
			return sqrt(sum);
		}

		template<typename LabelType, typename FeatureType>
		FeatureType minkowskyDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2) {
			throw std::runtime_error("not implemented");
		}

		template<typename LabelType, typename FeatureType>
		FeatureType correllationDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2) {
			throw std::runtime_error("not implemented");
		}

		template<typename LabelType, typename FeatureType>
		FeatureType chiSquareDistance(std::shared_ptr<DataPoint<LabelType, FeatureType>> point1, std::shared_ptr<DataPoint<LabelType, FeatureType>> point2) {
			throw std::runtime_error("not implemented");
		}
	}
}