#include <vector>
#include <unordered_set>

namespace ML {
	namespace utils {
		namespace collections {
			template <typename T>
			void allocateAtRandom(std::vector<T>& source, std::vector<T>& dest, int numberOfItemsToAllocate, std::unordered_set<int>& excludeIndices) {
				int numberOfItemsAllocated = 0;
				while (numberOfItemsAllocated < numberOfItemsToAllocate) {
					int randomIndex = rand() % source.size();
					if (excludeIndices.find(randomIndex) == excludeIndices.end()) {
						dest.push_back(source.at(randomIndex));
						excludeIndices.insert(randomIndex);
						numberOfItemsAllocated++;
					}
				}
			}

			template <typename T>
			void allocateAtRandom(const std::vector<T>& source, const std::vector<T>& dest, const int& numberOfItemsToAllocate) {
				std::unordered_set<int> excludeIndices;
				allocateAtRandom(source, dest, numberOfItemsToAllocate, excludeIndices);
			}
		}
	}
}