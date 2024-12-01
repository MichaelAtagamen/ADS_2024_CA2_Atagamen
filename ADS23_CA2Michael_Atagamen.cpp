#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>  // For std::tolower
#include <string>
#include "TreeMap.h"
#include "BinaryTree.h"

// Function to load words from a TXT file
void loadWordsFromFile(const std::string& filename, TreeMap<char, BinaryTree<std::string>>& letterMap) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        if (!word.empty()) {
            char firstLetter = std::tolower(word[0]); // Ensure case insensitivity
            if (std::isalpha(firstLetter)) { // Only process alphabetic characters
                if (!letterMap.containsKey(firstLetter)) {
                    letterMap.put(firstLetter, BinaryTree<std::string>()); // Create a new BinaryTree for the letter
                }
                letterMap.get(firstLetter).add(word); // Add the word to the BinaryTree for the letter
            }
        }
    }
}

// Function to load words from a CSV file
void loadWordsFromCSV(const std::string& filename, TreeMap<char, BinaryTree<std::string>>& letterMap, int columnIndex) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) { // Read each line of the CSV
        std::stringstream ss(line);
        std::string cell;
        int currentIndex = 0;
        std::string word;

        while (std::getline(ss, cell, ',')) { // Split by commas
            if (currentIndex == columnIndex) {
                word = cell; // Extract the required column
                break;
            }
            currentIndex++;
        }

        if (!word.empty()) {
            char firstLetter = std::tolower(word[0]); // Ensure case insensitivity
            if (std::isalpha(firstLetter)) {         // Only process alphabetic characters
                if (!letterMap.containsKey(firstLetter)) {
                    letterMap.put(firstLetter, BinaryTree<std::string>()); // Create a new BinaryTree for the letter
                }
                letterMap.get(firstLetter).add(word); // Add the word to the BinaryTree for the letter
            }
        }
    }
}

// Function to display words for a given letter
void displayWordsForLetter(const TreeMap<char, BinaryTree<std::string>>& letterMap, char letter) {
    if (letterMap.containsKey(letter)) {
        const BinaryTree<std::string>& wordsTree = letterMap.get(letter);
        auto wordsArray = wordsTree.toArray(); // Assuming you have a toArray() method in BinaryTree
        int wordCount = wordsTree.count();     // Number of words
        if (wordCount > 0) {
            std::cout << "Words under letter '" << letter << "':" << std::endl;
            for (int i = 0; i < wordCount; ++i) {
                std::cout << wordsArray[i] << std::endl;
            }
            delete[] wordsArray; // Clean up dynamic array
        }
        else {
            std::cout << "No words found for the letter: " << letter << std::endl;
        }
    }
    else {
        std::cout << "No words found for the letter: " << letter << std::endl;
    }
}

// Function to display available letters
void displayAvailableLetters(const TreeMap<char, BinaryTree<std::string>>& letterMap) {
    std::cout << "Available letters in the map:" << std::endl;
    auto keysTree = letterMap.keySet();        // Assuming keySet() returns a BinaryTree<char>
    auto keysArray = keysTree.toArray();       // Convert to array
    int keyCount = keysTree.count();           // Number of keys
    for (int i = 0; i < keyCount; ++i) {
        std::cout << keysArray[i] << " ";      // Print each letter
    }
    delete[] keysArray;                        // Clean up dynamic array
    std::cout << std::endl;
}

int main() {
    TreeMap<char, BinaryTree<std::string>> letterMap;
    std::string txtFilename = "sample_text.txt"; // Replace with your TXT file name
    std::string csvFilename = "NBA_Player_Stats.csv"; // Replace with your CSV file name
    int csvColumnIndex = 1;                      // Column index to extract words from (starting from 0)

    // Initial menu to process files
    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Process TXT file\n";
    std::cout << "2. Process SV file\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        // Process TXT file
        loadWordsFromFile(txtFilename, letterMap);
        std::cout << "\nTXT file processed successfully.\n";
    }
    else if (choice == 2) {
        // Process CSV file
        loadWordsFromCSV(csvFilename, letterMap, csvColumnIndex);
        std::cout << "\nCSV file processed successfully.\n";
    }
    else {
        std::cout << "Invalid choice. Exiting program.\n";
        return 1;
    }

    // Main menu loop
    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Display available letters\n";
        std::cout << "2. Display words for a specific letter\n";
        std::cout << "0. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }

        switch (choice) {
        case 1:
            displayAvailableLetters(letterMap);
            break;
        case 2: {
            char inputLetter;
            std::cout << "Enter a letter to display words: ";
            std::cin >> inputLetter;
            inputLetter = std::tolower(inputLetter); // Convert to lowercase for consistency
            if (std::isalpha(inputLetter)) {
                displayWordsForLetter(letterMap, inputLetter);
            }
            else {
                std::cout << "Invalid input. Please enter a letter." << std::endl;
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
