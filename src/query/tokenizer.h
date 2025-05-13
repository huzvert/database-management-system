#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <set>
#include <iostream>

#include "../utils/utils.h"


inline std::string removeTrailingSpaces(const std::string& input) {
    // Trim leading and trailing spaces
    size_t start = input.find_first_not_of(' ');
    if (start == std::string::npos) {
        return ";"; // If string is all spaces, return empty string
    }

    size_t end = input.find_last_not_of(' ');
    std::string trimmed = input.substr(start, end - start + 1);

    // Remove ALL trailing semicolons
    while (!trimmed.empty() && trimmed.back() == ';') {
        trimmed.pop_back();
    }

    // Add exactly one space before the final semicolon (if there is content)
    if (!trimmed.empty()) {
        trimmed += " "; // Ensure one space before the semicolon
        trimmed += ';';  // Append semicolon
    }

    return trimmed;
}

inline std::string cleanStringWithQuotes(const std::string& input) {
    std::string result;
    bool inDoubleQuote = false;
    bool inSingleQuote = false;

    size_t i = 0;
    while (i < input.size()) {
        char currentChar = input[i];

        // Check for unbalanced quotes
        if (currentChar == '"') {
            if (inDoubleQuote) {
                inDoubleQuote = false;  // Close the double quote
            } else if (!inSingleQuote) {
                inDoubleQuote = true;   // Open a double quote
            }
        } else if (currentChar == '\'') {
            if (inSingleQuote) {
                inSingleQuote = false;  // Close the single quote
            } else if (!inDoubleQuote) {
                inSingleQuote = true;   // Open a single quote
            }
        }

        // If we're inside quotes, preserve the content
        if (inDoubleQuote || inSingleQuote) {
            result += currentChar;
        } else {
            // Outside quotes: Handle spaces between words
            if (std::isspace(currentChar)) {
                // Only add a space if the last added character wasn't already a space
                if (!result.empty() && !std::isspace(result.back())) {
                    result += ' ';
                }
            } else {
                result += currentChar;
            }
        }

        i++;
    }

    // After processing the string, check if there were any unmatched quotes
    if (inDoubleQuote || inSingleQuote) {
        return "ERROR";  // Unmatched quotes
    }

    return result;
}

inline std::string formatSQLQuery(const std::string &input) {
    std::string result;
    bool inString = false;  // To track if we are inside a string literal
    bool inParentheses = false;  // To track if we are inside parentheses

    std::string token;
    std::istringstream stream(input);
    char prevChar = ' ';  // To track previous character (for managing spaces)

    while (stream.get(prevChar)) {
        // If we encounter a single quote, toggle string literal state
        if (prevChar == '\'' || prevChar == '\"') {
            inString = !inString;
            result += prevChar;  // Add the quote to the result
            continue;
        }

        // If we are inside a string or parentheses, just add characters
        if (inString || inParentheses) {
            result += prevChar;
            if (prevChar == '(') inParentheses = true;
            if (prevChar == ')') inParentheses = false;
            continue;
        }

        // Skip multiple spaces (only add one space)
        if (std::isspace(prevChar)) {
            if (!result.empty() && !std::isspace(result.back())) {
                result += ' ';
            }
        }
        else if (prevChar == ',' || prevChar == '(' || prevChar == ')') {
            // Ensure spaces around commas and parentheses
            if (!result.empty() && !std::isspace(result.back()) && result.back() != '(' && result.back() != ')') {
                result += ' ';
            }
            result += prevChar;
            if (prevChar != ')') {
                result += ' ';  // Add space after commas and opening parentheses
            }
        } else {
            // Add regular characters (SQL keywords, table names, etc.)
            result += prevChar;
        }
    }

    // Remove any trailing space
    if (!result.empty() && std::isspace(result.back())) {
        result.pop_back();
    }

    return result;
}

inline std::string clean(const std::string& inputSQL) {
    return formatSQLQuery(cleanStringWithQuotes(removeTrailingSpaces(inputSQL)));
}


// Enum to represent token types
enum class TokenType {
    Keyword,
    Logical,
    Identifier,
    Literal,
    Operator,
    Wildcard,
    OpeningParenthesis,
    ClosingParenthesis,
    Comma,
    Semicolon,
    EndOfFile,
    Invalid
};

inline TokenType determineTokenType(const std::string &value) {
    const std::string toLowerValue = toLower(value);  // Convert to lowercase once to simplify comparisons
    static const std::set<std::string> keywords = {
        "select", "insert", "update", "delete", "drop", "create", "use", "where", "from"
    };

    // Logical operators
    if (toLowerValue == "and" || toLowerValue == "or" || toLowerValue == "not") {
        return TokenType::Logical;
    }

    // Keywords like SELECT, INSERT, WHERE, etc.
    if (keywords.contains(toLowerValue)) {
        return TokenType::Keyword;
    }

    // Handle operators, including multi-character ones like <=, >=, !=
    static const std::set<std::string> operators = {
        "=", "<", ">", "+", "-", "/", "%", "<=", ">=", "==", "!="
    };
    if (operators.contains(toLowerValue)) {
        return TokenType::Operator;
    }

    // Check for wildcard (asterisk) symbol, commonly used in SELECT statements
    if (value == "*") {
        return TokenType::Wildcard;
    }

    // Handle numeric literals (anything that starts with a number)
    if (std::isdigit(value[0])) {
        return TokenType::Literal;
    }

    // Handle string literals, single or double quotes
    if ((value[0] == '\'' && value.back() == '\'') || (value[0] == '\"' && value.back() == '\"')) {
        return TokenType::Literal;
    }

    // Default case: treat as identifier (e.g., table names, column names)
    return TokenType::Identifier;
}


// Token struct to hold the token's type and value
struct Token {
    TokenType type;
    std::string value;
};

inline std::string to_string(const TokenType type) {
    switch (type) {
        case TokenType::Keyword: return "Keyword";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Literal: return "Literal";
        case TokenType::Operator: return "Operator";
        case TokenType::OpeningParenthesis: return "OpeningParenthesis";
        case TokenType::ClosingParenthesis: return "ClosingParenthesis";
        case TokenType::Comma: return "Comma";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::EndOfFile: return "EndOfFile";
        case TokenType::Invalid: return "Invalid";
        case TokenType::Logical: return "Logical";
        case TokenType::Wildcard: return "Wildcard";
        default: return "Unknown";
    }
}

// Tokenize function
// Function to split the SQL query and store tokens in a vector
inline std::vector<Token> tokenize(const std::string &input) {
    std::string temp;
    bool insideDoubleQuotes = false;
    bool insideSingleQuotes = false;

    // Vector to store tokens
    std::vector<Token> tokens;

    for (size_t i = 0; i < input.length(); ++i) {
        char currentChar = input[i];

        // Toggle the insideQuotes flag when encountering double or single quotes
        if (currentChar == '"') {
            insideDoubleQuotes = !insideDoubleQuotes;
            temp += currentChar;  // Keep the quote in the substring
        } else if (currentChar == '\'') {
            insideSingleQuotes = !insideSingleQuotes;
            temp += currentChar;  // Keep the quote in the substring
        } else if (currentChar == ' ' && !insideDoubleQuotes && !insideSingleQuotes) {
            // If we are outside quotes and encounter a space, add the current substring to tokens
            if (!temp.empty()) {
                Token token;
                token.value = temp;    // Set the value to the current temp substring
                token.type = determineTokenType(token.value);
                tokens.push_back(token); // Add the token to the vector
                temp.clear();  // Clear the temp string for the next token
            }
        } else {
            // Add the character to the current substring
            temp += currentChar;
        }
    }

    // If there's any remaining content in temp, add it as a token
    if (!temp.empty()) {
        Token token;
        token.type = TokenType::EndOfFile;  // Set the type to "empty"
        token.value = temp;    // Set the value to the current temp substring
        tokens.push_back(token); // Add the token to the vector
    }

    return tokens;
}

// Function to display tokens
inline void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "Token Type: ";
        switch (token.type) {
            case TokenType::Keyword:
                std::cout << "Keyword";
                break;
            case TokenType::Identifier:
                std::cout << "Identifier";
                break;
            case TokenType::Literal:
                std::cout << "Literal";
                break;
            case TokenType::Operator:
                std::cout << "Operator";
                break;
            case TokenType::OpeningParenthesis:
                std::cout << "Opening Parenthesis";
                break;
            case TokenType::ClosingParenthesis:
                std::cout << "Closing Parenthesis";
                break;
            case TokenType::Comma:
                std::cout << "Comma";
                break;
            case TokenType::Semicolon:
                std::cout << "Semicolon";
                break;
            default:
                std::cout << "Invalid";
                break;
        }
        std::cout << ", Value: '" << token.value << "'" << std::endl;
    }
}

