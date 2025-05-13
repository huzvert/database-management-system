#include <iostream>
#include <string>
#include <iomanip>
#include "src/metadata/json.hpp"

using json = nlohmann::json;

void tabulate(const std::string &jsonString) {
    // Parse the JSON string
    json parsedData = json::parse(jsonString);

    // Extract columns and data
    auto columns = parsedData["columns"];
    auto rows = parsedData["data"];

    // Print the headers
    for (const auto &col : columns) {
        std::cout << std::setw(12) << col.get<std::string>() << " ";
    }
    std::cout << "\n";

    // Print a separator
    for (size_t i = 0; i < columns.size(); ++i) {
        std::cout << std::string(12, '-') << " ";
    }
    std::cout << "\n";

    // Print the rows
    for (const auto &row : rows) {
        for (const auto &col : columns) {
            std::cout << std::setw(12) << row[col.get<std::string>()].get<std::string>() << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // JSON string input
    std::string jsonString = R"({
        "columns": [
            "ID",
            "DOB"
        ],
        "data": [
            { "DOB": "2024-12-28", "ID": "0" },
            { "DOB": "2024-12-29", "ID": "1" },
            { "DOB": "2024-12-30", "ID": "2" },
            { "DOB": "2024-12-31", "ID": "3" },
            { "DOB": "2025-01-01", "ID": "4" },
            { "DOB": "2025-01-02", "ID": "5" },
            { "DOB": "2025-01-03", "ID": "6" },
            { "DOB": "2025-01-04", "ID": "7" },
            { "DOB": "2025-01-05", "ID": "8" },
            { "DOB": "2025-01-06", "ID": "9" }
        ]
    })";

    // Call tabulate function
    tabulate(jsonString);

    return 0;
}
