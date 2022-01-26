#pragma once

#include <memory>

#include "lib/data-handlers/BaseDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	class BaseModel {
		public :
			SharedDataset<LabelType, FeatureType> dataset;
	};

}