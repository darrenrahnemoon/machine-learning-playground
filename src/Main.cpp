#include <iostream>

#include "lib/debug.cpp"
#include "entities/DataUnit.hpp"
#include "lib/data-handlers/BaseDataHandler.hpp"
#include "lib/data-handlers/MNISTDataHandler.hpp"

int main() {
	debug::timer timer("Main");

	ML::MNISTDataHandler dataHandler;
	dataHandler.readFromFile("../assets/mnist/train-images-idx3-ubyte", "../assets/mnist/train-labels-idx1-ubyte");
	dataHandler.allocateDataAtRandom();
}