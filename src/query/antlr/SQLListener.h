
// Generated from SQL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SQLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SQLParser.
 */
class  SQLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSqlStatement(SQLParser::SqlStatementContext *ctx) = 0;
  virtual void exitSqlStatement(SQLParser::SqlStatementContext *ctx) = 0;

  virtual void enterStatement(SQLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(SQLParser::StatementContext *ctx) = 0;

  virtual void enterListDatabases(SQLParser::ListDatabasesContext *ctx) = 0;
  virtual void exitListDatabases(SQLParser::ListDatabasesContext *ctx) = 0;

  virtual void enterCreateDatabase(SQLParser::CreateDatabaseContext *ctx) = 0;
  virtual void exitCreateDatabase(SQLParser::CreateDatabaseContext *ctx) = 0;

  virtual void enterCreateTable(SQLParser::CreateTableContext *ctx) = 0;
  virtual void exitCreateTable(SQLParser::CreateTableContext *ctx) = 0;

  virtual void enterPrimaryKeyDeclaration(SQLParser::PrimaryKeyDeclarationContext *ctx) = 0;
  virtual void exitPrimaryKeyDeclaration(SQLParser::PrimaryKeyDeclarationContext *ctx) = 0;

  virtual void enterDropTable(SQLParser::DropTableContext *ctx) = 0;
  virtual void exitDropTable(SQLParser::DropTableContext *ctx) = 0;

  virtual void enterDropDatabase(SQLParser::DropDatabaseContext *ctx) = 0;
  virtual void exitDropDatabase(SQLParser::DropDatabaseContext *ctx) = 0;

  virtual void enterInsertInto(SQLParser::InsertIntoContext *ctx) = 0;
  virtual void exitInsertInto(SQLParser::InsertIntoContext *ctx) = 0;

  virtual void enterUpdate(SQLParser::UpdateContext *ctx) = 0;
  virtual void exitUpdate(SQLParser::UpdateContext *ctx) = 0;

  virtual void enterSelectStatement(SQLParser::SelectStatementContext *ctx) = 0;
  virtual void exitSelectStatement(SQLParser::SelectStatementContext *ctx) = 0;

  virtual void enterDeleteStatement(SQLParser::DeleteStatementContext *ctx) = 0;
  virtual void exitDeleteStatement(SQLParser::DeleteStatementContext *ctx) = 0;

  virtual void enterUseDatabase(SQLParser::UseDatabaseContext *ctx) = 0;
  virtual void exitUseDatabase(SQLParser::UseDatabaseContext *ctx) = 0;

  virtual void enterAssignmentList(SQLParser::AssignmentListContext *ctx) = 0;
  virtual void exitAssignmentList(SQLParser::AssignmentListContext *ctx) = 0;

  virtual void enterAssignment(SQLParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(SQLParser::AssignmentContext *ctx) = 0;

  virtual void enterColumnList(SQLParser::ColumnListContext *ctx) = 0;
  virtual void exitColumnList(SQLParser::ColumnListContext *ctx) = 0;

  virtual void enterValueList(SQLParser::ValueListContext *ctx) = 0;
  virtual void exitValueList(SQLParser::ValueListContext *ctx) = 0;

  virtual void enterColumnDefinition(SQLParser::ColumnDefinitionContext *ctx) = 0;
  virtual void exitColumnDefinition(SQLParser::ColumnDefinitionContext *ctx) = 0;

  virtual void enterCondition(SQLParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(SQLParser::ConditionContext *ctx) = 0;

  virtual void enterComparisonOperator(SQLParser::ComparisonOperatorContext *ctx) = 0;
  virtual void exitComparisonOperator(SQLParser::ComparisonOperatorContext *ctx) = 0;

  virtual void enterValue(SQLParser::ValueContext *ctx) = 0;
  virtual void exitValue(SQLParser::ValueContext *ctx) = 0;

  virtual void enterDataType(SQLParser::DataTypeContext *ctx) = 0;
  virtual void exitDataType(SQLParser::DataTypeContext *ctx) = 0;

  virtual void enterDatabaseName(SQLParser::DatabaseNameContext *ctx) = 0;
  virtual void exitDatabaseName(SQLParser::DatabaseNameContext *ctx) = 0;

  virtual void enterTableName(SQLParser::TableNameContext *ctx) = 0;
  virtual void exitTableName(SQLParser::TableNameContext *ctx) = 0;


};

