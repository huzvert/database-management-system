#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "json.hpp"

// directory of metadata file, located in main folder.
const std::string METADATA_FILE = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/metadata.json";


// class to hold column information in memory
class Column_m {
    public:
    std::string name;   // name of column
    std::string type;   // datatype of column
    int order;          // position in row, e.g first element, seconf element, etc.
    bool isPrimaryKey;
    bool isIndexField;
    bool isUnique;

    Column_m(std::string name, std::string type, int order, bool PK = false) {
        this->name = std::move(name);
        this->type = std::move(type);
        this->order = order;
        this->isPrimaryKey = PK;
        isPrimaryKey = false;
        isIndexField = false;
        isUnique = false;
    }

    void printColumn() const {
        std::cout << this->name << " " << this->type << " " << this->order << std::endl;
        std::cout << "isPrimaryKey: " << this->isPrimaryKey << std::endl;
        std::cout << "isIndexField: " << this->isIndexField << std::endl;
        std::cout << "isUnique: " << this->isUnique << std::endl;
    }
};

// class to hold table information in memory
// table is vector of columns
class Table_m {
public:
    std::string name;              // table name
    std::vector<Column_m> columns; // list of columns
    int lastFreeBlock;             // last free block in ".table" file
    int rowsInLastFreeBlock;

    // default constructor needed to Table_m can be used in a hashmap.
    Table_m() {
        name = "";
        lastFreeBlock = 0;
        rowsInLastFreeBlock = 0;
    }

    // expilcit constructor so we can put values if/when needed
    explicit Table_m(std::string name) {
        this->name = std::move(name);
        this->lastFreeBlock = 0;
        this->rowsInLastFreeBlock = 0;
    }

    // add column to table
    void addColumn(const std::string& colName, const std::string& colType, int position, bool PK = false) {
        columns.emplace_back(colName, colType, position, PK);
    }

    // get column from vector of columns.
    Column_m* getColumn(const std::string& colName) {
        for (Column_m& column : columns) {
            if (column.name == colName) {
                return &column; // column found.
            }
        }
        return nullptr; // return nullptr if not found
    }


    // function to calculate total row length in bytes.
    [[nodiscard]] int getRowLength() const {
        int totalLength = 0;
        for (const auto& column : columns) {
            if (column.type == "CHAR") {
                totalLength += 16;
            } else if (column.type == "INT" || column.type == "INTEGER") {
                totalLength += 4;
            } else if (column.type == "DATE") {
                totalLength += 4;
            }
            else if (column.type == "BOOLEAN" || column.type == "BOOL") {
                totalLength += 1;
            }
            // Add cases for other types as needed
        }
        return ++totalLength;
    }

    // Method to display table details
    void display() const {
        std::cout << "Table Name: " << name << "\n";
        std::cout << "Columns:\n";
        for (const Column_m& column : columns) {
            std::cout << "  Name: " << column.name << ", Type: " << column.type
                      << ", Position: " << column.order << "\n";
        }
        std::cout << "Last Free Block: " << lastFreeBlock << "\n";
        std::cout << "Rows in Last Free Block: " << rowsInLastFreeBlock << "\n";
    }
};


class Database_m {
    public:
    std::string name; // name of database
    std::unordered_map<std::string, Table_m> tables; // hashmap of tables

    // default constructor so Database_m can be stored in hashmap.
    Database_m() {
        name = "";
    }

    // explicit constructor so we can set name if/when needed.
    explicit Database_m(std::string name) {
        this->name = std::move(name);
    }

    // add table to database object.
    int addTable(const Table_m& table) {
        auto result = tables.find(table.name);  // check for existence of database.
        if (result != tables.end()) {
            return -1;  // database already exists
        }
        tables[table.name] = table; // database does not exist, added successfully.
        return 0;
    }

    // get Table_m object from Database_m object
    Table_m* getTable(const std::string& tableName) {
        auto table = tables.find(tableName);
        if (table != tables.end()) {
            return &(table->second);    // table found, return ptr to it.
        }
        return nullptr; // table not found, return nullptr.
    }

};

// class to hold entire metadata in memory.
class Metadata {
public:
    std::unordered_map<std::string, std::unordered_map<std::string, Table_m>> databases; // hashmap of databases
    Database_m databaseInUse;
    // add database to Metadata
    int addDatabase(const std::string& dbName) {
        if (databases.find(dbName) == databases.end()) {
            databases[dbName] = std::unordered_map<std::string, Table_m>();
            std::cout << "Database \"" << dbName << "\" added.\n";
            return 0;
        } else {
            std::cout << "Database \"" << dbName << "\" already exists.\n";
            return -1;
        }
    }

    int removeDatabase(const std::string& dbName) {
        // Check if the database exists
        if (databases.find(dbName) == databases.end()) {
            std::cout << "Database \"" << dbName << "\" does not exist.\n";
            return -1; // Database not found
        }

        // Remove the database
        databases.erase(dbName);
        std::cout << "Database \"" << dbName << "\" removed.\n";
        return 0; // Success
    }


    // add table to database
    void addTable(const std::string& dbName, const std::string& tableName) {
        if (databases.find(dbName) == databases.end()) {
            std::cout << "Database \"" << dbName << "\" does not exist.\n";
            return;
        }
        auto& db = databases[dbName];
        if (db.find(tableName) == db.end()) {
            db[tableName] = Table_m(tableName);
            std::cout << "Table \"" << tableName << "\" added to database \"" << dbName << "\".\n";
        } else {
            std::cout << "Table \"" << tableName << "\" already exists in database \"" << dbName << "\".\n";
        }
    }


    void removeTable(const std::string& dbName, const std::string& tableName) {
        // Check if the database exists
        if (databases.find(dbName) == databases.end()) {
            std::cout << "Database \"" << dbName << "\" does not exist.\n";
            return;
        }

        auto& db = databases[dbName];

        // Check if the table exists in the database
        if (db.find(tableName) == db.end()) {
            std::cout << "Table \"" << tableName << "\" does not exist in database \"" << dbName << "\".\n";
            return;
        }

        // Remove the table
        db.erase(tableName);
        std::cout << "Table \"" << tableName << "\" removed from database \"" << dbName << "\".\n";
    }


    std::unordered_map<std::string, Table_m>* getDatabase(const std::string& dbName) {
        auto dbIt = databases.find(dbName);
        if (dbIt == databases.end()) {
            std::cout << "Database \"" << dbName << "\" does not exist.\n";
            return nullptr;
        }
        return &(dbIt->second);  // Return a pointer to the unordered_map of tables
    }



    // get table from database object
    Table_m* getTable(const std::string& dbName, const std::string& tableName) {
        if (databases.find(dbName) == databases.end()) {
            std::cout << "Database \"" << dbName << "\" does not exist.\n";
            return nullptr;
        }
        auto& db = databases[dbName];
        if (!db.contains(tableName)) {
            std::cout << "Table \"" << tableName << "\" does not exist in database \"" << dbName << "\".\n";
            return nullptr;
        }
        return &db[tableName];
    }

    int tableExists(const std::string& dbName, const std::string& tableName) {
        if (!databases.contains(dbName)) {
            return -1;
        }
        auto& db = databases[dbName];
        if (!db.contains(tableName)) {
            return 0;
        }
        return 1;
    }

    int databaseExists(const std::string& databaseName) const {
        // Check if the database exists in the 'databases' map
        if (databases.contains(databaseName)) {
            return 1; // Database exists
        }
        return 0; // Database does not exist
    }

    void displayAllDatabases() {
        if (databases.empty()) {
            std::cout << "NO DATABASES AVAILIBLE." << std::endl;
            return;
        }

        std::cout << "DATABASES" << std::endl;
        // Iterate over each database
        for (const auto &key: databases | std::views::keys) {
            const std::string& databaseName = key;
            std::cout << "\t" << databaseName << std::endl;
        }
    }


    int load() {
        std::ifstream file(METADATA_FILE);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << METADATA_FILE << std::endl;
            return -1;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();  // Read the entire file content into the buffer

        // Step 2: Parse the JSON data from the string
        nlohmann::json j;
        try {
            j = nlohmann::json::parse(buffer.str());
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            return -1;  // Exit the function if JSON parsing fails
        }

        // Step 3: Loop through the "databases" object
        for (auto& [db_name, db_info] : j["databases"].items()) {
            std::cout << "Database: " << db_name << std::endl;
            this->addDatabase(db_name);

            // Loop through the tables in each database
            for (auto& [table_name, table_info] : db_info.items()) {
                std::cout << "  Table: " << table_name << std::endl;

                // Add table
                addTable(db_name, table_name);

                // Initialize lastFreeBlock and numberOfRowsInLastBlock from the JSON data
                if (table_info.contains("lastFreeBlock")) {
                    int lastFreeBlock = table_info["lastFreeBlock"];
                    getTable(db_name, table_name)->lastFreeBlock = lastFreeBlock;
                } else {
                    // Default value if not present
                    getTable(db_name, table_name)->lastFreeBlock = 0;
                }

                if (table_info.contains("numberOfRowsInLastFreeBlock")) {
                    int numberOfRowsInLastBlock = table_info["numberOfRowsInLastFreeBlock"];
                    getTable(db_name, table_name)->rowsInLastFreeBlock = numberOfRowsInLastBlock;
                } else {
                    // Default value if not present
                    getTable(db_name, table_name)->rowsInLastFreeBlock = 0;
                }

                // Loop through the columns of the current table
                if (table_info.contains("columns")) {
                    const auto& columns = table_info["columns"];
                    for (const auto& column : columns) {
                        std::cout << "    Column: " << column["name"]
                                  << ", Position: " << column["position"]
                                  << ", Type: " << column["type"] << std::endl;
                        getTable(db_name, table_name)->addColumn(column["name"], column["type"], column["position"]);
                    }
                }
            }
        }
        return 0;
    }

    int save() const {
    // Step 1: Create a JSON object to hold the metadata
    nlohmann::json j;

    // Step 2: Loop through databases and populate the JSON structure
    for (const auto& dbPair : databases) {
        const std::string& dbName = dbPair.first;
        const auto& tables = dbPair.second;
        nlohmann::json dbInfo;

        // Step 3: Check if there are tables in the database
        if (tables.empty()) {
            // If no tables, store an empty object (not null)
            j["databases"][dbName] = nlohmann::json::object();  // Empty object
        } else {
            // Loop through tables in the database
            for (const auto& tablePair : tables) {
                const Table_m& table = tablePair.second;
                nlohmann::json tableInfo;
                nlohmann::json columns = nlohmann::json::array();  // Ensure columns is an empty array if no columns exist

                // Loop through columns of the table
                for (const Column_m& column : table.columns) {
                    nlohmann::json columnInfo;
                    columnInfo["name"] = column.name;
                    columnInfo["type"] = column.type;
                    columnInfo["position"] = column.order;
                    columns.push_back(columnInfo);
                }

                // If there are no columns, ensure it is still an empty array
                if (columns.empty()) {
                    tableInfo["columns"] = nlohmann::json::array();  // Set columns to an empty array
                } else {
                    tableInfo["columns"] = columns;  // Otherwise, set the populated columns array
                }

                // Add lastFreeBlock and numberOfRowsInLastBlock to the tableInfo
                tableInfo["lastFreeBlock"] = table.lastFreeBlock;
                tableInfo["numberOfRowsInLastFreeBlock"] = table.rowsInLastFreeBlock;

                // Add the table info to the database info
                dbInfo[table.name] = tableInfo;
            }

            // If the database has tables, store the info
            j["databases"][dbName] = dbInfo;
        }
    }

    // Step 4: Write the JSON data to the file (use METADATA_FILE constant)
    std::ofstream outFile(METADATA_FILE, std::ofstream::trunc);  // Open file in truncation mode (overwrite)
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for saving: " << METADATA_FILE << std::endl;
        return -1;  // Return error if the file couldn't be opened
    }

    // Write the JSON data to the file
    outFile << std::setw(4) << j;  // Write JSON with indentation for readability
    outFile.close();  // Close the file after writing

    std::cout << "Metadata saved successfully to " << METADATA_FILE << std::endl;
    return 0;  // Return success
}

    void display() const {
        if (databases.empty()) {
            std::cout << "No databases to display!" << std::endl;
        }

        for (const auto& dbPair : databases) {
            std::cout << "Database: " << dbPair.first << "\n";
            const auto& tables = dbPair.second;

            if (tables.empty()) {
                std::cout << "  No tables in database: " << dbPair.first << "\n";
            }

            for (const auto& tablePair : tables) {
                const Table_m& table = tablePair.second;
                std::cout << "  Table: " << table.name << "\n";
                std::cout << " Last free block: " << table.lastFreeBlock << std::endl;
                std::cout << " RowsInLastFreeBlock: " << table.rowsInLastFreeBlock << std::endl;

                if (table.columns.empty()) {
                    std::cout << "    No columns in table: " << table.name << "\n";
                }

                for (const Column_m& column : table.columns) {
                    std::cout << "    Column: " << column.name
                              << ", Type: " << column.type
                              << ", Position: " << column.order << "\n";
                }
            }
        }
    }

};  
