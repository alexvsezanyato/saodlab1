#pragma once
#include <cstdlib>
#include <bits/stdc++.h>
#include <cmath>

template<class T>
class Tree {
public:
    using Size = unsigned short;
    using Data = T;

    enum Type {
        PerfectlyBalanced,
        SearchOne,
        RandomOne,
        Unknown
    };
    struct Vertex {
        using Data = Tree::Data;
        Data data;
        struct Vertex* left = nullptr;
        struct Vertex* right = nullptr;
    };
    struct Array {
        using Data = Tree::Data;
        using Size = Tree::Size;
        Data* data = nullptr;
        Size size = 0;
    };

private:
    Type treeType = Unknown;
    Vertex* tree = nullptr;
    Size size = 0;

    Vertex* createNode(Data data) {
        Vertex* node = new Vertex{.data = data};
        size++;
        return node;
    }
    Vertex* makePerfectlyBalanced(Array* a, short l, short r) {
        if (l > r) return nullptr;
		short m = (l + r) / 2;
		Vertex* point = createNode(a->data[m]);
		point->left = makePerfectlyBalanced(a, l, m - 1);
		point->right = makePerfectlyBalanced(a, m + 1, r);
		return point;
    }
    void handle(Array* array) {
        switch (treeType) {
        case PerfectlyBalanced:
            std::sort(&array->data[0], &array->data[array->size]);
            this->tree = makePerfectlyBalanced(array, 0, array->size - 1);
            this->size = getSize();
            break;
        }
    }
    static void dropVertex(Vertex* tree) {
        if (!tree) return;
        if (tree->left) dropVertex(tree->left);
        if (tree->right) dropVertex(tree->right);
        delete tree;
        tree = nullptr;
        return;
    }
    void traverseFromLeft(Array* array, Vertex* vertex, short& i) {
        if (!vertex) return;
    	traverseFromLeft(array, vertex->left, i);
        const short position = i++;
        array->data[position] = vertex->data;
    	traverseFromLeft(array, vertex->right, i);
        return;
    }
    void traverseFromRoot(Array* array, Vertex* vertex, short& i) {
        if (!vertex) return;
        const short position = i;
        i++;
        array->data[position] = vertex->data;
    	traverseFromRoot(array, vertex->left, i);
    	traverseFromRoot(array, vertex->right, i);
        return;
    }
    Tree::Size getSize(Tree::Vertex* vertex) {
    	if (!vertex) return 0;
    	return 1 + getSize(vertex->left) + getSize(vertex->right);
    }
    Tree::Size getHeight(Tree::Vertex* i) {
    	if (!i) return 0;
    	return 1 + getMax(getHeight(i->left), getHeight(i->right));
    }
    Tree::Size getAverageHeight(Tree::Vertex* i, short l = 1) {
    	if (!i) return 0;
        auto rightOne = getAverageHeight(i->right, l + 1);
        auto leftOne = getAverageHeight(i->left, l + 1);
    	return l + rightOne + leftOne;
    }
    Tree::Size getCheckSum(Tree::Vertex* i) {
    	if (!i) return 0;
        auto rightOne = getCheckSum(i->left);
        auto leftOne = getCheckSum(i->right);
    	return i->data + rightOne + leftOne;
    }
    bool isSearchOne(Tree::Vertex* vertex) {
        bool searchOne = true;
        if (vertex && vertex->left && (vertex->data < vertex->left->data))
            return false;
        if (vertex->left && !isSearchOne(vertex->left))
            return false;
        if (vertex && vertex->right && (vertex->data > vertex->right->data))
            return false;
        if (vertex->right && !isSearchOne(vertex->right))
            return false;
        return searchOne;
    }
    Vertex* search(Data* data, Vertex* vertex) {
        if (!vertex) return nullptr;
        if (vertex->data == *data) return vertex;
        Vertex* left = nullptr;
        Vertex* right = nullptr;
        if (left = search(data, vertex->left)) return left;
        if (right = search(data, vertex->right)) return right;
        return nullptr;
    }

public:
    Data getMax(Data x, Data y) {
    	if (x > y) return x;
    	return y;
    }
    Tree::Size getHeight() {
        Tree::Size treeHeight = 0;
        treeHeight = getHeight(this->tree);
        return treeHeight;
    }
    Tree::Size getAverageHeight() {
        Tree::Size averageHeight = 0;
        averageHeight = getAverageHeight(this->tree) / getSize();
        return averageHeight;
    }
    Tree::Size getCheckSum() {
        Tree::Size checkSum = 0;
        checkSum = getCheckSum(this->tree);
        return checkSum;
    }
    bool isPerfectlyBalanced() {
        return true;
    }
    Vertex* search(Data data) {
        Vertex* vertex = nullptr;
        if (tree) vertex = search(&data, tree);
        return vertex;
    }
    bool isSearchOne() {
        bool searchOne = false;
        if (tree) searchOne = isSearchOne(tree);
        return searchOne;
    }
    static void printArray(const Tree::Array& array) {
        for (short i = 0; i < array.size; i++)
            std::cout << array.data[i] << ' ';
        return;
    }
    Tree::Array traverseFromLeft() {
        Tree::Size treeSize = this->getSize();
        Tree::Array array{new Data[treeSize], treeSize};
        short position = 0;
        traverseFromLeft(&array, tree, position);
        return array;
    }
    Tree::Array traverseFromRoot() {
        Tree::Size treeSize = this->getSize();
        Tree::Array array{new Data[treeSize], treeSize};
        short position = 0;
        traverseFromRoot(&array, tree, position);
        return array;
    }
    Tree::Size getSize() {
        Tree::Size size = getSize(this->tree);
        return size;
    }
    void setType(Type type) {
        this->treeType = type;
        return;
    }
    Tree(Array array, Tree::Type treeType) {
        setType(treeType);
        handle(&array);
        return;
    }
    ~Tree() {
        if (tree) Tree::dropVertex(tree);
        return;
    }
};
