#include <string>
#include <exception>
#include <vector>

#include "lib/logger.hpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "entities/DataUnit.hpp"

namespace ML {
	using namespace std::string_literals;

	enum HeaderInformation {
		MagicNumber = 0,
		NumberOfImages = 1,
		NumberOfLabels = 1,
		RowSize = 2,
		ColumnSize = 3
	};

	FILE* MNISTDataHandler::openFile(const std::string& path) {
		FILE* file = fopen(path.c_str(), "r");
		if (!file) {
			throw std::runtime_error("Cannot read file:"s + path);
		}
		return file;
	}

	std::vector<uint32_t> MNISTDataHandler::readHeader(FILE* file, const int& size) {
		std::vector<uint32_t> header(size);
		for (int i = 0; i < size; i++) {
			if (!fread(&header[i], sizeof(uint32_t), 1, file)) {
				throw std::runtime_error("Cannot read header");
			}
		}
		return header;
	}

	void MNISTDataHandler::readFromFile(std::string featureVectorFilePath, std::string featureLabelFilePath) {
		FILE* featureVectorFile = openFile(featureVectorFilePath);
		FILE* featureLabelFile = openFile(featureLabelFilePath);
		std::vector<uint32_t> featureVectorHeader = readHeader(featureVectorFile, 4);
		std::vector<uint32_t> featureLabelHeader = readHeader(featureLabelFile, 2);

		if (featureVectorHeader[NumberOfImages] != featureLabelHeader[NumberOfLabels]) {
			throw std::runtime_error("Number of images in the header of feature vector file does not match the number of labels in the header of feature elabel file");
		}

		uint8_t pixel;
		int imageSize = featureVectorHeader[RowSize] * featureVectorHeader[ColumnSize];
		for (int imageIndex = 0; imageIndex < featureVectorHeader[NumberOfImages]; imageIndex++) {

			DataUnit<uint8_t, uint8_t>* data;

			// Get the label for the DataUnit from the feature label file
			fread(&(data->label), sizeof(uint8_t), 1, featureLabelFile);

			// Get the pixel values for the DataUnit from the feature vector file
			for (int pixelIndex = 0; pixelIndex < imageSize; pixelIndex++) {
				if (!fread(&pixel, sizeof(uint8_t), 1, featureVectorFile)) {
					throw std::runtime_error(
						"Failed to read pixel"s
						+ std::to_string(pixelIndex)
						+ " from image " 
						+ std::to_string(imageIndex)
					);
				}
				data->featureVector->push_back(pixel);
			}

			this->rawData->push_back(data);
		}

	}
}