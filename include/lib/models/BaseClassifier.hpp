#pragma once

#include <memory>

#include "entities/DataPoint.hpp"

namespace ML {

	template<typename LabelType, typename FeatureType>
	class BaseModel {
		public : 
			std::shared_ptr<std::vector<std::shared_ptr<DataPoint<LabelType, FeatureType>>>> dataset;
	};

}