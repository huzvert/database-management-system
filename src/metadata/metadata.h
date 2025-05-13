#pragma once
#include <iostream>
int init();
int addDatabase(const std::string& dbName);
int addTable(const std::string& dbName, const std::string& tableName);
int addColumn(const std::string& dbName, const std::string& tableName, const std::string& columnName, const std::string& columnType, int position, bool isPK = false);
int removeDatabase(const std::string& dbName);
int removeColumn(const std::string& dbName, const std::string& tableName, const std::string& columnName);
int removeTable(const std::string& dbName, const std::string& tableName);