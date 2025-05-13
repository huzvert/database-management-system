#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <variant>

#include "../metadata/metadata_structures.h"
#include "bpt.h"

#define BLOCK_SIZE 4096
#define PROJECT_HOME = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER";


inline int insertToIndexFile(const std::string &databaseName, const std::string &tableName, const char *key,
                             const int block) {
    // Construct the file path for the index file
    const std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" +
                                 databaseName + "_" + tableName + ".index";

    // Open the B+ Tree with the index file
    bpt::bplus_tree indexFile(filePath.c_str());
    const bpt::value_t val = block;

    // Insert the key-block pair into the index file
    int result = indexFile.insert(key, val);
    if (result != 0) {
        std::cout << "Key " << key << " already exists in index file." << std::endl;
        return result;
    }

    std::cout << "Inserted key-block pair (" << key << ", " << block << ") successfully in index file." << std::endl;
    return 0;
}

inline int removeFromIndexFile(const std::string &databaseName, const std::string &tableName, const char *key) {
    // Construct the file path for the index file
    const std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" +
                                 databaseName + "_" + tableName + ".index";

    // Open the B+ Tree with the index file
    bpt::bplus_tree indexFile(filePath.c_str());

    // Attempt to remove the key from the index file
    int result = indexFile.remove(key);
    if (result != 0) {
        std::cout << "Key " << key << " not found in index file." << std::endl;
        return result;
    }

    std::cout << "Key " << key << " successfully removed from index file." << std::endl;
    return 0;
}

inline int searchFromIndexFile(const std::string &databaseName, const std::string &tableName, const char *key,
                               int &block) {
    // Construct the file path for the index file
    const std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" +
                                 databaseName + "_" + tableName + ".index";

    // Open the B+ Tree with the index file
    const bpt::bplus_tree indexFile(filePath.c_str());

    // Search for the key in the index file
    bpt::value_t val;
    int result = indexFile.search(key, &val);
    if (result != 0) {
        std::cout << "Key " << key << " not found in index file." << std::endl;
        return result;
    }

    // If found, assign the block value to the reference parameter
    block = val;

    std::cout << "Key " << key << " found in index file with block " << block << "." << std::endl;
    return 0;
}

inline int updateIndexFile(const std::string &databaseName, const std::string &tableName, const char *key,
                           const int newBlock) {
    // Construct the file path for the index file
    const std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" +
                                 databaseName + "_" + tableName + ".index";

    // Open the B+ Tree with the index file
    bpt::bplus_tree indexFile(filePath.c_str());

    // Attempt to update the key in the index file with the new block value
    int result = indexFile.update(key, newBlock);
    if (result != 0) {
        std::cout << "Key " << key << " not found in index file for update." << std::endl;
        return result;
    }

    std::cout << "Key " << key << " successfully updated to new block " << newBlock << " in index file." << std::endl;
    return 0;
}

enum DataType {
    INT,
    BOOL,
    CHAR,
    DATE,
    NONE
};

class Data {
public:
    DataType datatype;
    std::variant<int, bool, std::string> value;
    int charLength;

    // First constructor (handles string conversion and padding/truncating for CHAR)
    Data(const DataType datatype, const std::string &value, const int charLength) {
        this->datatype = datatype;
        if (datatype == CHAR) {
            this->charLength = charLength;
            if (value.length() > charLength) {
                this->value = value.substr(0, charLength); // Truncate if longer
            } else {
                this->value = value + std::string(charLength - value.length(), ' '); // Pad with spaces
            }
        } else {
            this->charLength = -1; // No charLength needed for non-CHAR types
            if (datatype == INT) {
                this->value = std::stoi(value); // Convert string to INT
            } else if (datatype == BOOL) {
                this->value = (value == "true"); // Convert string to BOOL
            } else if (datatype == DATE) {
                this->value = value; // For DATE, treat as string (e.g., "2024-12-15")
            }
        }
    }

    // Second constructor (directly uses variant types)
    Data(const DataType datatype, std::variant<int, bool, std::string> value) {
        this->datatype = datatype;
        this->value = std::move(value);
        if (datatype != CHAR) {
            this->charLength = -1; // No charLength needed for non-CHAR types
        }
    }

    void print() const {
        std::cout << "DataType: " << datatype << ", ";
        if (datatype == INT) {
            std::cout << "Value: " << std::get<int>(value);
        } else if (datatype == BOOL) {
            std::cout << "Value: " << std::get<bool>(value);
        } else if (datatype == CHAR || datatype == DATE) {
            std::cout << "Value: " << std::get<std::string>(value);
        }
        std::cout << ", CharLength: " << charLength << std::endl;
    }

    char *toCharPtr() {
        // Declare a local buffer to avoid static usage
        static std::string strBuffer; // Static buffer to hold the result (used safely)

        // Handle each type of value in the variant using std::visit
        std::visit([&]<typename T0>(T0 &&arg) {
            if constexpr (std::is_same_v<std::decay_t<T0>, bool>) {
                strBuffer = arg ? "TRUE" : "FALSE"; // Convert bool to "TRUE" or "FALSE"
            } else if constexpr (std::is_same_v<std::decay_t<T0>, int>) {
                strBuffer = std::to_string(arg); // Convert int to string
            } else if constexpr (std::is_same_v<std::decay_t<T0>, std::string>) {
                strBuffer = arg; // Directly use the string value
            }
        }, value);

        // Return char* to the string buffer
        return strBuffer.data(); // Return data pointer to strBuffer
    }



    inline std::string toString() {
        switch (datatype) {
            case INT:
                return std::to_string(std::get<int>(value));
            case BOOL:
                return std::get<bool>(value) ? "true" : "false";
            case DATE:
                return std::get<std::string>(value); // Date is already a string in "yyyy-mm-dd" format
            default:
                return ""; // Return an empty string or handle invalid cases
        }
    }
};

inline std::vector<unsigned char> intToBits(const int data) {
    std::vector<unsigned char> result(4);
    for (int i = 0; i < 4; i++) {
        result[3 - i] = (data >> (i * 8)) & 0xFF; // Reverse the order
    }
    return result;
}

inline std::vector<unsigned char> boolToBits(const bool data) {
    // If true, return a vector with a single byte of all 1s (0xFF)
    if (data) {
        return std::vector<unsigned char>(1, 0xFF); // All bits set to 1
    } else {
        return std::vector<unsigned char>(1, 0x00); // All bits set to 0
    }
}

inline std::vector<unsigned char> charsToBits(const std::string &data) {
    std::vector<unsigned char> result;

    for (size_t i = 0; i < data.length(); i++) {
        result.push_back(static_cast<unsigned char>(data[i])); // ASCII value of the character
    }

    return result;
}

inline std::vector<unsigned char> dateToBits(const std::string &date) {
    std::vector<unsigned char> result(4);

    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    /*
    if (ss.fail() || dash1 != '-' || dash2 != '-' || month < 1 || month > 12 || day < 1 || day > 31) {
        std::cerr << "Invalid date format!" << std::endl;
        return result;
    }
    */

    result[0] = (year >> 8) & 0xFF; // High byte of the year
    result[1] = year & 0xFF; // Low byte of the year
    result[2] = static_cast<unsigned char>(month);
    result[3] = static_cast<unsigned char>(day);

    return result;
}


// Reverse functions
inline int bitsToInt(const std::vector<unsigned char> &binaryData) {
    int value = 0;
    for (int i = 0; i < 4; i++) {
        value = (value << 8) | binaryData[i];
    }
    return value;
}

inline bool bitsToBool(const std::vector<unsigned char> &binaryData) {
    return binaryData[0] != 0x00;
}

inline std::string bitsToChars(const std::vector<unsigned char> &binaryData) {
    std::string result(binaryData.begin(), binaryData.end());
    return result;
}

inline std::string bitsToDate(const std::vector<unsigned char> &binaryData) {
    const int year = (binaryData[0] << 8) | binaryData[1];
    const int month = binaryData[2];
    const int day = binaryData[3];

    std::ostringstream dateStream;
    dateStream << std::setfill('0') << std::setw(4) << year << '-'
            << std::setw(2) << month << '-'
            << std::setw(2) << day;

    return dateStream.str();
}

inline std::vector<unsigned char> convertRowToBinary(std::vector<Data> data) {
    std::vector<unsigned char> result;

    for (auto &i: data) {
        if (i.datatype == INT) {
            // Convert INT to binary and append to the result
            auto binary = intToBits(std::get<int>(i.value)); // Extract value from variant and convert to binary
            result.insert(result.end(), binary.begin(), binary.end());
        } else if (i.datatype == BOOL) {
            // Convert BOOL to binary and append to the result
            auto binary = boolToBits(std::get<bool>(i.value));
            result.insert(result.end(), binary.begin(), binary.end());
        } else if (i.datatype == CHAR) {
            // Convert CHAR to binary and append to the result
            auto binary = charsToBits(std::get<std::string>(i.value));
            result.insert(result.end(), binary.begin(), binary.end());
        } else if (i.datatype == DATE) {
            // Convert DATE to binary and append to the result
            auto binary = dateToBits(std::get<std::string>(i.value));
            result.insert(result.end(), binary.begin(), binary.end());
        }
    }

    return result;
}

inline void toLittleEndian(int &value) {
    value = ((value >> 24) & 0x000000FF) |
            ((value >> 8) & 0x0000FF00) |
            ((value << 8) & 0x00FF0000) |
            ((value << 24) & 0xFF000000);
}

inline void appendInt(const std::string &filePath, int value) {
    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    toLittleEndian(value);
    // Write the integer to the file
    outFile.write(reinterpret_cast<const char *>(&value), sizeof(value));

    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "Integer appended successfully!" << std::endl;
}

inline void appendDate(const std::string& filePath, const std::string& date) {

    unsigned char result[4];

    int year, month, day;
    char dash1, dash2;
    std::stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    /*
    if (ss.fail() || dash1 != '-' || dash2 != '-' || month < 1 || month > 12 || day < 1 || day > 31) {
        std::cerr << "Invalid date format!" << std::endl;
        return result;
    }
    */

    result[0] = (year >> 8) & 0xFF; // High byte of the year
    result[1] = year & 0xFF; // Low byte of the year
    result[2] = static_cast<unsigned char>(month);
    result[3] = static_cast<unsigned char>(day);


    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    // Write the 4 bytes (year, month, day) to the file
    outFile.write(reinterpret_cast<const char*>(result), sizeof(result));

    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "Date appended successfully!" << std::endl;
}

inline void appendBool(const std::string &filePath, const bool value) {
    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    // Represent true as 0xFF (11111111) and false as 0x00 (00000000)
    unsigned char byteToWrite = value ? 0xFF : 0x00;

    // Write the byte to the file
    outFile.write(reinterpret_cast<const char *>(&byteToWrite), sizeof(byteToWrite));

    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "Boolean appended successfully!" << std::endl;
}

inline void appendChar(const std::string &filePath, const std::string &str, const size_t length) {
    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    // Ensure that we don't write more characters than the specified length
    if (length > str.size()) {
        std::cerr << "Length exceeds string size!" << std::endl;
        return;
    }

    // Write the specified length of the string to the file
    outFile.write(str.c_str(), length);

    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "String appended successfully!" << std::endl;
}

inline void appendMarkDeleted(const std::string &filePath) {
    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    constexpr unsigned char byteToWrite =  0xFF;
    // Write the byte to the file
    outFile.write(reinterpret_cast<const char *>(&byteToWrite), sizeof(byteToWrite));
    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "BAD FLAG flag appended successfully!" << std::endl;
}

inline void appendDeleteFlag(const std::string &filePath) {
    // Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Failed to open the file for appending!" << std::endl;
        return;
    }

    constexpr unsigned char byteToWrite =  0x00;
    std::cout << "Appending: " << static_cast<int>(byteToWrite) << std::endl;
    // Write the byte to the file
    outFile.write(reinterpret_cast<const char *>(&byteToWrite), sizeof(byteToWrite));
    // Close the file to ensure all data is written
    outFile.close();

    std::cout << "Delete flag appended successfully!" << std::endl;
}

inline long getFileSize(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);  // Open in binary mode and move to the end
    if (!inFile) {
        std::cerr << "Failed to open the file!" << std::endl;
        return -1;
    }
    return inFile.tellg();  // Return the position of the file pointer, i.e., the file size
}


inline int insertToDataFile(const std::vector<Data> &data, const std::string &databaseName,
                                 const std::string &tableName, Metadata &metadata) {

    // Step 1: Retrieve table metadata
    Table_m *tableMetadata = metadata.getTable(databaseName, tableName);
    if (!tableMetadata) {
        std::cerr << "Table not found!" << std::endl;
        return -1; // Return error if table not found
    }

    // Extract necessary information from table metadata
    const int rowSize = tableMetadata->getRowLength();

    // Step 3: Construct the file path
    const std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName +
                                 "_" + tableName + ".table";

    // Step 4: Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);

    // get file size
    const long size = getFileSize(filePath) % 4096;
    for (const auto & i : data) {
        if (i.datatype == INT) {
            appendInt(filePath, std::get<int>(i.value));
        }
        else if (i.datatype == BOOL) {
            appendBool(filePath, std::get<bool>(i.value));
        }
        else if (i.datatype == DATE) {
            appendDate(filePath, std::get<std::string>(i.value));
        }
        else if (i.datatype == CHAR) {
            appendChar(filePath, std::get<std::string>(i.value), std::get<std::string>(i.value).length());
        }
    }

    appendDeleteFlag(filePath);
    if (size == 0) {
        tableMetadata->rowsInLastFreeBlock++;
    }
    else {
        // get remaining part in block
        tableMetadata->rowsInLastFreeBlock++;
        int remainingSize = BLOCK_SIZE - size - rowSize;
        if (remainingSize < rowSize) {
            // fill the block with 0's for empty.
            for (int i = 0; i < remainingSize; i++) {
                appendBool(filePath, false);
            }
            tableMetadata->rowsInLastFreeBlock = 0;
            tableMetadata->lastFreeBlock++;
        }
    }

    return 0;
}

inline std::vector<Data> readFromFile(const std::string &databaseName, const std::string &tableName, int blockNumber,
                                      Metadata metadata, const std::vector<DataType> &dataTypes) {
    int rowSize = metadata.getTable(databaseName, tableName)->getRowLength();
    std::cout << "Row size is: " << rowSize << std::endl;
    std::vector<Data> output;

    std::ifstream file(
        "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName +
        ".table", std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return {};
    }

    Table_m *tableMetadata = metadata.getTable(databaseName, tableName);
    if (tableMetadata->lastFreeBlock == 0 && tableMetadata->rowsInLastFreeBlock == 0) {
        return {}; // No data to read
    }

    // Seek to the block position (each block is BLOCK_SIZE bytes)
    int blockPosition = blockNumber * BLOCK_SIZE;
    file.seekg(blockPosition, std::ios::beg);

    // Step 1: Calculate how many rows to read
    int rowsToRead = 0;
    if (blockNumber == tableMetadata->lastFreeBlock) {
        // If it's the last block, we only need to read `rowsInLastFreeBlock` rows
        rowsToRead = tableMetadata->rowsInLastFreeBlock;
    } else {
        // For other blocks, we read as many rows as fit into the block
        rowsToRead = BLOCK_SIZE / rowSize;
    }

    std::cout << "The row size is: " << rowSize << std::endl;


    // Step 2: Read each row and extract data
    for (int i = 0; i < rowsToRead; i++) {
        // Read the entire row (rowSize bytes)
        std::vector<char> rowData(rowSize);
        file.read(rowData.data(), rowSize);

        if (file.gcount() == rowSize) {  // Ensure full read
            // Access the last byte of the rowData
            unsigned char lastByte = rowData.back();
            // or equivalently
            // unsigned char lastByte = rowData[rowData.size() - 1];

            // Check if the last byte is 00000000 (which is just 0 in an unsigned char)
            if (static_cast<int>(lastByte) == 0) {
                std::cout << "Last byte is 00000000." << std::endl;
                int offset = 0;
                for (const auto &type: dataTypes) {
                    if (type == DataType::INT) {
                        // std::cout << "Reading from offset " << offset << std::endl;
                        // INT is 4 bytes
                        std::vector<unsigned char> byteData(rowData.begin() + offset, rowData.begin() + offset + 4);
                        output.emplace_back(INT, bitsToInt(byteData));
                        offset += 4;
                    } else if (type == DataType::BOOL) {
                        // std::cout << "Reading from offset " << offset << std::endl;
                        // BOOL is 1 byte
                        output.emplace_back(BOOL, rowData[offset] != 0); // Assuming non-zero is true
                        offset += 1;
                    } else if (type == DataType::DATE) {
                        // std::cout << "Reading from offset " << offset << std::endl;
                        // DATE is 4 bytes
                        std::vector<unsigned char> byteData(rowData.begin() + offset, rowData.begin() + offset + 4);
                        output.emplace_back(DATE, bitsToDate(byteData));
                        offset += 4;
                    } else {
                        std::cerr << "Invalid type field!" << std::endl;
                    }
                }
            } else {
                std::cout << "Last byte is not 00000000." << std::endl;
                std::cout << "Last byte as integer: " << static_cast<int>(lastByte) << std::endl;
            }
        }

    }
    return output;
}









































inline void readBlockAndPrintRowsFromFile(
    const std::string &filename, // File name for the data file
    int blockNumber, // Block number to read
    int rowSize, // Size of each row in bytes
    const std::vector<DataType> &dataTypes // Ordered data types for decoding
) {
    int blockSize = 4096;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Calculate the offset to the block
    std::streampos blockOffset = blockNumber * blockSize;

    // Seek to the block's position in the file
    file.seekg(blockOffset);
    if (!file) {
        std::cerr << "Error: Could not seek to block " << blockNumber << std::endl;
        return;
    }

    // Read the block data
    std::vector<unsigned char> blockData(blockSize);
    file.read(reinterpret_cast<char *>(blockData.data()), blockSize);
    if (!file) {
        std::cerr << "Error: Could not read block " << blockNumber << std::endl;
        return;
    }

    file.close();

    // Process the block data into rows and print
    int totalRows = blockSize / rowSize; // Total rows in the block

    for (int row = 0; row < totalRows; row++) {
        int offset = row * rowSize; // Start of the current row
        std::cout << "Row " << row + 1 << ": ";

        for (const auto &type: dataTypes) {
            if (type == INT) {
                int value = bitsToInt(std::vector<unsigned char>(
                    blockData.begin() + offset,
                    blockData.begin() + offset + 4));
                std::cout << value << " ";
                offset += 4;
            } else if (type == BOOL) {
                bool value = bitsToBool(std::vector<unsigned char>(
                    blockData.begin() + offset,
                    blockData.begin() + offset + 1));
                std::cout << (value ? "true" : "false") << " ";
                offset += 1;
            } else if (type == DATE) {
                std::string value = bitsToDate(std::vector<unsigned char>(
                    blockData.begin() + offset,
                    blockData.begin() + offset + 4));
                std::cout << value << " ";
                offset += 4;
            }
            // Add other types like CHAR if needed
        }
        std::cout << std::endl;
    }
}


/*
inline int insertToDataFile(const std::vector<Data> &data, const std::string &databaseName,
                            const std::string &tableName, Metadata &metadata) {
    // Step 1: Retrieve table metadata
    Table_m *tableMetadata = metadata.getTable(databaseName, tableName);
    if (!tableMetadata) {
        std::cerr << "Table not found!" << std::endl;
        return -1; // Return error if table not found
    }

    // Extract necessary information from table metadata
    int lastFreeBlock = tableMetadata->lastFreeBlock;
    int rowsInLastFreeBlock = tableMetadata->rowsInLastFreeBlock;
    int rowSize = tableMetadata->getRowLength();
    int blockSize = BLOCK_SIZE;

    // Step 2: Convert the entire row (a vector of Data) to binary
    std::vector<unsigned char> binaryRow = convertRowToBinary(data);

    if (binaryRow.empty()) {
        std::cerr << "Error: The binary row conversion resulted in an empty vector." << std::endl;
        return -1;
    }

    // Step 3: Construct the file path
    std::string filePath = "/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName +
                           "_" + tableName + ".table";

    // Step 4: Open the file in binary append mode
    std::ofstream outFile(filePath, std::ios::binary | std::ios::app);

    if (!outFile.is_open()) {
        return -1; // Return error if file could not be opened
    }

    // Step 5: Determine where to write the data
    int lastFreeBlockPosition = lastFreeBlock * blockSize;

    if (rowsInLastFreeBlock == 0) {
        // If there are no rows in the last free block, write the data at the start of the last free block
        outFile.seekp(lastFreeBlockPosition); // Move to the start of the last free block
        outFile.write(reinterpret_cast<const char *>(binaryRow.data()), binaryRow.size());
        tableMetadata->rowsInLastFreeBlock = 1; // We have now inserted one row into this block
    } else {
        // If there are already rows in the last free block, write the data in the current block
        outFile.seekp(lastFreeBlockPosition + rowsInLastFreeBlock * rowSize);
        outFile.write(reinterpret_cast<const char *>(binaryRow.data()), binaryRow.size());
        tableMetadata->rowsInLastFreeBlock++; // Increment the number of rows in the last block

        // Step 6: Check if there is enough space in the current block for another row
        if (blockSize - (rowsInLastFreeBlock * rowSize) < rowSize) {
            // If there is not enough space, pad the block with zeros
            int paddingSize = blockSize - (rowsInLastFreeBlock * rowSize);
            std::vector<unsigned char> padding(paddingSize, 0);
            outFile.write(reinterpret_cast<const char *>(padding.data()), padding.size());

            // Move to the next block and reset rowsInLastFreeBlock to 0
            tableMetadata->lastFreeBlock++; // Move to the next block
            tableMetadata->rowsInLastFreeBlock = 0; // Reset row count for the new block
        }
    }

    // Step 7: Close the file
    outFile.flush();
    outFile.close();

    return 0; // Return success
}
*/