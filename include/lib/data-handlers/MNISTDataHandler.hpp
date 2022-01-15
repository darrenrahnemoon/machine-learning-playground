#pragma once

#include <string>
#include <vector>
#include "BaseDataHandler.hpp"

namespace ML {
	class MNISTDataHandler: public BaseDataHandler<uint8_t, uint8_t> {
		private:
			FILE* openFile(const std::string& path);
			std::vector<uint32_t> readHeader(FILE* file, const int& size);
		public:
			void readFromFile(std::string featureVectorFilePath, std::string featureLabelFilePath);
	};
};

#include "lib/data-handlers/MNISTDataHandler.cpp"