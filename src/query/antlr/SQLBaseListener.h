
// Generated from SQL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SQLListener.h"


/**
 * This class provides an empty implementation of SQLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SQLBaseListener : public SQLListener {
public:

  virtual void enterSqlStatement(SQLParser::SqlStatementContext * /*ctx*/) override { }
  virtual void exitSqlStatement(SQLParser::SqlStatementContext * /*ctx*/) override { }

  virtual void enterStatement(SQLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(SQLParser::StatementContext * /*ctx*/) override { }

  virtual void enterListDatabases(SQLParser::ListDatabasesContext * /*ctx*/) override { }
  virtual void exitListDatabases(SQLParser::ListDatabasesContext * /*ctx*/) override { }

  virtual void enterCreateDatabase(SQLParser::CreateDatabaseContext * /*ctx*/) override { }
  virtual void exitCreateDatabase(SQLParser::CreateDatabaseContext * /*ctx*/) override { }

  virtual void enterCreateTable(SQLParser::CreateTableContext * /*ctx*/) override { }
  virtual void exitCreateTable(SQLParser::CreateTableContext * /*ctx*/) override { }

  virtual void enterPrimaryKeyDeclaration(SQLParser::PrimaryKeyDeclarationContext * /*ctx*/) override { }
  virtual void exitPrimaryKeyDeclaration(SQLParser::PrimaryKeyDeclarationContext * /*ctx*/) override { }

  virtual void enterDropTable(SQLParser::DropTableContext * /*ctx*/) override { }
  virtual void exitDropTable(SQLParser::DropTableContext * /*ctx*/) override { }

  virtual void enterDropDatabase(SQLParser::DropDatabaseContext * /*ctx*/) override { }
  virtual void exitDropDatabase(SQLParser::DropDatabaseContext * /*ctx*/) override { }

  virtual void enterInsertInto(SQLParser::InsertIntoContext * /*ctx*/) override { }
  virtual void exitInsertInto(SQLParser::InsertIntoContext * /*ctx*/) override { }

  virtual void enterUpdate(SQLParser::UpdateContext * /*ctx*/) override { }
  virtual void exitUpdate(SQLParser::UpdateContext * /*ctx*/) override { }

  virtual void enterSelectStatement(SQLParser::SelectStatementContext * /*ctx*/) override { }
  virtual void exitSelectStatement(SQLParser::SelectStatementContext * /*ctx*/) override { }

  virtual void enterDeleteStatement(SQLParser::DeleteStatementContext * /*ctx*/) override { }
  virtual void exitDeleteStatement(SQLParser::DeleteStatementContext * /*ctx*/) override { }

  virtual void enterUseDatabase(SQLParser::UseDatabaseContext * /*ctx*/) override { }
  virtual void exitUseDatabase(SQLParser::UseDatabaseContext * /*ctx*/) override { }

  virtual void enterAssignmentList(SQLParser::AssignmentListContext * /*ctx*/) override { }
  virtual void exitAssignmentList(SQLParser::AssignmentListContext * /*ctx*/) override { }

  virtual void enterAssignment(SQLParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(SQLParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterColumnList(SQLParser::ColumnListContext * /*ctx*/) override { }
  virtual void exitColumnList(SQLParser::ColumnListContext * /*ctx*/) override { }

  virtual void enterValueList(SQLParser::ValueListContext * /*ctx*/) override { }
  virtual void exitValueList(SQLParser::ValueListContext * /*ctx*/) override { }

  virtual void enterColumnDefinition(SQLParser::ColumnDefinitionContext * /*ctx*/) override { }
  virtual void exitColumnDefinition(SQLParser::ColumnDefinitionContext * /*ctx*/) override { }

  virtual void enterCondition(SQLParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(SQLParser::ConditionContext * /*ctx*/) override { }

  virtual void enterComparisonOperator(SQLParser::ComparisonOperatorContext * /*ctx*/) override { }
  virtual void exitComparisonOperator(SQLParser::ComparisonOperatorContext * /*ctx*/) override { }

  virtual void enterValue(SQLParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(SQLParser::ValueContext * /*ctx*/) override { }

  virtual void enterDataType(SQLParser::DataTypeContext * /*ctx*/) override { }
  virtual void exitDataType(SQLParser::DataTypeContext * /*ctx*/) override { }

  virtual void enterDatabaseName(SQLParser::DatabaseNameContext * /*ctx*/) override { }
  virtual void exitDatabaseName(SQLParser::DatabaseNameContext * /*ctx*/) override { }

  virtual void enterTableName(SQLParser::TableNameContext * /*ctx*/) override { }
  virtual void exitTableName(SQLParser::TableNameContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

