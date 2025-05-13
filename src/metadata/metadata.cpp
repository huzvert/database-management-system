#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

// status codes for successful initialization
enum InitStatus {
    METADATA_FILE_EXISTS = 0,
    METADATA_FILE_CREATED = 1,
    METADATA_FILE_CREATE_ERROR = -1
};

const std::string METADATA_FILE = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/metadata.json";

// function to initialize (empty) metadata file
int init() {
    std::ifstream infile(METADATA_FILE);
    if (infile.good()) {
        // file exists, no need to initialize
        return METADATA_FILE_EXISTS;
    }
    infile.close();
    // create the file and write initial JSON structure
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return METADATA_FILE_CREATE_ERROR;
    }

    outfile << "{\n  \"databases\": {}\n}" << std::endl;
    outfile.close();
    return METADATA_FILE_CREATED;
}

// enum of status codes for adding database
enum AddDatabaseStatus {
    ADD_DATABASE_SUCCESS = 0,
    ADD_DATABASE_ERROR = -1,
    ADD_DATABASE_ALREADY_EXISTS = 1
};

// function to add database to metadata file
int addDatabase(const std::string& dbName) {
    std::ifstream infile(METADATA_FILE);
    std::filesystem::create_directory("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases");
    std::filesystem::create_directories("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + dbName);
    if (!infile) {
        return ADD_DATABASE_ERROR;
    }

    // Parse the JSON from the file
    json metadata;
    infile >> metadata;
    infile.close();

    // Check if database already exists
    if (metadata["databases"].contains(dbName)) {
        return ADD_DATABASE_ALREADY_EXISTS;
    }

    // Add new database entry
    metadata["databases"][dbName] = json::object();  // Empty object for now

    // Write updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return ADD_DATABASE_ERROR;
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4 spaces for indentation
    outfile.close();

    return ADD_DATABASE_SUCCESS;
}

// enum of status codes for adding table
enum AddTableStatus {
    ADD_TABLE_SUCCESS = 0,
    ADD_TABLE_ERROR = -1,
    ADD_TABLE_DATABASE_NOT_FOUND = 1,
    ADD_TABLE_ALREADY_EXISTS = 2
};


AddTableStatus addTable(const std::string& dbName, const std::string& tableName) {
    std::ifstream infile(METADATA_FILE);
    if (!infile) {
        return ADD_TABLE_ERROR;  // Metadata file not found
    }

    std::string indexFilePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + dbName + "/" + dbName + "_" + tableName + ".index";
    std::string tableFilePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + dbName + "/" + dbName + "_" + tableName + ".table";
    std::filesystem::path dirPath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases";

    // Ensure the directory for databases exists
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directory(dirPath);
    }

    // Open the table file (it will be created if it doesn't exist)
    std::ofstream tableFile(tableFilePath);
    if (!tableFile) {
        return ADD_TABLE_ERROR;  // Could not create table file
    }
    tableFile.close();  // Close immediately after ensuring its creation


    std::ofstream indexFile(indexFilePath);
    if (!indexFile) {
        return ADD_TABLE_ERROR;  // Could not create table file
    }
    indexFile.close();

    // Parse the JSON from the metadata file
    nlohmann::json metadata;
    infile >> metadata;
    infile.close();

    // Check if the database exists
    if (!metadata["databases"].contains(dbName)) {
        return ADD_TABLE_DATABASE_NOT_FOUND;  // Database does not exist
    }

    // Check if the table already exists in the specified database
    if (metadata["databases"][dbName].contains(tableName)) {
        return ADD_TABLE_ALREADY_EXISTS;  // Table already exists
    }

    // Add a new table entry with `lastFreeBlock` set to 0 and an empty columns array
    metadata["databases"][dbName][tableName] = {
        {"lastFreeBlock", 0},      // Initializing the last free block
        {"numberOfRowsInLastFreeBlock", 0},
        {"columns", nlohmann::json::array()} // Empty array for columns
    };

    // Write the updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return ADD_TABLE_ERROR;  // Could not write to metadata file
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4-space indentation
    outfile.close();

    return ADD_TABLE_SUCCESS;  // Successfully added the table
}

// enum of status codes for adding column
enum AddColumnStatus {
    ADD_COLUMN_SUCCESS = 0,
    ADD_COLUMN_ERROR = -1,
    ADD_COLUMN_DATABASE_NOT_FOUND = 1,
    ADD_COLUMN_TABLE_NOT_FOUND = 2,
    ADD_COLUMN_ALREADY_EXISTS = 3,
    ADD_COLUMN_PRIMARY_KEY_EXISTS = 4
};

int addColumn(const std::string& dbName, const std::string& tableName,
              const std::string& columnName, const std::string& columnType, int position, bool isPK = false) {
    std::ifstream infile(METADATA_FILE);
    if (!infile) {
        return ADD_COLUMN_ERROR; // Error opening the metadata file
    }

    // Parse the JSON from the file
    json metadata;
    infile >> metadata;
    infile.close();

    // Check if the database exists
    if (!metadata["databases"].contains(dbName)) {
        return ADD_COLUMN_DATABASE_NOT_FOUND; // Database not found
    }

    // Check if the table exists in the database
    if (!metadata["databases"][dbName].contains(tableName)) {
        return ADD_COLUMN_TABLE_NOT_FOUND; // Table not found
    }

    // Check if the column already exists in the table
    for (const auto& column : metadata["databases"][dbName][tableName]["columns"]) {
        if (column["name"] == columnName) {
            return ADD_COLUMN_ALREADY_EXISTS; // Column already exists
        }
    }

    // Check if the table already has a primary key
    if (isPK) {
        for (const auto& column : metadata["databases"][dbName][tableName]["columns"]) {
            if (column.value("isPrimaryKey", false)) { // Check for an existing primary key
                return ADD_COLUMN_PRIMARY_KEY_EXISTS; // Primary key already exists
            }
        }
        position = 0; // Enforce primary key position as 0
    }

    // Create a new JSON object for the column
    json columnProperties;
    columnProperties["name"] = columnName;
    columnProperties["type"] = columnType;
    columnProperties["position"] = position;
    columnProperties["isPrimaryKey"] = isPK; // Add isPrimaryKey field

    // Add the column to the "columns" array
    metadata["databases"][dbName][tableName]["columns"].push_back(columnProperties);

    // Write updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return ADD_COLUMN_ERROR; // Error writing back to the file
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4 spaces for indentation
    outfile.close();

    return ADD_COLUMN_SUCCESS; // Success
}




// enum of status codes for removing database
enum RemoveDatabaseStatus {
    REMOVE_DATABASE_SUCCESS = 0,
    REMOVE_DATABASE_ERROR = -1,
    REMOVE_DATABASE_NOT_FOUND = -2
};

// function to remove database from metadata file
int removeDatabase(const std::string& dbName) {
    std::ifstream infile(METADATA_FILE);
    if (!infile) {
        return REMOVE_DATABASE_ERROR; // Error opening the metadata file
    }

    // Parse the JSON from the file
    json metadata;
    infile >> metadata;
    infile.close();

    // Check if the database exists
    if (!metadata["databases"].contains(dbName)) {
        return REMOVE_DATABASE_NOT_FOUND; // Database not found
    }

    // Remove the database
    metadata["databases"].erase(dbName);

    // Write updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return REMOVE_DATABASE_ERROR; // Error writing back to the file
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4 spaces for indentation
    outfile.close();

    return REMOVE_DATABASE_SUCCESS; // Success
}

// enum of status codes for removing column
enum RemoveColumnStatus {
    REMOVE_COLUMN_SUCCESS = 0,
    REMOVE_COLUMN_ERROR = -1,
    REMOVE_COLUMN_DATABASE_NOT_FOUND = -2,
    REMOVE_COLUMN_TABLE_NOT_FOUND = -3,
    REMOVE_COLUMN_NOT_FOUND = -4
};

// function to remove a column from the metadata file
int removeColumn(const std::string& dbName, const std::string& tableName,
                 const std::string& columnName) {
    std::ifstream infile(METADATA_FILE);
    if (!infile) {
        return REMOVE_COLUMN_ERROR; // Error opening the metadata file
    }

    // Parse the JSON from the file
    json metadata;
    infile >> metadata;
    infile.close();

    // Check if the database exists
    if (!metadata["databases"].contains(dbName)) {
        return REMOVE_COLUMN_DATABASE_NOT_FOUND; // Database not found
    }

    // Check if the table exists in the database
    if (!metadata["databases"][dbName].contains(tableName)) {
        return REMOVE_COLUMN_TABLE_NOT_FOUND; // Table not found
    }

    // Check if the column exists in the table
    bool columnFound = false;
    auto& columns = metadata["databases"][dbName][tableName]["columns"];
    for (auto it = columns.begin(); it != columns.end(); ++it) {
        if ((*it)["name"] == columnName) {
            // Column found, erase it from the array
            columns.erase(it);
            columnFound = true;
            break;
        }
    }

    if (!columnFound) {
        return REMOVE_COLUMN_NOT_FOUND; // Column not found
    }

    // Write the updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return REMOVE_COLUMN_ERROR; // Error writing back to the file
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4 spaces for indentation
    outfile.close();

    return REMOVE_COLUMN_SUCCESS; // Successfully removed the column
}


// enum of status codes for removing table
enum RemoveTableStatus {
    REMOVE_TABLE_SUCCESS = 0,
    REMOVE_TABLE_ERROR = -1,
    REMOVE_TABLE_DATABASE_NOT_FOUND = -2,
    REMOVE_TABLE_NOT_FOUND = -3
};

// function to remove table from metadata file
int removeTable(const std::string& dbName, const std::string& tableName) {
    std::ifstream infile(METADATA_FILE);
    if (!infile) {
        return REMOVE_TABLE_ERROR; // Error opening the metadata file
    }

    // Parse the JSON from the file
    json metadata;
    infile >> metadata;
    infile.close();

    // Check if the database exists
    if (!metadata["databases"].contains(dbName)) {
        return REMOVE_TABLE_DATABASE_NOT_FOUND; // Database not found
    }

    // Check if the table exists in the database
    if (!metadata["databases"][dbName].contains(tableName)) {
        return REMOVE_TABLE_NOT_FOUND; // Table not found
    }

    // Remove the table from the database
    metadata["databases"][dbName].erase(tableName);

    // Write updated metadata back to the file
    std::ofstream outfile(METADATA_FILE);
    if (!outfile) {
        return REMOVE_TABLE_ERROR; // Error writing back to the file
    }

    outfile << std::setw(4) << metadata << std::endl;  // Pretty print with 4 spaces for indentation
    outfile.close();

    return REMOVE_TABLE_SUCCESS; // Success
}




