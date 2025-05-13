#pragma once
#include "SQLBaseListener.h"
#include <iostream>

class MySQLListener : public SQLBaseListener {
public:
    void enterCreateDatabase(SQLParser::CreateDatabaseContext *ctx) override {
        std::cout << "Detected CREATE DATABASE statement\n";
        std::cout << "Database Name: " << ctx->databaseName()->getText() << std::endl;
    }

    // Other overrides for SELECT, CREATE TABLE, etc.
};
