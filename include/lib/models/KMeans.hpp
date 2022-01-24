#pragma once

#include <memory>
#include <vector>

#include "lib/models/BaseModel.hpp"

#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	class Cluster {
		public :
			DataPoint<LabelType, FeatureType> centroid;
			std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>> members;
			LabelType identifyMostFrequentLabel();
			void ensureCentroidIsAdjusted();

	};

	template<typename LabelType, typename FeatureType>
	class KMeans : public BaseModel<LabelType, FeatureType> {
		public :
			int k;
			std::vector<Cluster<LabelType, FeatureType>> clusters;
			FeatureType (*distanceCalculationMethod)(const DataPoint<LabelType, FeatureType>&, const DataPoint<LabelType, FeatureType>&);

			KMeans();
			~KMeans();

			void chooseCentroidsAtRanddom();
			void chooseCentroidsUsingKMeansPlusPlus();
			void ensureClustersCentroidsAreAdjusted(const bool& multithreaded = false);
			void ensureClustersMostFrequentLabelIdentified(const bool& multithreaded = false);
			void partition();
		private:
			std::vector<DataPoint<LabelType, FeatureType>> previousCentroids;
	};

}

#include "lib/models/KMeans.cpp"