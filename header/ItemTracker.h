// Edwin J. Martinez
#ifndef ITEMTRACKER_H
#define ITEMTRACKER_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies; // Stores items and their purchase frequencies.
    void capitalizeFirstLetter(std::string& word); // Ensure query works with lower case inputs for first letter
public:
    void loadData(const std::string& filePath); // Loads data from the specified file.
    void writeBackup(const std::string& backupPath); // Writes the item frequencies to a backup file.
    int findItemFrequency(std::string& query); // Returns the frequency of the specified item.
    void printAllFrequencies() const; // Prints the frequencies of all items.
    void printHistogram() const; // Prints a histogram of item frequencies.
};

#endif
