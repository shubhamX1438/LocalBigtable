#include "bigtable.h"

void Bigtable::InsertCell(const std::string &row_key,
                            const std::string &column,
                            const std::string &value) {
    std::lock_guard<std::mutex> lock(mutex_);
    table_[row_key][column] = Cell(value);
}

bool Bigtable::GetRow(const std::string &row_key, Row &row) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = table_.find(row_key);
    if (it != table_.end()) {
        row = it->second;
        return true;
    }
    return false;
}

std::vector<std::pair<std::string, Row>> Bigtable::ScanTable() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::pair<std::string, Row>> results;
    for (auto &entry : table_) {
        results.push_back(entry);
    }
    return results;
}

bool Bigtable::DeleteRow(const std::string &row_key) {
    std::lock_guard<std::mutex> lock(mutex_);
    return table_.erase(row_key) > 0;
}

bool Bigtable::DeleteCell(const std::string &row_key, const std::string &column) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto rowIt = table_.find(row_key);
    if (rowIt != table_.end()) {
        auto &row = rowIt->second;
        if (row.erase(column) > 0) {
            return true;
        }
    }
    return false;
}

bool Bigtable::SaveToFile(const std::string &filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::ofstream ofs(filename);
    if (!ofs.is_open()) return false;

    // For each row, write: row_key|col1=value1|col2=value2
    for (auto &entry : table_) {
        ofs << entry.first;
        for (auto &cellPair : entry.second) {
            ofs << "|" << cellPair.first << "=" << cellPair.second.value;
        }
        ofs << "\n";
    }
    ofs.close();
    return true;
}

bool Bigtable::LoadFromFile(const std::string &filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return false;

    table_.clear();
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string token;
        // First token is the row key.
        std::getline(iss, token, '|');
        std::string row_key = token;
        while (std::getline(iss, token, '|')) {
            // Each token is in format column=value
            size_t pos = token.find('=');
            if (pos != std::string::npos) {
                std::string column = token.substr(0, pos);
                std::string value = token.substr(pos + 1);
                table_[row_key][column] = Cell(value);
            }
        }
    }
    ifs.close();
    return true;
}
