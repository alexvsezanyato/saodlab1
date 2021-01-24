#pragma once
#include <iostream>
#include <cstdlib>
#include "TreeBox.hpp"

class App {
public:
    static short getRandom(short from, short to) {
    	auto data = std::rand() % (to - from);
    	return data;
    }
    static void printTable(Tree<short int>* tree) {
        std::cout << std::setw(10) << tree->getSize()
            << std::setw(15) << tree->getCheckSum()
            << std::setw(10) << tree->getHeight()
            << std::setw(20) << tree->getAverageHeight()
            << std::endl;
        return;
    }
};
