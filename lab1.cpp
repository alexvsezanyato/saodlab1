#include <iostream>
#include <cstdlib>
#include "TreeBox.hpp"
#include "App.hpp"

int main() {
    App app;
    using Size = unsigned short;

    using C = char;
    Size arraySize = 12;

    C* chars = new C[arraySize]{
        'a', 'l', 'e', 'x', 'n', 'd', 'r',
        'b', 'o', 'v', 'y', 'c'
    };
    Tree<C> charsTree(
        Tree<C>::Array{chars, arraySize},
        Tree<C>::PerfectlyBalanced
    );
    std::cout << "Chars tree[" << arraySize << "]: ";
    Tree<C>::Array traversedCharsTree = charsTree.traverseFromRoot();
    Tree<C>::printArray(traversedCharsTree);
    std::cout << std::endl;
    delete [] traversedCharsTree.data;

    C Crequest = 'a';
    std::cout << "Search result (" << Crequest << "): ";

    auto Cresponse = charsTree.search(Crequest);
    if (Cresponse) std::cout << Cresponse->data << std::endl;
    else std::cout << "not found" << std::endl;

    Crequest = 'm';
    std::cout << "Search result (" << Crequest << "): ";
    Cresponse = charsTree.search(Crequest);
    if (Cresponse) std::cout << Cresponse->data << std::endl;
    else std::cout << "not found" << std::endl;

    std::cout << "Search tree: " << charsTree.isSearchOne() << std::endl
        << "Size: " << charsTree.getSize() << std::endl
        << "Check sum: " << charsTree.getCheckSum() << std::endl
        << "Height: " << charsTree.getHeight() << std::endl
        << "Average height: " << charsTree.getAverageHeight() << std::endl;
    std::cout << std::endl;

    delete [] chars;
    chars = nullptr;
    arraySize = 0;

    using S = short;
    arraySize = 10;
    S* numbers = new S[arraySize];
    for (Size i = 0; i < arraySize; i++)
        numbers[i] = App::getRandom(10, 99);

    std::cout << "Array: ";
    Tree<S>::printArray(Tree<S>::Array{numbers, arraySize});
    std::cout << std::endl;

    Tree<S> numbersTree(
        Tree<S>::Array{numbers, arraySize},
        Tree<S>::PerfectlyBalanced
    );
    std::cout << "Perfectly balanced numbers tree[" << arraySize << "]: ";
    Tree<S>::Array traversedFromLeft = numbersTree.traverseFromLeft();
    Tree<S>::printArray(traversedFromLeft);
    std::cout << std::endl;
    delete [] traversedFromLeft.data;
    std::cout << "Search tree: " << numbersTree.isSearchOne() << std::endl;

    delete [] numbers;
    numbers = nullptr;
    arraySize = 0;
    std::cout << std::endl;

    std::cout << std::setw(10) << "Size"
        << std::setw(15) << "Check sum"
        << std::setw(10) << "Height"
        << std::setw(20) << "Average height"
        << std::endl;

    const Size tableHeight = 5;
    Tree<S>* tree[tableHeight];

    for (Size i = 0; i < tableHeight; i++) {
        S* nodes = new S[(i + 1) * 100];
        for (Size j = 0; j < (i + 1) * 100; j++)
            nodes[j] = App::getRandom(10, 99);
        Size arraySize = (i + 1) * 100;

        tree[i] = new Tree<S>(
            Tree<S>::Array{nodes, arraySize},
            Tree<S>::PerfectlyBalanced
        );
        App::printTable(tree[i]);
        delete [] nodes;

    }

    std::cout << "Do you want to see the trees? (y / n): ";
    char* answer;
    std::cin >> answer;

    switch (answer[0]) {
    case 'y':
        for (Size i = 0; i < tableHeight; i++) {
            std::cout << "Tree[" << i << "]: \n";
            auto traversedTree = tree[i]->traverseFromLeft();
            Tree<short int>::printArray(traversedTree);
            std::cout << std::endl << "End \n";
            delete [] traversedTree.data;
        }
        break;
    case 'n':
        break;
    }

    for (Size i = 0; i < tableHeight; i++) {
        delete tree[i];
    }
    return 0;
}
