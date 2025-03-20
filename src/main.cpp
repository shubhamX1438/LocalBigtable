#include <iostream>
#include <limits>
#include "bigtable.h"

void DisplayMenu() {
    std::cout << "\n===== Local Bigtable Simulation =====\n";
    std::cout << "1. Insert/Update Cell\n";
    std::cout << "2. Get Row\n";
    std::cout << "3. Delete Row\n";
    std::cout << "4. Delete Cell\n";
    std::cout << "5. Scan Table\n";
    std::cout << "6. Save Table to File\n";
    std::cout << "7. Load Table from File\n";
    std::cout << "8. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    Bigtable myTable;
    int choice = 0;
    std::string rowKey, column, value, filename;

    while (true) {
        DisplayMenu();
        std::cin >> choice;

        // Clear newline from input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter row key: ";
                std::getline(std::cin, rowKey);
                std::cout << "Enter column: ";
                std::getline(std::cin, column);
                std::cout << "Enter value: ";
                std::getline(std::cin, value);
                myTable.InsertCell(rowKey, column, value);
                std::cout << "Cell inserted/updated.\n";
                break;
            case 2: {
                std::cout << "Enter row key to get: ";
                std::getline(std::cin, rowKey);
                Row row;
                if (myTable.GetRow(rowKey, row)) {
                    std::cout << "Data for row '" << rowKey << "':\n";
                    for (auto &cell : row) {
                        std::cout << "  " << cell.first << ": " << cell.second.value << "\n";
                    }
                } else {
                    std::cout << "Row '" << rowKey << "' not found.\n";
                }
                break;
            }
            case 3:
                std::cout << "Enter row key to delete: ";
                std::getline(std::cin, rowKey);
                if (myTable.DeleteRow(rowKey)) {
                    std::cout << "Row '" << rowKey << "' deleted.\n";
                } else {
                    std::cout << "Row '" << rowKey << "' not found.\n";
                }
                break;
            case 4:
                std::cout << "Enter row key: ";
                std::getline(std::cin, rowKey);
                std::cout << "Enter column to delete: ";
                std::getline(std::cin, column);
                if (myTable.DeleteCell(rowKey, column)) {
                    std::cout << "Cell '" << column << "' deleted from row '" << rowKey << "'.\n";
                } else {
                    std::cout << "Cell '" << column << "' not found in row '" << rowKey << "'.\n";
                }
                break;
            case 5: {
                auto rows = myTable.ScanTable();
                std::cout << "Scanning entire table:\n";
                for (auto &entry : rows) {
                    std::cout << "Row key: " << entry.first << "\n";
                    for (auto &cell : entry.second) {
                        std::cout << "  " << cell.first << ": " << cell.second.value << "\n";
                    }
                }
                break;
            }
            case 6:
                std::cout << "Enter filename to save table: ";
                std::getline(std::cin, filename);
                if (myTable.SaveToFile(filename)) {
                    std::cout << "Table saved to '" << filename << "'.\n";
                } else {
                    std::cout << "Error saving table.\n";
                }
                break;
            case 7:
                std::cout << "Enter filename to load table: ";
                std::getline(std::cin, filename);
                if (myTable.LoadFromFile(filename)) {
                    std::cout << "Table loaded from '" << filename << "'.\n";
                } else {
                    std::cout << "Error loading table.\n";
                }
                break;
            case 8:
                std::cout << "Exiting. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
