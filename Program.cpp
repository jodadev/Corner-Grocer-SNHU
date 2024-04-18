// Edwin J. Martinez
#include "./header/ItemTracker.h"
#include <iostream>
#include <limits>
#include <string>

/**
 * @brief Displays a menu with options to search for an item's frequency, 
 * display all frequencies, show a histogram of frequencies, or exit the program.
 */
void displayMenu() {
    std::cout << "\nCorner Grocer Item Tracking\n";
    std::cout << "1. Search Item Frequency\n";
    std::cout << "2. Display All Item Frequencies\n";
    std::cout << "3. Display Histogram of Item Frequencies\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

/**
 * @brief Get the Validated Input object. Bounds to the min and max choices
 * available. Clears and ignores anything outside the bounds.
 * 
 * @param min Min bound.
 * @param max Max bound.
 * @return Choice type int.
 */
int getValidatedInput(int min, int max) {
    int choice;
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

/**
 * @brief Program entry point.
 * 
 * @return int 
 */
int main() {
    ItemTracker tracker;
    int choice;
    std::string inputFilePath = "CS210_Project_Three_Input_File.txt";
    std::string backupFilePath = "frequency.dat";

    // Attempt to load data and create backup at startup
    try {
        tracker.loadData(inputFilePath);
        tracker.writeBackup(backupFilePath);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        system("pause"); // prevent closing program until user presses key.
        return 0;
    }

    do {
        displayMenu();
        choice = getValidatedInput(1, 4);

        switch (choice) {
            case 1: {
                std::string item;
                std::cout << "Enter item name to search: ";
                std::cin >> item;
                std::cout << "\n\tResponse ->> Frequency: " << tracker.findItemFrequency(item) << std::endl;
                break;
            }
            case 2:
                tracker.printAllFrequencies();
                break;
            case 3:
                tracker.printHistogram();
                break;
            case 4:
                std::cout << "***[Exiting program]***\n";
                break;
            default:
                std::cerr << "***[[Unknown error has occurred.]]***" << std::endl;
        }
    } while (choice != 4);

    return 0;
}
