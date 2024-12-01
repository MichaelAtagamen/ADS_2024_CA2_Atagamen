#pragma once
#include "BSTNode.h"
#include <stdexcept>

template <class T>
class BinaryTree {
private:
    BSTNode<T>* root;

    void addItemToArray(const BSTNode<T>* node, int& pos, T* arr) const;
    void clearHelper(BSTNode<T>* node);

    // Helper function for size
    int sizeHelper(const BSTNode<T>* node) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    ~BinaryTree();

    void add(const T& item);
    bool remove(const T& item); // Not yet implemented
    const T& get(const T& item) const;
    void clear();

    int count() const;
    int size() const; // New size method
    T* toArray() const;

    BinaryTree<T>& operator=(const BinaryTree<T>& other);

    // Overload operator==
    bool operator==(const BinaryTree<std::string>& other) const {
        return this->size() == other.size(); // Compare sizes
    }

    // Overload operator<
    bool operator<(const BinaryTree<std::string>& other) const {
        return this->size() < other.size(); // Compare sizes
    }

    // Static comparison function
    static bool compare(const BinaryTree<std::string>& left, const BinaryTree<std::string>& right) {
        return left.size() < right.size(); // Compare sizes
    }
};

// Constructor
template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

// Copy Constructor
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) : root(nullptr) {
    if (other.root) {
        root = new BSTNode<T>(*other.root);
    }
}

// Destructor
template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

// Clear the tree
template <class T>
void BinaryTree<T>::clear() {
    clearHelper(root);
    root = nullptr;
}

template <class T>
void BinaryTree<T>::clearHelper(BSTNode<T>* node) {
    if (node) {
        clearHelper(node->getLeft());
        clearHelper(node->getRight());
        delete node;
    }
}

// Add a node
template <class T>
void BinaryTree<T>::add(const T& item) {
    if (!root) {
        root = new BSTNode<T>(item);
    }
    else {
        root->add(item);
    }
}

// Remove a node (not implemented)
template <class T>
bool BinaryTree<T>::remove(const T& item) {
    return false; // Placeholder for removal logic
}

// Get an item
template <class T>
const T& BinaryTree<T>::get(const T& item) const {
    BSTNode<T>* current = root;
    while (current) {
        if (item == current->getItem()) return current->getItem();
        current = (item < current->getItem()) ? current->getLeft() : current->getRight();
    }
    throw std::logic_error("Item not found");
}

// Count nodes
template <class T>
int BinaryTree<T>::count() const {
    return root ? root->count() : 0;
}

// Get size of the tree
template <class T>
int BinaryTree<T>::size() const {
    return sizeHelper(root);
}

template <class T>
int BinaryTree<T>::sizeHelper(const BSTNode<T>* node) const {
    if (!node) return 0;
    return 1 + sizeHelper(node->getLeft()) + sizeHelper(node->getRight());
}

// Convert to array
template <class T>
T* BinaryTree<T>::toArray() const {
    int size = count();
    T* arr = new T[size];
    int pos = 0;
    addItemToArray(root, pos, arr);
    return arr;
}

template <class T>
void BinaryTree<T>::addItemToArray(const BSTNode<T>* node, int& pos, T* arr) const {
    if (node) {
        addItemToArray(node->getLeft(), pos, arr);
        arr[pos++] = node->getItem();
        addItemToArray(node->getRight(), pos, arr);
    }
}

// Assignment operator
template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this != &other) {
        clear();
        if (other.root) {
            root = new BSTNode<T>(*other.root);
        }
    }
    return *this;
}
