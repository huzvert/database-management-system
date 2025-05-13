#pragma once
#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "src/query/antlr/SQLParser.h"
#include "src/query/antlr/MySQLListener.h"

#include "src/metadata/metadata_structures.h"
#include "src/metadata/metadata.h"
#include "src/storage/storage_engine.h"
#include "src/metadata/json.hpp"
#include "src/utils/utils.h"


class SQLExecutor final : public SQLBaseListener {
public:
    Metadata &metadata;
    std::string result;
    std::string statusResult;

    explicit SQLExecutor(Metadata &metadata) : metadata(metadata) {}

    [[nodiscard]] std::string getResult() const {
        return result;
    }

    void display() const {
        std::cout << getResult() << std::endl;
    }

    void execute(SQLParser::StatementContext *context) {
        if (context->createDatabase()) {
            enterCreateDatabase(context->createDatabase());
        } else if (context->createTable()) {
            enterCreateTable(context->createTable());
        } else if (context->dropDatabase()) {
            enterDropDatabase(context->dropDatabase());
        } else if (context->dropTable()) {
            enterDropTable(context->dropTable());
        } else if (context->useDatabase()) {
            enterUseDatabase(context->useDatabase());
        } else if (context->insertInto()) {
            enterInsertInto(context->insertInto());
        } else if (context->selectStatement()) {
            enterSelectStatement(context->selectStatement());
        } else if (context->listDatabases()) {
            enterListDatabases(context->listDatabases());
        } else if (context->deleteStatement()) {
            enterDeleteStatement(context->deleteStatement());
        }
        else {
            statusResult = "Unsupported SQL statement.";
            return;
        }


        // At the end, return the final result after all execution steps
        statusResult = "Statement executed successfully.";
    }

    void enterCreateDatabase(SQLParser::CreateDatabaseContext *ctx) override {
        const int status = addDatabase(ctx->databaseName()->getText());

        nlohmann::json jsonResult;
        jsonResult["databaseName"] = ctx->databaseName()->getText();

        if (status == 1) {
            jsonResult["status"] = "error";
            jsonResult["message"] = "Database already exists.";
        } else if (status == 0) {
            jsonResult["status"] = "success";
            jsonResult["message"] = "Database created successfully.";
            metadata.addDatabase(ctx->databaseName()->getText());
        } else {
            jsonResult["status"] = "error";
            jsonResult["message"] = "Unknown error creating database.";
        }

        result = jsonResult.dump(); // Convert JSON object to string
    }

    void enterCreateTable(SQLParser::CreateTableContext *ctx) override {
    // GET TABLE AND DATABASE NAMES
    std::string fullTableName = ctx->tableName()->getText(); // Get table name (with or without a dot)
    std::string databaseName, tableName;

    size_t dotPos = fullTableName.find('.'); // Check for qualified table name
    if (dotPos != std::string::npos) {
        // Extract database name and table name
        databaseName = fullTableName.substr(0, dotPos);
        tableName = fullTableName.substr(dotPos + 1);
    } else if (metadata.databaseInUse.name.empty()) {
        // No active database and no qualified name provided
        nlohmann::json errorJson = {{"error", "No database is currently in use. Specify a database name or use a fully qualified table name."}};
        result = errorJson.dump();
        return;
    } else {
        // Use the active database
        databaseName = metadata.databaseInUse.name;
        tableName = fullTableName;
    }
    // ENDS HERE -------------------------------------------------------------------------------------------------------

    // Add the table to the specified database
    const int status = addTable(databaseName, tableName);

    // Create JSON response based on the status
    nlohmann::json responseJson;
    if (status == 0) {
        int pos = 0;
        // First, handle primary key if it exists
        if (ctx->primaryKeyDeclaration() != nullptr) {
            const std::string pkColumn = ctx->primaryKeyDeclaration()->IDENTIFIER()->getText();  // Get the primary key column name
            std::string pkType;

            // Find the column definition that matches the primary key column and get its type
            for (const auto columnDef : ctx->columnDefinition()) {
                if (columnDef->IDENTIFIER()->getText() == pkColumn) {
                    pkType = columnDef->dataType()->getText();
                    // std::cout << "PRIMARY KEY: " << pkColumn << pkType <<"\n\n\n";
                    break;
                }
            }

            // Add PK column at position 0
            addColumn(databaseName, tableName, pkColumn, pkType, 0, true);
            pos++;
            metadata.addTable(databaseName, tableName);
            metadata.getTable(databaseName, tableName)->addColumn(pkColumn, pkType, 0, true);
        }

        else {
            result = "NO PRIMARY KEY.";
            return;
        }


        for (int i = 0; i < ctx->columnDefinition().size(); i++) {
            std::string columnName = ctx->columnDefinition(i)->IDENTIFIER()->getText();
            std::string columnType = ctx->columnDefinition(i)->dataType()->getText();


            // Check if the column is the primary key
            if (ctx->primaryKeyDeclaration() != nullptr &&
                ctx->primaryKeyDeclaration()->IDENTIFIER()->getText() == columnName) {
                // do not insert this
                continue;
                }

            // insert this.
            addColumn(databaseName, tableName, columnName, columnType, pos, false);
            metadata.getTable(databaseName, tableName)->addColumn(columnName, columnType, pos++, false);
        }

        responseJson["success"] = "Table \"" + tableName + "\" created successfully in database \"" + databaseName + "\".";

        // errors.
    } else if (status == 1) {
        responseJson["error"] = "Database \"" + databaseName + "\" not found.";
    } else if (status == 2) {
        responseJson["error"] = "Table \"" + tableName + "\" already exists in database \"" + databaseName + "\".";
    } else if (status == -1) {
        responseJson["error"] = "An unknown error occurred while creating table \"" + tableName + "\" in database \"" + databaseName + "\".";
    }

    result = responseJson.dump(); // Convert the JSON object to a string
}

    void enterDropTable(SQLParser::DropTableContext *ctx) override {
        std::string fullTableName = ctx->tableName()->getText(); // Get table name (with or without a dot)
        std::string databaseName, tableName;

        size_t dotPos = fullTableName.find('.'); // Check for qualified table name
        if (dotPos != std::string::npos) {
            // Extract database name and table name
            databaseName = fullTableName.substr(0, dotPos);
            tableName = fullTableName.substr(dotPos + 1);
        } else if (metadata.databaseInUse.name.empty()) {
            // No active database and no qualified name provided
            result = nlohmann::json({{"error", "No database is currently in use. Specify a database name or use a fully qualified table name."}}).dump();
            return;
        } else {
            // Use the active database
            databaseName = metadata.databaseInUse.name;
            tableName = fullTableName;
        }

        int status = removeTable(databaseName, tableName);

        if (status == 0) {
            metadata.removeTable(databaseName, tableName);
            // metadata.load();
            result = nlohmann::json({
                {"success", "Table \"" + tableName + "\" removed successfully from database \"" + databaseName + "\"."}
            }).dump();
        } else if (status == -2) {
            result = nlohmann::json({
                {"error", "Database \"" + databaseName + "\" not found."}
            }).dump();
        } else if (status == -3) {
            result = nlohmann::json({
                {"error", "Table \"" + tableName + "\" not found in database \"" + databaseName + "\"."}
            }).dump();
        } else if (status == -1) {
            result = nlohmann::json({
                {"error", "An unknown error occurred while removing table \"" + tableName + "\" in database \"" + databaseName + "\"."}
            }).dump();
        }
    }

    void enterDropDatabase(SQLParser::DropDatabaseContext *ctx) override {
        // Create a JSON object for the result
        nlohmann::json resultJson;

        // Get the database name
        std::string dbName = ctx->databaseName()->getText();

        // Call the removeDatabase function to remove the database
        int status = removeDatabase(dbName);

        if (status == 0) {
            metadata.removeDatabase(dbName);
            resultJson["success"] = "Database \"" + dbName + "\" removed successfully.";
        } else if (status == -1) {
            resultJson["error"] = "Database \"" + dbName + "\" not found.";
        } else {
            resultJson["error"] = "An unknown error occurred while removing database \"" + dbName + "\".";
        }

        // Set the result to the JSON string
        result = resultJson.dump(); // Convert JSON object to string
        std::cout << "Error: database with given name does not exist." << std::endl;
    }

    void enterUseDatabase(SQLParser::UseDatabaseContext *ctx) override {
        std::cout << "USE FUNCTION CALLED." << std::endl;
        // check if database exists
        if (const std::string databaseName = ctx->databaseName()->getText(); metadata.databaseExists(databaseName)) {
            std::cout << "Database Exists" << std::endl;

            if (const auto it = metadata.databases.find(databaseName); it != metadata.databases.end()) {
                metadata.databaseInUse.name = databaseName;
                std::cout << "Default database set to " + databaseName + "." << std::endl;
                result = "Default database set to " + databaseName + ".";
            }
        }
        else {
            std::cout << "Database not found. Please create a database or use a valid database." << std::endl;
            result = "Database not found. Please create or use a valid database.";
        }
    }

    void enterInsertInto(SQLParser::InsertIntoContext *ctx) override {
    std::string fullTableName = ctx->tableName()->getText();  // Get the table name

    // Check if the table name contains a dot
    const size_t dotPos = fullTableName.find('.');

    std::string databaseName, tableName;
    if (dotPos != std::string::npos) {
        // Split the table name into database and table
        databaseName = fullTableName.substr(0, dotPos);
        tableName = fullTableName.substr(dotPos + 1);
    } else if (metadata.databaseInUse.name.empty()) {
        result = "Error: No database in use. Please specify a database.";
        return;
    } else {
        // Use the default database
        databaseName = metadata.databaseInUse.name;
        if (databaseName.empty()) {
            result = "Error: No default database specified.";
            return;
        }
        tableName = fullTableName;
    }

    std::cout << "Executing INSERT INTO table: " << tableName << " in database: " << databaseName << std::endl;

    // Check if the table exists
    if (!metadata.tableExists(databaseName, tableName)) {
        result = "Error: Table " + tableName + " does not exist in database " + databaseName;
        return;
    }

    // Get column names from columnList (if available)
    std::vector<std::string> insertColumns;
    if (ctx->columnList() != nullptr) {
        for (auto column : ctx->columnList()->IDENTIFIER()) {
            insertColumns.push_back(column->getText());
        }
    }

    // Validate columns (Ensure columns in insert statement match the table's columns)
    auto tableMetadata = metadata.getTable(databaseName, tableName);
    std::set<std::string> tableColumns;
    for (const auto& column : tableMetadata->columns) {
        tableColumns.insert(column.name); // Assuming column has a 'name' attribute
    }

    for (const auto& columnName : insertColumns) {
        if (tableColumns.find(columnName) == tableColumns.end()) {
            std::cerr << "Error: Column " << columnName << " does not exist in table "
                      << tableName << std::endl;
            return;
        }
    }

    // Get values from valueList and match them to columns in the right order
    std::vector<std::string> insertValues;
    for (auto value : ctx->valueList()->value()) {
        insertValues.push_back(value->getText());
    }

    // Sort the columns based on the table's column order
    std::vector<std::string> sortedValues(tableMetadata->columns.size(), "");

    for (size_t i = 0; i < insertColumns.size(); ++i) {
        for (size_t j = 0; j < tableMetadata->columns.size(); ++j) {
            if (insertColumns[i] == tableMetadata->columns[j].name) {
                sortedValues[j] = insertValues[i];
                break;
            }
        }
    }

    // Print the sorted values for debugging
    std::cout << "Sorted row values: ";
    for (const auto& value : sortedValues) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Prepare data for insertion into index and data files
        std::vector<Data> dataToInsert;
        for (int i = 0; i < sortedValues.size(); i++) {
            const auto& column = tableMetadata->columns[i];

            if (column.type == "INT" || column.type == "INTEGER") {
                try {
                    // Convert string to INT
                    int intValue = std::stoi(sortedValues[i]);
                    dataToInsert.emplace_back(INT, intValue);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid INT value: " << sortedValues[i] << std::endl;
                    return;
                }
            }
            else if (column.type == "DATE") {
                // Assume DATE is stored as a string
                dataToInsert.emplace_back(DATE, sortedValues[i]);
            }
            else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                // Convert string to BOOL (true/false)
                std::string value = sortedValues[i];
                std::transform(value.begin(), value.end(), value.begin(), ::tolower); // Convert to lowercase for comparison

                if (value == "true") {
                    dataToInsert.emplace_back(BOOL, true);
                } else if (value == "false") {
                    dataToInsert.emplace_back(BOOL, false);
                } else {
                    std::cerr << "Invalid BOOL value: " << sortedValues[i] << std::endl;
                    return;
                }
            }

            /*
            else if (column.type == "CHAR") {
                // For CHAR, handle string with potential padding
                dataToInsert.emplace_back(CHAR, sortedValues[i], column.charLength);
            }
            */
            std::cout << "Successful\n";
        }

    // Always treat the first column as the primary key and insert into the index
    int status = insertToIndexFile(databaseName, tableName, dataToInsert[0].toCharPtr(), tableMetadata->lastFreeBlock);
    if (status == 0) {
        int statusDataFile = insertToDataFile(dataToInsert, databaseName, tableName, metadata);
        if (statusDataFile == 0) {
            result = "successfully inserted";
        }
        else {
            result = "failed to insert in data file";
        }
    }
    else {
        std::cout << "KEYYYYYYYYYYYYYYYYYYYYYYYYYY EXISTS" << std::endl;
        result = "failed to insert in index file";
    }
}

    void enterListDatabases(SQLParser::ListDatabasesContext *ctx) override {
        metadata.displayAllDatabases();
    }

    void enterSelectStatement(SQLParser::SelectStatementContext *ctx) override {
        // get table and database names
        std::string fullTableName = ctx->tableName()->getText();
        std::string databaseName, tableName;

        // check if in the form of <database name>.<table name>
        size_t dotPos = fullTableName.find('.'); // Check for qualified table name
        if (dotPos != std::string::npos) {
            // extract database name and table name
            databaseName = fullTableName.substr(0, dotPos);
            tableName = fullTableName.substr(dotPos + 1);
        } else if (metadata.databaseInUse.name.empty()) {
            // no active database AND no database name provided
            nlohmann::json errorJson = {{"error", "No database is currently in use. Specify a database name or use a fully qualified table name."}};
            result = errorJson.dump();
            return;
        } else {
            // use the active database
            databaseName = metadata.databaseInUse.name;
            tableName = fullTableName;
        }
        // ENDS HERE ---------------------------------------------------------------------------------------------------

        // get list of columns
        std::string columnListText = ctx->columnList()->getText();

        // check if column list is wildcard "*"
        // if yes, select all columns.
        if (columnListText == "*") {
            // check if there is a condition
            if (ctx->condition()) {
                std::string op;
                std::string rightString;
                std::string leftString;

                std::cout << "This is a SELECT * with a WHERE condition." << std::endl;

                leftString = ctx->condition()->IDENTIFIER()->getText();
                rightString = ctx->condition()->value()->getText();
                op = ctx->condition()->comparisonOperator()->getText();


                // select all rows
                // then for each one apply a filter.

                // vector of output rows.
                std::vector<Data> rows;

                // vector of DataType objects, for readFromFile function.
                std::vector<DataType> dataTypes;

                Table_m* table_m;
                // get table metadata, and last block.

                table_m = metadata.getTable(databaseName, tableName);
                if (table_m == nullptr) {
                    return;
                }
                int lastBlock = table_m->lastFreeBlock;

                // add values to the vector of DataTypes
                for (const auto& column : metadata.getTable(databaseName, tableName)->columns) {
                    if (column.type == "INT" || column.type == "INTEGER") {
                        dataTypes.emplace_back(INT);
                    }
                    else if (column.type == "DATE") {
                        dataTypes.emplace_back(DATE);
                    }
                    else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                        dataTypes.emplace_back(BOOL);
                    }
                }

                // read all blocks data. insert to vector.
                for (int i = 0; i <= lastBlock; i++) {
                    std::vector<Data> temp_data = readFromFile(databaseName, tableName, i, metadata, dataTypes);
                    rows.insert(rows.end(), temp_data.begin(), temp_data.end());  // More efficient insertion
                }

                // vector for filtered rows.
                std::vector<Data> filteredRows;

                // get table metadata
                Table_m* filteredTable_m = metadata.getTable(databaseName, tableName);
                std::string dataTypeOfCondition = filteredTable_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->type;
                int position = filteredTable_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->order;

                for (int i = 0; i < rows.size(); i = i + dataTypes.size()) {
                    bool evaluated = false;
                    if (dataTypeOfCondition == "INT" || dataTypeOfCondition == "INTEGER") {
                        try {
                            int value = std::get<int>(rows[i + position].value); // Extract the int
                            evaluated = checkCondition(value, stoi(rightString), op);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }

                    else if (dataTypeOfCondition == "DATE") {
                        try {
                            // get string of date
                            auto value = std::get<std::string>(rows[i + position].value);
                            evaluated = checkCondition(value, rightString, op, true);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error HERE. : " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }

                    else if (dataTypeOfCondition == "BOOL" || dataTypeOfCondition == "BOOLEAN") {
                        try {
                            // get string of date
                            auto value = std::get<bool>(rows[i + position].value);
                            evaluated = checkCondition(value, strToBool(rightString), op);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error HERE. : " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }
                    if (evaluated) {
                        std::cout << "True\n";
                        for (int j = 0; j < dataTypes.size(); j++) {
                            filteredRows.emplace_back(rows[i + j]);
                        }
                    }
                }

                // temp JSON object to build result
                nlohmann::json jsonResult;

                // store column names
                std::vector<std::string> columns;
                for (auto & column : table_m->columns) {
                    columns.push_back(column.name);
                }
                // add columns to the JSON object
                jsonResult["columns"] = columns;


                // loop through each row to add data.

                // stores data of each row.
                std::vector<nlohmann::json> data;

                for (int i = 0; i < filteredRows.size(); i += dataTypes.size()) {
                    nlohmann::json jsonObject;
                    for (int j = 0; j < dataTypes.size(); j++) {
                        // Match column name to its value
                        jsonObject[columns[j]] = filteredRows[i + j].toString();
                    }
                    data.push_back(jsonObject);
                }

                jsonResult["data"] = data;

                // convert the final JSON object to a string
                result = jsonResult.dump(4);    // use dump 0 before compiling, so less memory is needed.
                tabulate(result);
            }

            // no condition, select all rows.
            else {
                std::cout << "This is a SELECT * without a WHERE condition." << std::endl;
                // vector of output rows.
                std::vector<Data> rows;

                // vector of DataType objects, for readFromFile function.
                std::vector<DataType> dataTypes;

                // get table metadata, and last block.
                Table_m* table_m = metadata.getTable(databaseName, tableName);
                if (table_m == nullptr) {
                    return;
                }
                int lastBlock = table_m->lastFreeBlock;
                std::cout << lastBlock << std::endl;

                if (lastBlock == 0 && table_m->rowsInLastFreeBlock == 0) {
                    result = "TABLE IS EMPTY";
                    return;
                }

                // add values to the vector of DataTypes
                for (const auto& column : metadata.getTable(databaseName, tableName)->columns) {
                    if (column.type == "INT" || column.type == "INTEGER") {
                        dataTypes.emplace_back(INT);
                    }
                    else if (column.type == "DATE") {
                        dataTypes.emplace_back(DATE);
                    }
                    else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                        dataTypes.emplace_back(BOOL);
                    }
                }

                // read all blocks data. insert to vector.
                for (int i = 0; i <= lastBlock; i++) {
                    std::vector<Data> temp_data = readFromFile(databaseName, tableName, i, metadata, dataTypes);
                    rows.insert(rows.end(), temp_data.begin(), temp_data.end());  // More efficient insertion
                }


                // temp JSON object to build result
                nlohmann::json jsonResult;

                // Store column names
                std::vector<std::string> columns;
                for (auto & column : table_m->columns) {
                    columns.push_back(column.name);
                }
                // Add columns to the JSON object
                jsonResult["columns"] = columns;


                // Loop through each row to add data.

                // stores data of each row.
                std::vector<nlohmann::json> data;

                for (int i = 0; i < rows.size(); i += dataTypes.size()) {
                    nlohmann::json jsonObject;
                    for (int j = 0; j < dataTypes.size(); j++) {
                        // Match column name to its value
                        jsonObject[columns[j]] = rows[i + j].toString();
                    }
                    data.push_back(jsonObject);  // Add the row to the data array
                }

                jsonResult["data"] = data;  // Add data to the JSON object

                // Convert the final JSON object to a string
                result = jsonResult.dump(4);    // use dump 0 before compiling, so less memory is needed.
                tabulate(result);         }
        }

        else {
            if (ctx->condition()) {
                std::cout << "This is a SELECT SUBSET with a WHERE condition." << std::endl;

                std::string op;
                std::string rightString;
                std::string leftString;

                leftString = ctx->condition()->IDENTIFIER()->getText();
                rightString = ctx->condition()->value()->getText();
                op = ctx->condition()->comparisonOperator()->getText();


                // select all rows
                // then for each one apply a filter.

                // vector of output rows.
                std::vector<Data> rows;

                // vector of DataType objects, for readFromFile function.
                std::vector<DataType> dataTypes;

                // get table metadata, and last block.
                Table_m* table_m;
                table_m = metadata.getTable(databaseName, tableName);
                if (table_m == nullptr) {
                    return;
                }
                int lastBlock = table_m->lastFreeBlock;

                // add values to the vector of DataTypes
                for (const auto& column : metadata.getTable(databaseName, tableName)->columns) {
                    if (column.type == "INT" || column.type == "INTEGER") {
                        dataTypes.emplace_back(INT);
                    }
                    else if (column.type == "DATE") {
                        dataTypes.emplace_back(DATE);
                    }
                    else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                        dataTypes.emplace_back(BOOL);
                    }
                }

                // read all blocks data. insert to vector.
                for (int i = 0; i <= lastBlock; i++) {
                    std::vector<Data> temp_data = readFromFile(databaseName, tableName, i, metadata, dataTypes);
                    rows.insert(rows.end(), temp_data.begin(), temp_data.end());  // More efficient insertion
                }

                // now filter by condition.
                // vector for filtered rows.
                std::vector<Data> filteredByCondition;

                std::string dataTypeOfCondition = table_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->type;
                int position = table_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->order;

                for (int i = 0; i < rows.size(); i = i + dataTypes.size()) {
                    bool evaluated = false;
                    if (dataTypeOfCondition == "INT" || dataTypeOfCondition == "INTEGER") {
                        try {
                            int value = std::get<int>(rows[i + position].value); // Extract the int
                            evaluated = checkCondition(value, stoi(rightString), op);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }

                    else if (dataTypeOfCondition == "DATE") {
                        try {
                            // get string of date
                            std::string value = std::get<std::string>(rows[i + position].value);
                            evaluated = checkCondition(value, rightString, op, true);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }

                    else if (dataTypeOfCondition == "BOOL" || dataTypeOfCondition == "BOOLEAN") {
                        try {
                            // get string of date
                            auto value = std::get<bool>(rows[i + position].value);
                            evaluated = checkCondition(value, strToBool(rightString), op);
                        } catch (const std::bad_variant_access& e) {
                            std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                        }
                    }

                    if (evaluated) {
                        std::cout << "True\n";
                        for (int j = 0; j < dataTypes.size(); j++) {
                            filteredByCondition.emplace_back(rows[i + j]);
                        }
                    }
                }


                // now rows need to be filtered by column.

                // vector to store columns of result
                std::vector<std::string> columns;
                for (auto & i : ctx->columnList()->children) {
                    if (i->getText() != ",") {
                        columns.push_back(i->getText());
                        std::cout << "Stored column: " << i->getText() << std::endl;
                    }
                }

                // make a vector for final, fully filtered rows
                std::vector<Data> filteredRows;


                for (int i = 0; i < filteredByCondition.size(); i++) {
                    std::cout << filteredByCondition[i].toString() << std::endl;
                }


                for (int i = 0; i < filteredByCondition.size(); i = i + dataTypes.size()) {
                    for (int j = 0 ; j < columns.size(); j++) {
                        int pos = table_m->getColumn(columns[j])->order;
                        filteredRows.emplace_back(filteredByCondition[i + pos]);
                    }
                }
                std::cout << "Filtered by columns\n";
                // temp JSON object to build result
                nlohmann::json jsonResult;

                // add columns to the JSON object
                jsonResult["columns"] = columns;


                // loop through each row to add data.

                // stores data of each row.
                std::vector<nlohmann::json> data;

                // final loop to convert filtered rows to JSON
                // stores data of each row.
                for (int i = 0; i < filteredRows.size(); i += columns.size()) {
                    nlohmann::json jsonObject;
                    for (int j = 0; j < columns.size(); j++) {
                        // Match column name to its value
                        jsonObject[columns[j]] = filteredRows[i + j].toString();
                    }
                    data.push_back(jsonObject);  // Add the row to the data array
                }

                jsonResult["data"] = data;  // Add data to the JSON object

                // Convert the final JSON object to a string
                result = jsonResult.dump(4);    // use dump 0 before compiling, so less memory is needed.
                tabulate(result);


            }

            else {
                std::cout << "This is a SELECT SUBSET without a WHERE condition." << std::endl;
                // select all rows.

                std::string leftString;
                std::string op;
                std::string rightString;

                // vector of DataType objects, for readFromFile function.
                std::vector<DataType> dataTypes;

                // get table metadata, and last block.
                Table_m* table_m = metadata.getTable(databaseName, tableName);
                if (table_m == nullptr) {
                    return;
                }
                int lastBlock = table_m->lastFreeBlock;

                // add values to the vector of DataTypes
                for (const auto& column : metadata.getTable(databaseName, tableName)->columns) {
                    if (column.type == "INT" || column.type == "INTEGER") {
                        dataTypes.emplace_back(INT);
                    }
                    else if (column.type == "DATE") {
                        dataTypes.emplace_back(DATE);
                    }
                    else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                        dataTypes.emplace_back(BOOL);
                    }
                }

                // now read all blocks from file one by one, and add to list of unfiltered rows.
                std::vector<Data> rows;
                for (int i = 0; i <= lastBlock; i++) {
                    std::vector<Data> temp  = readFromFile(databaseName, tableName, i, metadata, dataTypes);
                    rows.insert(rows.end(), temp.begin(), temp.end());  // More efficient insertion
                }

                for (auto & row : rows) {
                    std::cout << row.toString() << std::endl;
                }

                // get and store column names
                std::vector<std::string> columns;
                for (auto & i : ctx->columnList()->children) {
                    if (i->getText() != ",") {
                        columns.push_back(i->getText());
                    }
                }

                // loop through rows
                std::vector<Data> filteredRows;
                // loop through rows
                // offset = pos
                for (int i = 0; i < rows.size(); i = i + dataTypes.size()) {
                    for (int j = 0 ; j < columns.size(); j++) {
                        int pos = table_m->getColumn(columns[j])->order;
                        filteredRows.emplace_back(rows[i + pos]);
                    }
                }

                for (int i = 0; i < filteredRows.size(); i++) {
                    std::cout << filteredRows[i].toString() << std::endl;
                }

                // temp JSON object to build result
                nlohmann::json jsonResult;

                // Add columns to the JSON object
                jsonResult["columns"] = columns;

                // make a vector of json objects
                std::vector<nlohmann::json> data;

                // final loop to convert filtered rows to JSON
                // stores data of each row.
                for (int i = 0; i < filteredRows.size(); i += columns.size()) {
                    nlohmann::json jsonObject;
                    for (int j = 0; j < columns.size(); j++) {
                        // Match column name to its value
                        jsonObject[columns[j]] = filteredRows[i + j].toString();
                    }
                    data.push_back(jsonObject);  // Add the row to the data array
                }

                jsonResult["data"] = data;  // Add data to the JSON object

                // Convert the final JSON object to a string
                result = jsonResult.dump(4);    // use dump 0 before compiling, so less memory is needed.
                tabulate(result);
            }
        }
    }

    void enterDeleteStatement(SQLParser::DeleteStatementContext *ctx) override {
        std::cout << "Executing DELETE FROM: " << ctx->tableName()->getText() << std::endl;
        // get table and database names
        std::string fullTableName = ctx->tableName()->getText();
        std::string databaseName, tableName;

        // check if in the form of <database name>.<table name>
        size_t dotPos = fullTableName.find('.'); // Check for qualified table name
        if (dotPos != std::string::npos) {
            // extract database name and table name
            databaseName = fullTableName.substr(0, dotPos);
            tableName = fullTableName.substr(dotPos + 1);
        } else if (metadata.databaseInUse.name.empty()) {
            // no active database AND no database name provided
            nlohmann::json errorJson = {{"error", "No database is currently in use. Specify a database name or use a fully qualified table name."}};
            result = errorJson.dump();
            return;
        } else {
            // use the active database
            databaseName = metadata.databaseInUse.name;
            tableName = fullTableName;
        }
        // ENDS HERE ---------------------------------------------------------------------------------------------------

        // check if condition
        if (ctx->condition()) {
            std::string leftString = ctx->condition()->IDENTIFIER()->getText();
        std::string rightString = ctx->condition()->value()->getText();
        std::string op = ctx->condition()->comparisonOperator()->getText();


        // vector of output rows.
        std::vector<Data> rows;

        // vector of DataType objects, for readFromFile function.
        std::vector<DataType> dataTypes;

        // get table metadata, and last block.
        Table_m* table_m = metadata.getTable(databaseName, tableName);
        int lastBlock = table_m->lastFreeBlock;

        // add values to the vector of DataTypes
        for (const auto& column : metadata.getTable(databaseName, tableName)->columns) {
            if (column.type == "INT" || column.type == "INTEGER") {
                dataTypes.emplace_back(INT);
            }
            else if (column.type == "DATE") {
                dataTypes.emplace_back(DATE);
            }
            else if (column.type == "BOOL" || column.type == "BOOLEAN") {
                dataTypes.emplace_back(BOOL);
            }
        }

        // read all blocks data. insert to vector.
        for (int i = 0; i <= lastBlock; i++) {
            std::vector<Data> temp_data = readFromFile(databaseName, tableName, i, metadata, dataTypes);
            rows.insert(rows.end(), temp_data.begin(), temp_data.end());  // More efficient insertion
        }

        // vector for filtered rows.
        std::vector<Data> filteredRows;

        // get table metadata
        Table_m* filteredTable_m = metadata.getTable(databaseName, tableName);
        std::string dataTypeOfCondition = filteredTable_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->type;
        int position = filteredTable_m->getColumn(ctx->condition()->IDENTIFIER()->getText())->order;

        for (int i = 0; i < rows.size(); i = i + dataTypes.size()) {
            bool evaluated = false;
            if (dataTypeOfCondition == "INT" || dataTypeOfCondition == "INTEGER") {
                try {
                    int value = std::get<int>(rows[i + position].value); // Extract the int
                    evaluated = checkCondition(value, stoi(rightString), op);
                } catch (const std::bad_variant_access& e) {
                    std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                }
            }

            else if (dataTypeOfCondition == "DATE") {
                try {
                    // get string of date
                    auto value = std::get<std::string>(rows[i + position].value);
                    evaluated = checkCondition(value, rightString, op, true);
                } catch (const std::bad_variant_access& e) {
                    std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                }
            }

            else if (dataTypeOfCondition == "BOOL" || dataTypeOfCondition == "BOOLEAN") {
                try {
                    // get string of date
                    auto value = std::get<bool>(rows[i + position].value);
                    evaluated = checkCondition(value, strToBool(rightString), op);
                } catch (const std::bad_variant_access& e) {
                    std::cerr << "Error: " << e.what() << std::endl; // Handle the case where the variant does not hold an int
                }
            }
            if (evaluated) {
                std::cout << "True\n";
                for (int j = 0; j < dataTypes.size(); j++) {
                    filteredRows.emplace_back(rows[i + j]);
                }
            }
        }

        // we filtered the rows based on the condition
        // now loop through each element in filtered rows


        // open the table file ONCE, so repetitive calls are not done
        std::fstream file("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName +
                      ".table", std::ios::in | std::ios::out | std::ios::binary);

        int rowSize = table_m->getRowLength();
        DataType dataType = filteredRows.at(0).datatype;
        int sizeOfDataType;
        if (dataType == INT || dataType == DATE) {
            sizeOfDataType = 4;
        }
        else if (dataType == BOOL) {
            sizeOfDataType = 1;
        }

        for (int i = 0; i < filteredRows.size(); i = i + dataTypes.size()) {
            // we only need i, bcs PK is at i.
            Data pkData = filteredRows[i];

            // search if this row exists in index file, just in case.
            int block = -1;
            searchFromIndexFile(databaseName, tableName, pkData.toCharPtr(), block);
            if (block != -1) {
                int status;
                // row exists in index file
                // attempt to delete it
                status = removeFromIndexFile(databaseName, tableName, pkData.toCharPtr());

                if (status == 0) {
                    // Seek to the start of the block
                    file.seekg(block * BLOCK_SIZE); // Assuming blockSize is the size of a block

                    char rowBuffer[rowSize]; // Buffer to hold data of one row
                    int bytesRead = 0;

                    // Loop through the block by rowSize bytes
                    while (bytesRead < BLOCK_SIZE) {
                        file.read(rowBuffer, rowSize); // Read one row into buffer

                        if (file.gcount() < rowSize) {
                            break;
                        }

                        char pkBytes[sizeOfDataType];
                        std::memcpy(pkBytes, rowBuffer, sizeOfDataType);

                        // Convert pkData to binary format
                        std::vector<unsigned char> pkBinary = convertRowToBinary({pkData});

                        // Check if pkBytes matches the binary primary key representation
                        if (std::memcmp(pkBytes, pkBinary.data(), sizeOfDataType) == 0) {
                            // Mark this row for deletion by setting the last byte to 0xFF
                            rowBuffer[rowSize - 1] = 0xFF; // This marks the row as deleted

                            // Seek back to the position of the row in the file
                            file.seekp(bytesRead);
                            file.write(rowBuffer, rowSize); // Overwrite the row with the modified buffer

                            std::cout << "Marked row for deletion at position " << bytesRead << std::endl;
                            break; // Assuming only one row matches per block
                        }
                        bytesRead += rowSize;
                    }
                }
            }
        }
        }

        else {
            Table_m* table_m = metadata.getTable(databaseName, tableName);
            if (table_m == nullptr) {
                std::cout << "Error: Table does not exist." << std::endl;
                return;
            }
            std::remove(("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName + ".table").c_str());
            std::remove(("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName + ".index").c_str());

            // Recreate the files as empty files
            std::ofstream(("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName + ".table"));
            std::ofstream(("/home/dawud/DSA_DATABASE_PROJECT_FOLDER/databases/" + databaseName + "/" + databaseName + "_" + tableName + ".index"));

            table_m->lastFreeBlock = 0;
            table_m->rowsInLastFreeBlock = 0;

            metadata.save();
            std::cout << "All rows deleted." << std::endl;
        }
    }



    void enterUpdate(SQLParser::UpdateContext *ctx) override {}

};
