#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "BinaryTree.h"
#include "TreeMap.h"
#include "NBA.h"

void displayMainMenu();
void displayTextMenu(const std::vector<std::string>& words);
void displayCsvMenu(const std::vector<std::vector<std::string>>& csvData);
std::vector<std::string> loadTextFile(const std::string& filename);
std::vector<std::vector<std::string>> loadCsvFile(const std::string& filename);
void displayLetters(const std::vector<std::string>& words);
void searchWordsByLetter(const std::vector<std::string>& words);
void displayAllCsvData(const std::vector<std::vector<std::string>>& csvData);
void searchCsvByColumn(const std::vector<std::vector<std::string>>& csvData);

int main() {
    // Load data from files
    std::vector<std::string> words = loadTextFile("sample_text.txt");
    std::vector<std::vector<std::string>> csvData = loadCsvFile("NBA_Player_Stats.csv");

    if (words.empty() || csvData.empty()) {
        std::cerr << "Error: Failed to load files. Ensure both files are available." << std::endl;
        return 1;
    }

    int choice = -1;
    while (choice != 0) {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayTextMenu(words);
            break;
        case 2:
            displayCsvMenu(csvData);
            break;
        case 0:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}

void displayMainMenu() {
    std::cout << "\nMain Menu:" << std::endl;
    std::cout << "1. Text File Menu" << std::endl;
    std::cout << "2. CSV File Menu" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter choice: ";
}

void displayTextMenu(const std::vector<std::string>& words) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\nText File Menu:" << std::endl;
        std::cout << "1. Display all available letters" << std::endl;
        std::cout << "2. Search words by letter" << std::endl;
        std::cout << "0. Return to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayLetters(words);
            break;
        case 2:
            searchWordsByLetter(words);
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void displayCsvMenu(const std::vector<std::vector<std::string>>& csvData) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\nCSV File Menu:" << std::endl;
        std::cout << "1. Display all data" << std::endl;
        std::cout << "2. Search data by column" << std::endl;
        std::cout << "0. Return to Main Menu" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayAllCsvData(csvData);
            break;
        case 2:
            searchCsvByColumn(csvData);
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

std::vector<std::string> loadTextFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;

    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "!" << std::endl;
        return words;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

std::vector<std::vector<std::string>> loadCsvFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;

    if (!file) {
        std::cerr << "Error: Unable to open " << filename << "!" << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

void displayLetters(const std::vector<std::string>& words) {
    std::vector<char> letters;
    for (const std::string& word : words) {
        char firstLetter = tolower(word[0]);
        if (std::find(letters.begin(), letters.end(), firstLetter) == letters.end()) {
            letters.push_back(firstLetter);
        }
    }

    std::cout << "Available letters: ";
    for (char letter : letters) {
        std::cout << letter << " ";
    }
    std::cout << std::endl;
}

void searchWordsByLetter(const std::vector<std::string>& words) {
    char letter;
    std::cout << "Enter a letter: ";
    std::cin >> letter;
    letter = tolower(letter);

    bool found = false;
    std::cout << "Words starting with '" << letter << "': ";
    for (const std::string& word : words) {
        if (tolower(word[0]) == letter) {
            std::cout << word << " ";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No words found for the letter: " << letter;
    }
    std::cout << std::endl;
}

void displayAllCsvData(const std::vector<std::vector<std::string>>& csvData) {
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

void searchCsvByColumn(const std::vector<std::vector<std::string>>& csvData) {
    int column;
    std::string value;

    if (csvData.empty() || csvData[0].empty()) {
        std::cerr << "CSV data is empty or invalid!" << std::endl;
        return;
    }

    std::cout << "Enter column index (0 to " << csvData[0].size() - 1 << "): ";
    std::cin >> column;

    if (column < 0 || column >= csvData[0].size()) {
        std::cerr << "Invalid column index!" << std::endl;
        return;
    }

    std::cout << "Enter value to search: ";
    std::cin >> value;

    bool found = false;
    for (const auto& row : csvData) {
        if (row[column] == value) {
            for (const auto& cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching data found." << std::endl;
    }
}
