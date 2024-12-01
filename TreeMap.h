#pragma once
#include "BinaryTree.h"
#include <stdexcept>

template <typename K, typename V>
class TreeMap {
private:
    BinaryTree<std::pair<K, V>> tree; // Store key-value pairs in BinaryTree

public:
    // Clears all elements from the TreeMap
    void clear() {
        tree.clear();
    }

    // Checks if the TreeMap contains the specified key
    bool containsKey(const K& key) const {
        try {
            get(key); // Attempt to find the key
            return true;
        }
        catch (const std::logic_error&) {
            return false;
        }
    }

    // Retrieves the value associated with the specified key
    V get(const K& key) const {
        std::pair<K, V> searchPair(key, V()); // Create dummy pair
        return tree.get(searchPair).second;   // Return the value corresponding to the key
    }

    // Adds or updates a key-value pair in the TreeMap
    void put(const K& key, const V& value) {
        std::pair<K, V> newPair(key, value);
        if (containsKey(key)) {
            removeKey(key); // Remove old pair if key exists
        }
        tree.add(newPair); // Add the new pair
    }

    // Retrieves all keys in the TreeMap
    BinaryTree<K> keySet() const {
        BinaryTree<K> keys;
        auto allPairs = tree.toArray();
        int size = tree.count();
        for (int i = 0; i < size; ++i) {
            keys.add(allPairs[i].first); // Extract keys
        }
        delete[] allPairs; // Clean up array
        return keys;
    }

    // Returns the number of key-value pairs in the TreeMap
    int size() const {
        return tree.count();
    }

    // Removes the key-value pair with the specified key
    bool removeKey(const K& key) {
        if (!containsKey(key)) return false;
        std::pair<K, V> removePair(key, V());
        return tree.remove(removePair);
    }

    // Array-style access to values
    V& operator[](const K& key) {
        if (!containsKey(key)) {
            put(key, V()); // Insert default value if key doesn't exist
        }
        return const_cast<V&>(get(key));
    }
};
