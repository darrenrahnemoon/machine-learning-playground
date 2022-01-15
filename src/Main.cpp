#include "entities/DataUnit.hpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"

int main() {
	using namespace ML;

	MNISTDataHandler dataHandler;
	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
}