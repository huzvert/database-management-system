
// Generated from SQL.g4 by ANTLR 4.13.2


#include "SQLListener.h"

#include "SQLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SQLParserStaticData final {
  SQLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SQLParserStaticData(const SQLParserStaticData&) = delete;
  SQLParserStaticData(SQLParserStaticData&&) = delete;
  SQLParserStaticData& operator=(const SQLParserStaticData&) = delete;
  SQLParserStaticData& operator=(SQLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sqlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<SQLParserStaticData> sqlParserStaticData = nullptr;

void sqlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sqlParserStaticData != nullptr) {
    return;
  }
#else
  assert(sqlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SQLParserStaticData>(
    std::vector<std::string>{
      "sqlStatement", "statement", "listDatabases", "createDatabase", "createTable", 
      "primaryKeyDeclaration", "dropTable", "dropDatabase", "insertInto", 
      "update", "selectStatement", "deleteStatement", "useDatabase", "assignmentList", 
      "assignment", "columnList", "valueList", "columnDefinition", "condition", 
      "comparisonOperator", "value", "dataType", "databaseName", "tableName"
    },
    std::vector<std::string>{
      "", "'LIST DATABASES'", "'CREATE'", "'DATABASE'", "'TABLE'", "'('", 
      "','", "')'", "'PRIMARY'", "'KEY'", "'DROP'", "'INSERT'", "'INTO'", 
      "'VALUES'", "'UPDATE'", "'SET'", "'WHERE'", "'SELECT'", "'FROM'", 
      "'DELETE'", "'USE'", "'='", "'*'", "'AND'", "'OR'", "'>'", "'<'", 
      "'>='", "'<='", "'!='", "'TRUE'", "'FALSE'", "'INT'", "'INTEGER'", 
      "'BOOL'", "'BOOLEAN'", "'CHAR'", "'DATE'", "'.'", "", "", "", "", 
      "", "", "';'", "", "", "'NULL'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "BOOL_LITERAL", "IDENTIFIER", "STRING", "NUMBER", 
      "DATE_LITERAL", "DIGIT", "SEMICOLON", "WS", "COMMENT", "NULL"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,48,221,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,1,0,3,0,51,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,3,1,63,8,1,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,4,5,4,78,8,4,10,4,12,4,81,9,4,1,4,1,4,3,4,85,8,4,1,4,1,4,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,
  	1,10,1,10,3,10,127,8,10,1,11,1,11,1,11,1,11,1,11,3,11,134,8,11,1,12,1,
  	12,1,12,1,13,1,13,1,13,5,13,142,8,13,10,13,12,13,145,9,13,1,14,1,14,1,
  	14,1,14,1,15,1,15,1,15,1,15,5,15,155,8,15,10,15,12,15,158,9,15,3,15,160,
  	8,15,1,16,1,16,1,16,5,16,165,8,16,10,16,12,16,168,9,16,1,17,1,17,1,17,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,182,8,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,5,18,190,8,18,10,18,12,18,193,9,18,1,19,1,19,1,20,
  	1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,207,8,21,1,21,3,21,
  	210,8,21,1,22,1,22,1,23,1,23,1,23,3,23,217,8,23,1,23,1,23,1,23,0,1,36,
  	24,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,
  	0,2,2,0,21,21,25,29,3,0,30,31,41,43,48,48,224,0,48,1,0,0,0,2,62,1,0,0,
  	0,4,64,1,0,0,0,6,66,1,0,0,0,8,70,1,0,0,0,10,88,1,0,0,0,12,94,1,0,0,0,
  	14,98,1,0,0,0,16,102,1,0,0,0,18,113,1,0,0,0,20,120,1,0,0,0,22,128,1,0,
  	0,0,24,135,1,0,0,0,26,138,1,0,0,0,28,146,1,0,0,0,30,159,1,0,0,0,32,161,
  	1,0,0,0,34,169,1,0,0,0,36,181,1,0,0,0,38,194,1,0,0,0,40,196,1,0,0,0,42,
  	209,1,0,0,0,44,211,1,0,0,0,46,216,1,0,0,0,48,50,3,2,1,0,49,51,5,45,0,
  	0,50,49,1,0,0,0,50,51,1,0,0,0,51,1,1,0,0,0,52,63,3,6,3,0,53,63,3,8,4,
  	0,54,63,3,12,6,0,55,63,3,14,7,0,56,63,3,16,8,0,57,63,3,18,9,0,58,63,3,
  	20,10,0,59,63,3,22,11,0,60,63,3,24,12,0,61,63,3,4,2,0,62,52,1,0,0,0,62,
  	53,1,0,0,0,62,54,1,0,0,0,62,55,1,0,0,0,62,56,1,0,0,0,62,57,1,0,0,0,62,
  	58,1,0,0,0,62,59,1,0,0,0,62,60,1,0,0,0,62,61,1,0,0,0,63,3,1,0,0,0,64,
  	65,5,1,0,0,65,5,1,0,0,0,66,67,5,2,0,0,67,68,5,3,0,0,68,69,3,44,22,0,69,
  	7,1,0,0,0,70,71,5,2,0,0,71,72,5,4,0,0,72,73,3,46,23,0,73,74,5,5,0,0,74,
  	79,3,34,17,0,75,76,5,6,0,0,76,78,3,34,17,0,77,75,1,0,0,0,78,81,1,0,0,
  	0,79,77,1,0,0,0,79,80,1,0,0,0,80,84,1,0,0,0,81,79,1,0,0,0,82,83,5,6,0,
  	0,83,85,3,10,5,0,84,82,1,0,0,0,84,85,1,0,0,0,85,86,1,0,0,0,86,87,5,7,
  	0,0,87,9,1,0,0,0,88,89,5,8,0,0,89,90,5,9,0,0,90,91,5,5,0,0,91,92,5,40,
  	0,0,92,93,5,7,0,0,93,11,1,0,0,0,94,95,5,10,0,0,95,96,5,4,0,0,96,97,3,
  	46,23,0,97,13,1,0,0,0,98,99,5,10,0,0,99,100,5,3,0,0,100,101,3,44,22,0,
  	101,15,1,0,0,0,102,103,5,11,0,0,103,104,5,12,0,0,104,105,3,46,23,0,105,
  	106,5,5,0,0,106,107,3,30,15,0,107,108,5,7,0,0,108,109,5,13,0,0,109,110,
  	5,5,0,0,110,111,3,32,16,0,111,112,5,7,0,0,112,17,1,0,0,0,113,114,5,14,
  	0,0,114,115,3,46,23,0,115,116,5,15,0,0,116,117,3,26,13,0,117,118,5,16,
  	0,0,118,119,3,36,18,0,119,19,1,0,0,0,120,121,5,17,0,0,121,122,3,30,15,
  	0,122,123,5,18,0,0,123,126,3,46,23,0,124,125,5,16,0,0,125,127,3,36,18,
  	0,126,124,1,0,0,0,126,127,1,0,0,0,127,21,1,0,0,0,128,129,5,19,0,0,129,
  	130,5,18,0,0,130,133,3,46,23,0,131,132,5,16,0,0,132,134,3,36,18,0,133,
  	131,1,0,0,0,133,134,1,0,0,0,134,23,1,0,0,0,135,136,5,20,0,0,136,137,3,
  	44,22,0,137,25,1,0,0,0,138,143,3,28,14,0,139,140,5,6,0,0,140,142,3,28,
  	14,0,141,139,1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,143,144,1,0,0,0,
  	144,27,1,0,0,0,145,143,1,0,0,0,146,147,5,40,0,0,147,148,5,21,0,0,148,
  	149,3,40,20,0,149,29,1,0,0,0,150,160,5,22,0,0,151,156,5,40,0,0,152,153,
  	5,6,0,0,153,155,5,40,0,0,154,152,1,0,0,0,155,158,1,0,0,0,156,154,1,0,
  	0,0,156,157,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,0,159,150,1,0,0,0,159,
  	151,1,0,0,0,160,31,1,0,0,0,161,166,3,40,20,0,162,163,5,6,0,0,163,165,
  	3,40,20,0,164,162,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,0,166,167,1,0,
  	0,0,167,33,1,0,0,0,168,166,1,0,0,0,169,170,5,40,0,0,170,171,3,42,21,0,
  	171,35,1,0,0,0,172,173,6,18,-1,0,173,174,5,5,0,0,174,175,3,36,18,0,175,
  	176,5,7,0,0,176,182,1,0,0,0,177,178,5,40,0,0,178,179,3,38,19,0,179,180,
  	3,40,20,0,180,182,1,0,0,0,181,172,1,0,0,0,181,177,1,0,0,0,182,191,1,0,
  	0,0,183,184,10,4,0,0,184,185,5,23,0,0,185,190,3,36,18,5,186,187,10,3,
  	0,0,187,188,5,24,0,0,188,190,3,36,18,4,189,183,1,0,0,0,189,186,1,0,0,
  	0,190,193,1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,192,37,1,0,0,0,193,
  	191,1,0,0,0,194,195,7,0,0,0,195,39,1,0,0,0,196,197,7,1,0,0,197,41,1,0,
  	0,0,198,210,5,32,0,0,199,210,5,33,0,0,200,210,5,34,0,0,201,210,5,35,0,
  	0,202,206,5,36,0,0,203,204,5,5,0,0,204,205,5,42,0,0,205,207,5,7,0,0,206,
  	203,1,0,0,0,206,207,1,0,0,0,207,210,1,0,0,0,208,210,5,37,0,0,209,198,
  	1,0,0,0,209,199,1,0,0,0,209,200,1,0,0,0,209,201,1,0,0,0,209,202,1,0,0,
  	0,209,208,1,0,0,0,210,43,1,0,0,0,211,212,5,40,0,0,212,45,1,0,0,0,213,
  	214,3,44,22,0,214,215,5,38,0,0,215,217,1,0,0,0,216,213,1,0,0,0,216,217,
  	1,0,0,0,217,218,1,0,0,0,218,219,5,40,0,0,219,47,1,0,0,0,16,50,62,79,84,
  	126,133,143,156,159,166,181,189,191,206,209,216
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sqlParserStaticData = std::move(staticData);
}

}

SQLParser::SQLParser(TokenStream *input) : SQLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SQLParser::SQLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SQLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sqlParserStaticData->atn, sqlParserStaticData->decisionToDFA, sqlParserStaticData->sharedContextCache, options);
}

SQLParser::~SQLParser() {
  delete _interpreter;
}

const atn::ATN& SQLParser::getATN() const {
  return *sqlParserStaticData->atn;
}

std::string SQLParser::getGrammarFileName() const {
  return "SQL.g4";
}

const std::vector<std::string>& SQLParser::getRuleNames() const {
  return sqlParserStaticData->ruleNames;
}

const dfa::Vocabulary& SQLParser::getVocabulary() const {
  return sqlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SQLParser::getSerializedATN() const {
  return sqlParserStaticData->serializedATN;
}


//----------------- SqlStatementContext ------------------------------------------------------------------

SQLParser::SqlStatementContext::SqlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::StatementContext* SQLParser::SqlStatementContext::statement() {
  return getRuleContext<SQLParser::StatementContext>(0);
}

tree::TerminalNode* SQLParser::SqlStatementContext::SEMICOLON() {
  return getToken(SQLParser::SEMICOLON, 0);
}


size_t SQLParser::SqlStatementContext::getRuleIndex() const {
  return SQLParser::RuleSqlStatement;
}

void SQLParser::SqlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSqlStatement(this);
}

void SQLParser::SqlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSqlStatement(this);
}

SQLParser::SqlStatementContext* SQLParser::sqlStatement() {
  SqlStatementContext *_localctx = _tracker.createInstance<SqlStatementContext>(_ctx, getState());
  enterRule(_localctx, 0, SQLParser::RuleSqlStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    statement();
    setState(50);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::SEMICOLON) {
      setState(49);
      match(SQLParser::SEMICOLON);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

SQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::CreateDatabaseContext* SQLParser::StatementContext::createDatabase() {
  return getRuleContext<SQLParser::CreateDatabaseContext>(0);
}

SQLParser::CreateTableContext* SQLParser::StatementContext::createTable() {
  return getRuleContext<SQLParser::CreateTableContext>(0);
}

SQLParser::DropTableContext* SQLParser::StatementContext::dropTable() {
  return getRuleContext<SQLParser::DropTableContext>(0);
}

SQLParser::DropDatabaseContext* SQLParser::StatementContext::dropDatabase() {
  return getRuleContext<SQLParser::DropDatabaseContext>(0);
}

SQLParser::InsertIntoContext* SQLParser::StatementContext::insertInto() {
  return getRuleContext<SQLParser::InsertIntoContext>(0);
}

SQLParser::UpdateContext* SQLParser::StatementContext::update() {
  return getRuleContext<SQLParser::UpdateContext>(0);
}

SQLParser::SelectStatementContext* SQLParser::StatementContext::selectStatement() {
  return getRuleContext<SQLParser::SelectStatementContext>(0);
}

SQLParser::DeleteStatementContext* SQLParser::StatementContext::deleteStatement() {
  return getRuleContext<SQLParser::DeleteStatementContext>(0);
}

SQLParser::UseDatabaseContext* SQLParser::StatementContext::useDatabase() {
  return getRuleContext<SQLParser::UseDatabaseContext>(0);
}

SQLParser::ListDatabasesContext* SQLParser::StatementContext::listDatabases() {
  return getRuleContext<SQLParser::ListDatabasesContext>(0);
}


size_t SQLParser::StatementContext::getRuleIndex() const {
  return SQLParser::RuleStatement;
}

void SQLParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void SQLParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

SQLParser::StatementContext* SQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, SQLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(62);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(52);
      createDatabase();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(53);
      createTable();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(54);
      dropTable();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(55);
      dropDatabase();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(56);
      insertInto();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(57);
      update();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(58);
      selectStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(59);
      deleteStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(60);
      useDatabase();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(61);
      listDatabases();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListDatabasesContext ------------------------------------------------------------------

SQLParser::ListDatabasesContext::ListDatabasesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::ListDatabasesContext::getRuleIndex() const {
  return SQLParser::RuleListDatabases;
}

void SQLParser::ListDatabasesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterListDatabases(this);
}

void SQLParser::ListDatabasesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitListDatabases(this);
}

SQLParser::ListDatabasesContext* SQLParser::listDatabases() {
  ListDatabasesContext *_localctx = _tracker.createInstance<ListDatabasesContext>(_ctx, getState());
  enterRule(_localctx, 4, SQLParser::RuleListDatabases);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(SQLParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateDatabaseContext ------------------------------------------------------------------

SQLParser::CreateDatabaseContext::CreateDatabaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::DatabaseNameContext* SQLParser::CreateDatabaseContext::databaseName() {
  return getRuleContext<SQLParser::DatabaseNameContext>(0);
}


size_t SQLParser::CreateDatabaseContext::getRuleIndex() const {
  return SQLParser::RuleCreateDatabase;
}

void SQLParser::CreateDatabaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateDatabase(this);
}

void SQLParser::CreateDatabaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateDatabase(this);
}

SQLParser::CreateDatabaseContext* SQLParser::createDatabase() {
  CreateDatabaseContext *_localctx = _tracker.createInstance<CreateDatabaseContext>(_ctx, getState());
  enterRule(_localctx, 6, SQLParser::RuleCreateDatabase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(SQLParser::T__1);
    setState(67);
    match(SQLParser::T__2);
    setState(68);
    databaseName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableContext ------------------------------------------------------------------

SQLParser::CreateTableContext::CreateTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::TableNameContext* SQLParser::CreateTableContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}

std::vector<SQLParser::ColumnDefinitionContext *> SQLParser::CreateTableContext::columnDefinition() {
  return getRuleContexts<SQLParser::ColumnDefinitionContext>();
}

SQLParser::ColumnDefinitionContext* SQLParser::CreateTableContext::columnDefinition(size_t i) {
  return getRuleContext<SQLParser::ColumnDefinitionContext>(i);
}

SQLParser::PrimaryKeyDeclarationContext* SQLParser::CreateTableContext::primaryKeyDeclaration() {
  return getRuleContext<SQLParser::PrimaryKeyDeclarationContext>(0);
}


size_t SQLParser::CreateTableContext::getRuleIndex() const {
  return SQLParser::RuleCreateTable;
}

void SQLParser::CreateTableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateTable(this);
}

void SQLParser::CreateTableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateTable(this);
}

SQLParser::CreateTableContext* SQLParser::createTable() {
  CreateTableContext *_localctx = _tracker.createInstance<CreateTableContext>(_ctx, getState());
  enterRule(_localctx, 8, SQLParser::RuleCreateTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(70);
    match(SQLParser::T__1);
    setState(71);
    match(SQLParser::T__3);
    setState(72);
    tableName();
    setState(73);
    match(SQLParser::T__4);
    setState(74);
    columnDefinition();
    setState(79);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(75);
        match(SQLParser::T__5);
        setState(76);
        columnDefinition(); 
      }
      setState(81);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(84);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__5) {
      setState(82);
      match(SQLParser::T__5);
      setState(83);
      primaryKeyDeclaration();
    }
    setState(86);
    match(SQLParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryKeyDeclarationContext ------------------------------------------------------------------

SQLParser::PrimaryKeyDeclarationContext::PrimaryKeyDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::PrimaryKeyDeclarationContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}


size_t SQLParser::PrimaryKeyDeclarationContext::getRuleIndex() const {
  return SQLParser::RulePrimaryKeyDeclaration;
}

void SQLParser::PrimaryKeyDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryKeyDeclaration(this);
}

void SQLParser::PrimaryKeyDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryKeyDeclaration(this);
}

SQLParser::PrimaryKeyDeclarationContext* SQLParser::primaryKeyDeclaration() {
  PrimaryKeyDeclarationContext *_localctx = _tracker.createInstance<PrimaryKeyDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, SQLParser::RulePrimaryKeyDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(SQLParser::T__7);
    setState(89);
    match(SQLParser::T__8);
    setState(90);
    match(SQLParser::T__4);
    setState(91);
    match(SQLParser::IDENTIFIER);
    setState(92);
    match(SQLParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropTableContext ------------------------------------------------------------------

SQLParser::DropTableContext::DropTableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::TableNameContext* SQLParser::DropTableContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}


size_t SQLParser::DropTableContext::getRuleIndex() const {
  return SQLParser::RuleDropTable;
}

void SQLParser::DropTableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropTable(this);
}

void SQLParser::DropTableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropTable(this);
}

SQLParser::DropTableContext* SQLParser::dropTable() {
  DropTableContext *_localctx = _tracker.createInstance<DropTableContext>(_ctx, getState());
  enterRule(_localctx, 12, SQLParser::RuleDropTable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    match(SQLParser::T__9);
    setState(95);
    match(SQLParser::T__3);
    setState(96);
    tableName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropDatabaseContext ------------------------------------------------------------------

SQLParser::DropDatabaseContext::DropDatabaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::DatabaseNameContext* SQLParser::DropDatabaseContext::databaseName() {
  return getRuleContext<SQLParser::DatabaseNameContext>(0);
}


size_t SQLParser::DropDatabaseContext::getRuleIndex() const {
  return SQLParser::RuleDropDatabase;
}

void SQLParser::DropDatabaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropDatabase(this);
}

void SQLParser::DropDatabaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropDatabase(this);
}

SQLParser::DropDatabaseContext* SQLParser::dropDatabase() {
  DropDatabaseContext *_localctx = _tracker.createInstance<DropDatabaseContext>(_ctx, getState());
  enterRule(_localctx, 14, SQLParser::RuleDropDatabase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(SQLParser::T__9);
    setState(99);
    match(SQLParser::T__2);
    setState(100);
    databaseName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertIntoContext ------------------------------------------------------------------

SQLParser::InsertIntoContext::InsertIntoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::TableNameContext* SQLParser::InsertIntoContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}

SQLParser::ColumnListContext* SQLParser::InsertIntoContext::columnList() {
  return getRuleContext<SQLParser::ColumnListContext>(0);
}

SQLParser::ValueListContext* SQLParser::InsertIntoContext::valueList() {
  return getRuleContext<SQLParser::ValueListContext>(0);
}


size_t SQLParser::InsertIntoContext::getRuleIndex() const {
  return SQLParser::RuleInsertInto;
}

void SQLParser::InsertIntoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertInto(this);
}

void SQLParser::InsertIntoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertInto(this);
}

SQLParser::InsertIntoContext* SQLParser::insertInto() {
  InsertIntoContext *_localctx = _tracker.createInstance<InsertIntoContext>(_ctx, getState());
  enterRule(_localctx, 16, SQLParser::RuleInsertInto);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(SQLParser::T__10);
    setState(103);
    match(SQLParser::T__11);
    setState(104);
    tableName();
    setState(105);
    match(SQLParser::T__4);
    setState(106);
    columnList();
    setState(107);
    match(SQLParser::T__6);
    setState(108);
    match(SQLParser::T__12);
    setState(109);
    match(SQLParser::T__4);
    setState(110);
    valueList();
    setState(111);
    match(SQLParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateContext ------------------------------------------------------------------

SQLParser::UpdateContext::UpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::TableNameContext* SQLParser::UpdateContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}

SQLParser::AssignmentListContext* SQLParser::UpdateContext::assignmentList() {
  return getRuleContext<SQLParser::AssignmentListContext>(0);
}

SQLParser::ConditionContext* SQLParser::UpdateContext::condition() {
  return getRuleContext<SQLParser::ConditionContext>(0);
}


size_t SQLParser::UpdateContext::getRuleIndex() const {
  return SQLParser::RuleUpdate;
}

void SQLParser::UpdateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdate(this);
}

void SQLParser::UpdateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdate(this);
}

SQLParser::UpdateContext* SQLParser::update() {
  UpdateContext *_localctx = _tracker.createInstance<UpdateContext>(_ctx, getState());
  enterRule(_localctx, 18, SQLParser::RuleUpdate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    match(SQLParser::T__13);
    setState(114);
    tableName();
    setState(115);
    match(SQLParser::T__14);
    setState(116);
    assignmentList();
    setState(117);
    match(SQLParser::T__15);
    setState(118);
    condition(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectStatementContext ------------------------------------------------------------------

SQLParser::SelectStatementContext::SelectStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::ColumnListContext* SQLParser::SelectStatementContext::columnList() {
  return getRuleContext<SQLParser::ColumnListContext>(0);
}

SQLParser::TableNameContext* SQLParser::SelectStatementContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}

SQLParser::ConditionContext* SQLParser::SelectStatementContext::condition() {
  return getRuleContext<SQLParser::ConditionContext>(0);
}


size_t SQLParser::SelectStatementContext::getRuleIndex() const {
  return SQLParser::RuleSelectStatement;
}

void SQLParser::SelectStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectStatement(this);
}

void SQLParser::SelectStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectStatement(this);
}

SQLParser::SelectStatementContext* SQLParser::selectStatement() {
  SelectStatementContext *_localctx = _tracker.createInstance<SelectStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, SQLParser::RuleSelectStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    match(SQLParser::T__16);
    setState(121);
    columnList();
    setState(122);
    match(SQLParser::T__17);
    setState(123);
    tableName();
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__15) {
      setState(124);
      match(SQLParser::T__15);
      setState(125);
      condition(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

SQLParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::TableNameContext* SQLParser::DeleteStatementContext::tableName() {
  return getRuleContext<SQLParser::TableNameContext>(0);
}

SQLParser::ConditionContext* SQLParser::DeleteStatementContext::condition() {
  return getRuleContext<SQLParser::ConditionContext>(0);
}


size_t SQLParser::DeleteStatementContext::getRuleIndex() const {
  return SQLParser::RuleDeleteStatement;
}

void SQLParser::DeleteStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeleteStatement(this);
}

void SQLParser::DeleteStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeleteStatement(this);
}

SQLParser::DeleteStatementContext* SQLParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, SQLParser::RuleDeleteStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    match(SQLParser::T__18);
    setState(129);
    match(SQLParser::T__17);
    setState(130);
    tableName();
    setState(133);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::T__15) {
      setState(131);
      match(SQLParser::T__15);
      setState(132);
      condition(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UseDatabaseContext ------------------------------------------------------------------

SQLParser::UseDatabaseContext::UseDatabaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::DatabaseNameContext* SQLParser::UseDatabaseContext::databaseName() {
  return getRuleContext<SQLParser::DatabaseNameContext>(0);
}


size_t SQLParser::UseDatabaseContext::getRuleIndex() const {
  return SQLParser::RuleUseDatabase;
}

void SQLParser::UseDatabaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUseDatabase(this);
}

void SQLParser::UseDatabaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUseDatabase(this);
}

SQLParser::UseDatabaseContext* SQLParser::useDatabase() {
  UseDatabaseContext *_localctx = _tracker.createInstance<UseDatabaseContext>(_ctx, getState());
  enterRule(_localctx, 24, SQLParser::RuleUseDatabase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    match(SQLParser::T__19);
    setState(136);
    databaseName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentListContext ------------------------------------------------------------------

SQLParser::AssignmentListContext::AssignmentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::AssignmentContext *> SQLParser::AssignmentListContext::assignment() {
  return getRuleContexts<SQLParser::AssignmentContext>();
}

SQLParser::AssignmentContext* SQLParser::AssignmentListContext::assignment(size_t i) {
  return getRuleContext<SQLParser::AssignmentContext>(i);
}


size_t SQLParser::AssignmentListContext::getRuleIndex() const {
  return SQLParser::RuleAssignmentList;
}

void SQLParser::AssignmentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentList(this);
}

void SQLParser::AssignmentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentList(this);
}

SQLParser::AssignmentListContext* SQLParser::assignmentList() {
  AssignmentListContext *_localctx = _tracker.createInstance<AssignmentListContext>(_ctx, getState());
  enterRule(_localctx, 26, SQLParser::RuleAssignmentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    assignment();
    setState(143);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__5) {
      setState(139);
      match(SQLParser::T__5);
      setState(140);
      assignment();
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

SQLParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::AssignmentContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}

SQLParser::ValueContext* SQLParser::AssignmentContext::value() {
  return getRuleContext<SQLParser::ValueContext>(0);
}


size_t SQLParser::AssignmentContext::getRuleIndex() const {
  return SQLParser::RuleAssignment;
}

void SQLParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void SQLParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}

SQLParser::AssignmentContext* SQLParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 28, SQLParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(SQLParser::IDENTIFIER);
    setState(147);
    match(SQLParser::T__20);
    setState(148);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnListContext ------------------------------------------------------------------

SQLParser::ColumnListContext::ColumnListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::ColumnListContext::IDENTIFIER() {
  return getTokens(SQLParser::IDENTIFIER);
}

tree::TerminalNode* SQLParser::ColumnListContext::IDENTIFIER(size_t i) {
  return getToken(SQLParser::IDENTIFIER, i);
}


size_t SQLParser::ColumnListContext::getRuleIndex() const {
  return SQLParser::RuleColumnList;
}

void SQLParser::ColumnListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnList(this);
}

void SQLParser::ColumnListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnList(this);
}

SQLParser::ColumnListContext* SQLParser::columnList() {
  ColumnListContext *_localctx = _tracker.createInstance<ColumnListContext>(_ctx, getState());
  enterRule(_localctx, 30, SQLParser::RuleColumnList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(159);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__21: {
        enterOuterAlt(_localctx, 1);
        setState(150);
        match(SQLParser::T__21);
        break;
      }

      case SQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(151);
        match(SQLParser::IDENTIFIER);
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SQLParser::T__5) {
          setState(152);
          match(SQLParser::T__5);
          setState(153);
          match(SQLParser::IDENTIFIER);
          setState(158);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueListContext ------------------------------------------------------------------

SQLParser::ValueListContext::ValueListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::ValueContext *> SQLParser::ValueListContext::value() {
  return getRuleContexts<SQLParser::ValueContext>();
}

SQLParser::ValueContext* SQLParser::ValueListContext::value(size_t i) {
  return getRuleContext<SQLParser::ValueContext>(i);
}


size_t SQLParser::ValueListContext::getRuleIndex() const {
  return SQLParser::RuleValueList;
}

void SQLParser::ValueListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValueList(this);
}

void SQLParser::ValueListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValueList(this);
}

SQLParser::ValueListContext* SQLParser::valueList() {
  ValueListContext *_localctx = _tracker.createInstance<ValueListContext>(_ctx, getState());
  enterRule(_localctx, 32, SQLParser::RuleValueList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    value();
    setState(166);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SQLParser::T__5) {
      setState(162);
      match(SQLParser::T__5);
      setState(163);
      value();
      setState(168);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnDefinitionContext ------------------------------------------------------------------

SQLParser::ColumnDefinitionContext::ColumnDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::ColumnDefinitionContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}

SQLParser::DataTypeContext* SQLParser::ColumnDefinitionContext::dataType() {
  return getRuleContext<SQLParser::DataTypeContext>(0);
}


size_t SQLParser::ColumnDefinitionContext::getRuleIndex() const {
  return SQLParser::RuleColumnDefinition;
}

void SQLParser::ColumnDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnDefinition(this);
}

void SQLParser::ColumnDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnDefinition(this);
}

SQLParser::ColumnDefinitionContext* SQLParser::columnDefinition() {
  ColumnDefinitionContext *_localctx = _tracker.createInstance<ColumnDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 34, SQLParser::RuleColumnDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    match(SQLParser::IDENTIFIER);
    setState(170);
    dataType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

SQLParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::ConditionContext *> SQLParser::ConditionContext::condition() {
  return getRuleContexts<SQLParser::ConditionContext>();
}

SQLParser::ConditionContext* SQLParser::ConditionContext::condition(size_t i) {
  return getRuleContext<SQLParser::ConditionContext>(i);
}

tree::TerminalNode* SQLParser::ConditionContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}

SQLParser::ComparisonOperatorContext* SQLParser::ConditionContext::comparisonOperator() {
  return getRuleContext<SQLParser::ComparisonOperatorContext>(0);
}

SQLParser::ValueContext* SQLParser::ConditionContext::value() {
  return getRuleContext<SQLParser::ValueContext>(0);
}


size_t SQLParser::ConditionContext::getRuleIndex() const {
  return SQLParser::RuleCondition;
}

void SQLParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void SQLParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}


SQLParser::ConditionContext* SQLParser::condition() {
   return condition(0);
}

SQLParser::ConditionContext* SQLParser::condition(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SQLParser::ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, parentState);
  SQLParser::ConditionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, SQLParser::RuleCondition, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(181);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__4: {
        setState(173);
        match(SQLParser::T__4);
        setState(174);
        condition(0);
        setState(175);
        match(SQLParser::T__6);
        break;
      }

      case SQLParser::IDENTIFIER: {
        setState(177);
        match(SQLParser::IDENTIFIER);
        setState(178);
        comparisonOperator();
        setState(179);
        value();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(191);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(189);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ConditionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCondition);
          setState(183);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(184);
          match(SQLParser::T__22);
          setState(185);
          condition(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ConditionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCondition);
          setState(186);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(187);
          match(SQLParser::T__23);
          setState(188);
          condition(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(193);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ComparisonOperatorContext ------------------------------------------------------------------

SQLParser::ComparisonOperatorContext::ComparisonOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SQLParser::ComparisonOperatorContext::getRuleIndex() const {
  return SQLParser::RuleComparisonOperator;
}

void SQLParser::ComparisonOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonOperator(this);
}

void SQLParser::ComparisonOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonOperator(this);
}

SQLParser::ComparisonOperatorContext* SQLParser::comparisonOperator() {
  ComparisonOperatorContext *_localctx = _tracker.createInstance<ComparisonOperatorContext>(_ctx, getState());
  enterRule(_localctx, 38, SQLParser::RuleComparisonOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1042284544) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

SQLParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::ValueContext::STRING() {
  return getToken(SQLParser::STRING, 0);
}

tree::TerminalNode* SQLParser::ValueContext::NUMBER() {
  return getToken(SQLParser::NUMBER, 0);
}

tree::TerminalNode* SQLParser::ValueContext::DATE_LITERAL() {
  return getToken(SQLParser::DATE_LITERAL, 0);
}

tree::TerminalNode* SQLParser::ValueContext::NULL_() {
  return getToken(SQLParser::NULL_, 0);
}


size_t SQLParser::ValueContext::getRuleIndex() const {
  return SQLParser::RuleValue;
}

void SQLParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void SQLParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

SQLParser::ValueContext* SQLParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 40, SQLParser::RuleValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 296871360724992) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataTypeContext ------------------------------------------------------------------

SQLParser::DataTypeContext::DataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::DataTypeContext::NUMBER() {
  return getToken(SQLParser::NUMBER, 0);
}


size_t SQLParser::DataTypeContext::getRuleIndex() const {
  return SQLParser::RuleDataType;
}

void SQLParser::DataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataType(this);
}

void SQLParser::DataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataType(this);
}

SQLParser::DataTypeContext* SQLParser::dataType() {
  DataTypeContext *_localctx = _tracker.createInstance<DataTypeContext>(_ctx, getState());
  enterRule(_localctx, 42, SQLParser::RuleDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(209);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::T__31: {
        enterOuterAlt(_localctx, 1);
        setState(198);
        match(SQLParser::T__31);
        break;
      }

      case SQLParser::T__32: {
        enterOuterAlt(_localctx, 2);
        setState(199);
        match(SQLParser::T__32);
        break;
      }

      case SQLParser::T__33: {
        enterOuterAlt(_localctx, 3);
        setState(200);
        match(SQLParser::T__33);
        break;
      }

      case SQLParser::T__34: {
        enterOuterAlt(_localctx, 4);
        setState(201);
        match(SQLParser::T__34);
        break;
      }

      case SQLParser::T__35: {
        enterOuterAlt(_localctx, 5);
        setState(202);
        match(SQLParser::T__35);
        setState(206);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SQLParser::T__4) {
          setState(203);
          match(SQLParser::T__4);
          setState(204);
          match(SQLParser::NUMBER);
          setState(205);
          match(SQLParser::T__6);
        }
        break;
      }

      case SQLParser::T__36: {
        enterOuterAlt(_localctx, 6);
        setState(208);
        match(SQLParser::T__36);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DatabaseNameContext ------------------------------------------------------------------

SQLParser::DatabaseNameContext::DatabaseNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::DatabaseNameContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}


size_t SQLParser::DatabaseNameContext::getRuleIndex() const {
  return SQLParser::RuleDatabaseName;
}

void SQLParser::DatabaseNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDatabaseName(this);
}

void SQLParser::DatabaseNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDatabaseName(this);
}

SQLParser::DatabaseNameContext* SQLParser::databaseName() {
  DatabaseNameContext *_localctx = _tracker.createInstance<DatabaseNameContext>(_ctx, getState());
  enterRule(_localctx, 44, SQLParser::RuleDatabaseName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(SQLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableNameContext ------------------------------------------------------------------

SQLParser::TableNameContext::TableNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::TableNameContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}

SQLParser::DatabaseNameContext* SQLParser::TableNameContext::databaseName() {
  return getRuleContext<SQLParser::DatabaseNameContext>(0);
}


size_t SQLParser::TableNameContext::getRuleIndex() const {
  return SQLParser::RuleTableName;
}

void SQLParser::TableNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableName(this);
}

void SQLParser::TableNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableName(this);
}

SQLParser::TableNameContext* SQLParser::tableName() {
  TableNameContext *_localctx = _tracker.createInstance<TableNameContext>(_ctx, getState());
  enterRule(_localctx, 46, SQLParser::RuleTableName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(213);
      databaseName();
      setState(214);
      match(SQLParser::T__37);
      break;
    }

    default:
      break;
    }
    setState(218);
    match(SQLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SQLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 18: return conditionSempred(antlrcpp::downCast<ConditionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SQLParser::conditionSempred(ConditionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void SQLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sqlParserInitialize();
#else
  ::antlr4::internal::call_once(sqlParserOnceFlag, sqlParserInitialize);
#endif
}
