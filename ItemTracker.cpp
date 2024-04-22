// Edwin J. Martinez
#include "./header/ItemTracker.h"

/**
 * @brief Takes a string value and ensures the first character is capitalized.
 * Accepts a reference and replaces the first letter with capital, no need for return.
 * 
 * @param word Word to check.
 */
void ItemTracker::capitalizeFirstLetter(std::string& word) {
    // Capitalize the first letter
    if (!word.empty()) {
        word[0] = toupper(word[0]);
    }  
}

/**
 * @brief Loads data from .txt file, inserts each record into map and
 * increments the frequency of a record from the entire file as value.
 * Validates: one word per line - this means the file should adhere to 
 * this rule, if not, an error will be thrown.
 * 
 * @param filePath Path to file for records.
 */
void ItemTracker::loadData(const std::string& filePath) {
    std::ifstream inFile(filePath);
    std::string line;

    // Validate that the file is open
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    // The file is structured with each line containing an item name.
    // Each occurrence of an item name increments its frequency in the map.
    while (std::getline(inFile, line)) {
        // Use a stringstream to check if the line consists of exactly one word.
        std::istringstream iss(line);
        std::string item;
        iss >> item; // Attempt to read the first word and store in string.

        if (!item.empty() && iss.eof()) { // Check if there's exactly one word. Must not be empty and reached end of line.
            itemFrequencies[item] += 1; // Increment the frequency of the item.
        } else if (!item.empty()) { // Line has more than one word or unexpected content.
            inFile.close(); // Clean up i/o before throwing.
            std::string secondWord;
            iss >> secondWord; // Get the second word to display in error message
            throw std::runtime_error("Invalid content in file: " + filePath + ". Expected one item per line, got two: " + item + " " + secondWord);
        }
        // Possible: If item.empty() is true, it's a blank line, and we simply ignore it.
    }

    inFile.close();
}

/**
 * @brief Writes a backup of the map data (item:freq) to a .bat file.
 * 
 * @param backupPath Path to save file.
 */
void ItemTracker::writeBackup(const std::string& backupPath) {
    std::ofstream outFile(backupPath);
    
    // Validate we opened file
    if (!outFile) {
        throw std::runtime_error("Unable to create backup file: " + backupPath);
    }

    // Iterate through map and record each pair to the file, end line.
    for (const auto& pair : itemFrequencies) {
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
}

/**
 * @brief Finds the frequency based on the passed query and returns it as integer.
 * 
 * @param query Search query string for item.
 * @return Frequency as type integer.
 */
int ItemTracker::findItemFrequency(std::string& query) {
    
    // Ensure the query's first letter is capital
    capitalizeFirstLetter(query);

    auto it = itemFrequencies.find(query); // Attempt it get iterator
    // Return freq only if the iterator returned is not the end iterator(empty)
    if (it != itemFrequencies.end()) {
        return it->second;
    } else {
        return 0; // Item not found
    }
}

/**
 * @brief Prints all items(keys) in map with their associated frequencies(value).
 * 
 */
void ItemTracker::printAllFrequencies() const {
    std::cout << "\nResponse ->> " << std::endl;
    for (const auto& pair : itemFrequencies) {
        std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
    }
}

/**
 * @brief Prints all items(keys) in map with their associated frequencies(value)
 * as astrid(*).
 * 
 */
void ItemTracker::printHistogram() const {
    std::cout << "\nResponse ->> " << std::endl;
    for (const auto& pair : itemFrequencies) {
        std::cout << "\t" << std::left << std::setw(12) << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}