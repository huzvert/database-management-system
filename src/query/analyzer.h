#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

#include "tokenizer.h"
#include "../utils/utils.h"
#include "../metadata/metadata_structures.h"

// Enum for SQL statement types
enum StatementType {
    SELECT_ALL,
    SELECT_WHERE,
    CREATE_TABLE,
    CREATE_DATABASE,
    USE_DATABASE,
    DROP_TABLE,
    DROP_DATABASE,
    INSERT,
    UPDATE,
    EMPTY,
    ERROR
};

// Helper function to trim leading and trailing spaces
inline std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";  // No non-space characters
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Helper function to split a token by commas
inline std::vector<std::string> splitByComma(const std::string& str) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(',');
    while (end != std::string::npos) {
        result.push_back(trim(str.substr(start, end - start)));
        start = end + 1;
        end = str.find(',', start);
    }
    result.push_back(trim(str.substr(start, end - start)));
    return result;
}

// Analyze statement from a vector of tokens
inline StatementType analyzeStatement(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        return EMPTY;
    }

    // Check for INSERT INTO statement
    if (tokens[0].type == TokenType::Keyword && tokens[0].value == "INSERT" && tokens[1].type == TokenType::Keyword && tokens[1].value == "INTO") {
        // After "INSERT INTO", we should have the table name
        if (tokens.size() < 4 || tokens[2].type != TokenType::Identifier) {
            return ERROR;  // Invalid or missing table name
        }

        std::string tableName = tokens[2].value;
        size_t idx = 3;  // Start looking after the table name

        // Look for columns (enclosed in parentheses)
        if (tokens[idx].type == TokenType::OpeningParenthesis) {
            idx++;  // Move past the opening parenthesis
            size_t columnsEndIdx = idx;
            while (columnsEndIdx < tokens.size() && tokens[columnsEndIdx].type != TokenType::ClosingParenthesis) {
                columnsEndIdx++;
            }
            if (columnsEndIdx == tokens.size() || tokens[columnsEndIdx].type != TokenType::ClosingParenthesis) {
                return ERROR;  // Missing closing parenthesis for columns
            }

            // Extract column names (tokens from idx to columnsEndIdx-1)
            std::vector<std::string> columnNames;
            for (size_t i = idx; i < columnsEndIdx; i++) {
                if (tokens[i].type == TokenType::Identifier) {
                    columnNames.push_back(tokens[i].value);
                } else if (tokens[i].type != TokenType::Comma) {
                    return ERROR;  // Invalid token within column names
                }
            }
            idx = columnsEndIdx + 1;  // Move past the closing parenthesis
        }

        // After columns, look for "VALUES"
        if (idx >= tokens.size() || tokens[idx].type != TokenType::Keyword || tokens[idx].value != "VALUES") {
            return ERROR;  // Missing "VALUES" keyword
        }
        idx++;  // Move past "VALUES"

        // Look for values (enclosed in parentheses)
        if (tokens[idx].type != TokenType::OpeningParenthesis) {
            return ERROR;  // Missing opening parenthesis for values
        }

        size_t valuesEndIdx = idx;
        while (valuesEndIdx < tokens.size() && tokens[valuesEndIdx].type != TokenType::ClosingParenthesis) {
            valuesEndIdx++;
        }
        if (valuesEndIdx == tokens.size() || tokens[valuesEndIdx].type != TokenType::ClosingParenthesis) {
            return ERROR;  // Missing closing parenthesis for values
        }

        // Extract values (tokens from idx to valuesEndIdx-1)
        std::vector<std::string> values;
        for (size_t i = idx + 1; i < valuesEndIdx; i++) {
            if (tokens[i].type == TokenType::Literal) {
                values.push_back(tokens[i].value);
            } else if (tokens[i].type != TokenType::Comma) {
                return ERROR;  // Invalid token within values
            }
        }


        // If everything is valid, return INSERT
        return INSERT;
    }

    // If no other statement type matches, return ERROR
    return ERROR;
}
