#pragma once

#include <string>
#include <regex>

inline std::string toLower(const std::string& str) {
  std::string result = str;
  for (char& c : result) {
    c = std::tolower(static_cast<unsigned char>(c));
  }
  return result;
}

struct variantDate {
  std::string date;

  explicit variantDate(const std::string& date) {
    this->date = date;
  }
};

enum OperandType {
  CHAR_,
  DATE_,
  INT_,
  BOOL_,
  IDENTIFIER_,
  ERROR_
};

inline DataType getDataType(const OperandType op) {
  switch (op) {
    case CHAR_:
      return DataType::CHAR;
    case INT_:
      return DataType::INT;
    case BOOL_:
      return DataType::BOOL;
    case DATE_:
      return DataType::DATE;
    default:
      return NONE;
  }
}


inline bool strToBool(const std::string& str) {
  if (str == "true" || str == "TRUE") {
    return true;
  }
  if (str == "false" || str == "FALSE") {
    return false;
  }
  return false;
}

inline void getOperandTypes(const std::string& a, const std::string& b, OperandType& aType, OperandType& bType) {
  // Check if it's a string literal
  if ((a.at(0) == '"' || a.at(0) == '\'') && std::regex_match(a, std::regex(R"(\d{4}-\d{2}-\d{2})"))) {
    // It's a date literal in the format YYYY-MM-DD
    aType = DATE_;
  } else if (a.at(0) == '"' || a.at(0) == '\'') {
    // It's a string literal
    aType = CHAR_;
  } else if (std::ranges::all_of(a, ::isdigit)) {
    // It's a number (integer)
    aType = INT_;
  } else if (a ==  "true" || a == "TRUE" || a == "FALSE" || a == "false") {
    // It's a boolean literal
    aType = BOOL_;
  } else {
    // It's an identifier (column name)
    aType = IDENTIFIER_;
  }

  // Repeat the same checks for b
  if ((b.at(0) == '"' || b.at(0) == '\'') && std::regex_match(b, std::regex(R"(\d{4}-\d{2}-\d{2})"))) {
    // It's a date literal in the format YYYY-MM-DD
    bType = DATE_;
  } else if (b.at(0) == '"' || b.at(0) == '\'') {
    // It's a string literal
    bType = CHAR_;
  } else if (std::ranges::all_of(b, ::isdigit)) {
    // It's a number (integer)
    bType = INT_;
  } else if (b == "true" || b == "TRUE" || b == "FALSE" || b == "false") {
    // It's a boolean literal
    bType = BOOL_;
  } else {
    // It's an identifier (column name)
    bType = IDENTIFIER_;
  }
}


inline bool checkConditionOnInt(const int a, const int b, const std::string& c) {
  if (c == "=") {
    return a == b;
  }

  if (c == ">") {
    return a > b;
  }

  if (c == "<") {
    return a < b;
  }

  if (c == "<=") {
    return a <= b;
  }

  if (c == ">=") {
    return a >= b;
  }

  if (c == "!=") {
    return a != b;
  }

  if (c == "!>") {
    return a <= b;
  }

  if (c == "!<") {
    return a >= b;
  }

  return false; // Default case if the operator is not recognized
}

inline bool checkConditionOnBool(const bool a, const bool b, const std::string& c) {
  if (c == "=") {
    return a == b;
  }
  if (c == ">" || c == "<" || c == "!>" || c == "!<") {
    return false;
  }
  if (c == "!=") {
    return a != b;
  }
  return false;
}

inline std::string removeSingleQuotes(const std::string& input) {
  std::string result;
  for (const char c : input) {
    if (c != '\'') {
      result += c;
    }
  }
  return result;
}

inline bool checkConditionOnDate(const std::string& a_, const std::string& b_, const std::string& op) {
  std::cout << "Debug: Comparing dates - " << a_ << " " << op << " " << b_ << std::endl;

  std::string a = removeSingleQuotes(a_);
  std::string b = removeSingleQuotes(b_);

  if (a.length() != 10 || b.length() != 10) {
    std::cout << "Invalid date format!!!!!!!!!!!!!: " << a << ", " << b << std::endl;
    return false;
  }

  if (op == "=") return a == b;
  if (op == ">") return a > b;
  if (op == "<") return a < b;
  if (op == ">=") return a >= b;
  if (op == "<=") return a <= b;
  if (op == "!=") return a != b;

  std::cout << "Invalid operator: " << op << std::endl;
  return false;
}

inline bool checkConditionOnChar(const std::string& a, const std::string& b, const std::string& op) {

  if (op == "=") return a == b;
  if (op == ">") return a > b;
  if (op == "<") return a < b;
  if (op == ">=") return a >= b;
  if (op == "<=") return a <= b;
  if (op == "!=") return a != b;

  std::cout << "Invalid operator: " << op << std::endl;
  return false;
}


inline bool checkCondition(const std::variant<int, bool, std::string>& left, const std::variant<int, bool, std::string>& right, const std::string& op, const bool isDate = false) {
  // Check if both left and right are of the same type
  if (left.index() != right.index()) {
    return false;  // If they are of different types, return false
  }

  if (isDate) {

  }

  if (left.index() == 0) {
    // Extract int values from the variants and check the condition
    return checkConditionOnInt(std::get<int>(left), std::get<int>(right), op);
  }

  if (left.index() == 1) {
    return checkConditionOnBool(std::get<bool>(left), std::get<bool>(right), op);
  }

  if (left.index() == 2) {
    if (isDate) {
      return checkConditionOnDate(std::get<std::string>(left), std::get<std::string>(right), op);
    }
    return checkConditionOnChar(std::get<std::string>(left), std::get<std::string>(right), op);
  }

  std::cout << "Invalid. Did not execute any function." << std::endl;
  return false;
}

inline void tabulate(const std::string &jsonString) {
  // Parse the JSON string
  nlohmann::json parsedData = nlohmann::json::parse(jsonString);

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
