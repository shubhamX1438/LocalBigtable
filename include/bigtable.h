#ifndef BIGTABLE_H
#define BIGTABLE_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <chrono>
#include <fstream>
#include <sstream>

// A simple cell structure that can hold a value and a timestamp.
struct Cell {
    std::string value;
    std::chrono::system_clock::time_point timestamp;
    
    // Default constructor initializes an empty value.
    Cell() : value(""), timestamp(std::chrono::system_clock::now()) {}

    // Constructor that initializes with a given value.
    Cell(const std::string &val)
        : value(val), timestamp(std::chrono::system_clock::now()) {}
};

// A row is a map from column qualifiers to cells.
using Row = std::map<std::string, Cell>;

// A table is a map from row keys to rows.
using Table = std::map<std::string, Row>;

// The Bigtable class provides a simple API to simulate a distributed table.
class Bigtable {
public:
    Bigtable() = default;

    // Inserts or updates a cell value in a given row and column.
    void InsertCell(const std::string &row_key,
                      const std::string &column,
                      const std::string &value);

    // Retrieves a row by key. Returns true if found.
    bool GetRow(const std::string &row_key, Row &row);

    // Scans the table for all rows.
    std::vector<std::pair<std::string, Row>> ScanTable();

    // Deletes an entire row. Returns true if deletion happened.
    bool DeleteRow(const std::string &row_key);

    // Deletes a specific cell from a row. Returns true if deletion happened.
    bool DeleteCell(const std::string &row_key, const std::string &column);

    // Saves the current table to a file. Returns true on success.
    bool SaveToFile(const std::string &filename);

    // Loads table data from a file. Returns true on success.
    bool LoadFromFile(const std::string &filename);

private:
    Table table_;
    std::mutex mutex_;
};

#endif // BIGTABLE_H
