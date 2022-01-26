#include <exception>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>

#include "lib/utils/timer.cpp"
#include "lib/utils/log.cpp"
#include "lib/utils/endian.cpp"
#include "lib/utils/file.cpp"

#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "entities/DataPoint.hpp"

namespace ML {
	std::map<std::string, int> FeatureVectorHeader = {
		{ "MagicNumber", 0 },
		{ "NumberOfImages", 1 },
		{ "RowSize", 2 },
		{ "ColumnSize", 3}
	};

	std::map<std::string, int> FeatureLabelHeader = {
		{ "MagicNumber", 0 },
		{ "NumberOfLabels", 1 }
	};

	void MNISTDataHandler::readFromFile(std::string featureVectorFilePath, std::string featureLabelFilePath) {
		using namespace std::string_literals;
		utils::timer timer("Reading from vector file "s + featureVectorFilePath + " and label file " + featureLabelFilePath);

		FILE* featureVectorFile = file::open(featureVectorFilePath);
		FILE* featureLabelFile = file::open(featureLabelFilePath);
		std::vector<uint32_t> featureVectorHeader = readHeader(featureVectorFile, 4);
		std::vector<uint32_t> featureLabelHeader = readHeader(featureLabelFile, 2);

		if (featureVectorHeader[FeatureVectorHeader["NumberOfImages"]] != featureLabelHeader[FeatureLabelHeader["NumberOfLabels"]]) {
			throw std::runtime_error("Number of images in the header of feature vector file does not match the number of labels in the header of feature elabel file");
		}

		this->dataset = std::make_shared<Dataset<uint8_t, uint8_t>>();

		uint8_t pixel;
		uint32_t imageSize = featureVectorHeader[FeatureVectorHeader["RowSize"]] * featureVectorHeader[FeatureVectorHeader["ColumnSize"]];

		for (int imageIndex = 0; imageIndex < featureVectorHeader[FeatureVectorHeader["NumberOfImages"]]; imageIndex++) {
			auto data = std::make_shared<DataPoint<uint8_t, uint8_t>>();

			// Get the label for the DataPoint from the feature label file
			fread(&(data->label), sizeof(uint8_t), 1, featureLabelFile);

			// Get the pixel values for the DataPoint from the feature vector file
			for (int pixelIndex = 0; pixelIndex < imageSize; pixelIndex++) {
				if (!fread(&pixel, sizeof(uint8_t), 1, featureVectorFile)) {
					throw std::runtime_error(
						"Failed to read pixel"s
						+ std::to_string(pixelIndex)
						+ " from image " 
						+ std::to_string(imageIndex)
					);
				}
				data->featureVector.push_back(pixel);
			}
			this->dataset->push_back(data);

			utils::log::low(
				"Image:", imageIndex,
				"Label:", data->label,
				"Pixel length: ", data->featureVector.size()
			);
		}
	}

	std::vector<uint32_t> MNISTDataHandler::readHeader(FILE* file, const int& size) {
		std::vector<uint32_t> header(size);
		for (int i = 0; i < size; i++) {
			if (!fread(&header[i], sizeof(uint32_t), 1, file)) {
				throw std::runtime_error("Cannot read header");
			}
			utils::swapEndian(header[i]);
			utils::log::low("Reading Header", i);
			utils::log::low("Value", header[i]);
		}
		return header;
	}
}