#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>

namespace ML {
	namespace utils {
		namespace collections {
			template<typename T, typename R>
			using Iterator = R (*)(T& value, int& index, std::vector<T>& collection);

			template <typename T>
			std::vector<T> chooseAtRandom(std::vector<T>& collection,const int& numberOfItemsToChoose, std::unordered_set<int>& excludeIndices) {
				std::vector<T> chosen;
				chosen.reserve(numberOfItemsToChoose);
				int numberOfItemsAllocated = 0;
				while (numberOfItemsAllocated < numberOfItemsToChoose) {
					int randomIndex = rand() % collection.size();
					if (excludeIndices.find(randomIndex) == excludeIndices.end()) {
						chosen.push_back(collection.at(randomIndex));
						excludeIndices.insert(randomIndex);
						numberOfItemsAllocated++;
					}
				}
				return chosen;
			}

			template <typename T>
			std::vector<T> chooseAtRandom(std::vector<T>& collection, const int& numberOfItemsToChoose) {
				std::unordered_set<int> excludeIndices;
				return chooseAtRandom(collection, numberOfItemsToChoose, excludeIndices);
			}

			template <typename T>
			bool every(const std::vector<T>& collection, Iterator<T, bool> iterator) {
				for (int i = 0; i < collection.size(); i++) {
					if (!iterator(collection[i], i, collection)) {
						return false;
					}
				}
				return true;
			}

			template <typename T>
			bool some(const std::vector<T>& collection, Iterator<T, bool> iterator) {
				for (int i = 0; i < collection.size(); i++) {
					if (iterator(collection[i], i, collection)) {
						return true;
					}
				}
				return false;
			}

			template <typename T>
			std::vector<T> filter(const std::vector<T>& collection, Iterator<T, bool> check) {
				std::vector<T> filtered;
				for (int i = 0; i < collection.size(); i++) {
					if (check(collection[i], i, collection)) {
						filtered.push_back(collection[i]);
					}
				}
				return filtered;
			}

			template <typename T, typename K>
			std::vector<K> mapValues(const std::vector<T>& collection, Iterator<T, K> transform) {
				std::vector<K> mapped;
				mapped.reserve(collection.size());
				for (int i = 0; i < collection.size(); i++) {
					mapped.push_back(transform(collection[i], i, collection));
				}
				return mapped;
			}

			template<typename T, typename C>
			std::vector<T> getTop(int numberOfItems, const std::vector<T>& collection, C compare) {
				std::vector<T> result;
				result.resize(numberOfItems);
				std::partial_sort_copy(
					std::begin(collection), std::end(collection),
					std::begin(result), std::end(result),
					compare
				);
				return result;
			}
		}
	}
}