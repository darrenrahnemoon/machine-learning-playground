#include <exception>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <iostream>

#include "lib/debug.cpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"
#include "entities/DataUnit.hpp"

namespace ML {
	using namespace std::string_literals;

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
		debug::timer timer("Reading from vector file "s + featureVectorFilePath + " and label file " + featureLabelFilePath);

		FILE* featureVectorFile = openFile(featureVectorFilePath);
		FILE* featureLabelFile = openFile(featureLabelFilePath);
		std::vector<uint32_t> featureVectorHeader = readHeader(featureVectorFile, 4);
		std::vector<uint32_t> featureLabelHeader = readHeader(featureLabelFile, 2);

		if (featureVectorHeader[FeatureVectorHeader["NumberOfImages"]] != featureLabelHeader[FeatureLabelHeader["NumberOfLabels"]]) {
			throw std::runtime_error("Number of images in the header of feature vector file does not match the number of labels in the header of feature elabel file");
		}

		uint8_t pixel;
		uint32_t imageSize = featureVectorHeader[FeatureVectorHeader["RowSize"]] * featureVectorHeader[FeatureVectorHeader["ColumnSize"]];

		for (int imageIndex = 0; imageIndex < featureVectorHeader[FeatureVectorHeader["NumberOfImages"]]; imageIndex++) {
			auto data = std::make_shared<DataUnit<uint8_t, uint8_t>>();

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

			debug::log::low(
				"Image:", imageIndex,
				"Label:", data->label,
				"Pixel length: ", data->featureVector->size()
			);
		}
	}

	FILE* MNISTDataHandler::openFile(const std::string& path) {
		debug::timer timer("Opening file: "s + path);
		FILE* file = fopen(path.c_str(), "rb");
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
			this->swapEndian(header[i]);
			debug::log::low("Reading Header", i);
			debug::log::low("Value", header[i]);
		}
		return header;
	}

	template <typename T>
	void MNISTDataHandler::swapEndian(T &value) {
		union U {
			T value;
			std::array<uint8_t, sizeof(T)> raw;
		} src, dst;

		src.value = value;
		std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
		value = dst.value;
	}
}