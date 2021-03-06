#pragma once

#include <memory>

#include "lib/data-handlers/BaseDataHandler.hpp"
#include "lib/models/BaseModel.hpp"

namespace ML {
	template<typename LabelType, typename FeatureType>
	class KNN : public BaseModel<LabelType, FeatureType> {
		typedef DataPoint<LabelType, FeatureType> Data;
		public:
			int k;
			FeatureType (*distanceCalculationMethod)(const Data&, const Data&);

			KNN();
			~KNN();

			LabelType predict(const Data& data);
			std::vector<std::shared_ptr<Data>> getNearestNeighbors(const Data& point);
	};

}

#include "lib/models/KNN.cpp"