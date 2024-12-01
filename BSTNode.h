#pragma once

#include <iostream>

template <class T>
class BSTNode {
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;
    T data;

public:
    BSTNode();
    BSTNode(T data);
    BSTNode(const BSTNode<T>& other);
    BSTNode<T>& operator=(const BSTNode<T>& other);
    ~BSTNode();

    void setItem(const T& item);
    const T& getItem() const;
    BSTNode<T>* getLeft() const;
    BSTNode<T>* getRight() const;
    void setLeft(BSTNode<T>* l);
    void setRight(BSTNode<T>* r);

    int count() const;
    void add(const T& item);
};

template <class T>
BSTNode<T>::BSTNode() : parent(nullptr), left(nullptr), right(nullptr) {}

template <class T>
BSTNode<T>::BSTNode(T data) : parent(nullptr), left(nullptr), right(nullptr), data(data) {}

template <class T>
BSTNode<T>::BSTNode(const BSTNode<T>& other) : parent(nullptr), left(nullptr), right(nullptr), data(other.data) {
    if (other.left) this->left = new BSTNode<T>(*other.left);
    if (other.right) this->right = new BSTNode<T>(*other.right);
}

template <class T>
BSTNode<T>& BSTNode<T>::operator=(const BSTNode<T>& other) {
    if (this == &other) return *this;

    delete left;
    delete right;

    left = right = nullptr;
    data = other.data;

    if (other.left) left = new BSTNode<T>(*other.left);
    if (other.right) right = new BSTNode<T>(*other.right);

    return *this;
}

template <class T>
BSTNode<T>::~BSTNode() {
    delete left;
    delete right;
}

template <class T>
void BSTNode<T>::setItem(const T& item) {
    data = item;
}

template <class T>
const T& BSTNode<T>::getItem() const {
    return data;
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft() const {
    return left;
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight() const {
    return right;
}

template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* l) {
    left = l;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* r) {
    right = r;
}

template <class T>
int BSTNode<T>::count() const {
    int c = 1;
    if (left) c += left->count();
    if (right) c += right->count();
    return c;
}

template <class T>
void BSTNode<T>::add(const T& item) {
    if (item == data) return; // Avoid duplicates
    if (item < data) {
        if (!left) {
            left = new BSTNode<T>(item);
            left->parent = this;
        }
        else {
            left->add(item);
        }
    }
    else {
        if (!right) {
            right = new BSTNode<T>(item);
            right->parent = this;
        }
        else {
            right->add(item);
        }
    }
}

