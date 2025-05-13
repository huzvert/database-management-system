grammar SQL;

sqlStatement
    : statement SEMICOLON?
    ;

statement
    : createDatabase
    | createTable
    | dropTable
    | dropDatabase
    | insertInto
    | update
    | selectStatement
    | deleteStatement
    | useDatabase
    | listDatabases
    ;

listDatabases
    : 'LIST DATABASES';

createDatabase
    : 'CREATE' 'DATABASE' databaseName
    ;

createTable
    : 'CREATE' 'TABLE' tableName '(' columnDefinition (',' columnDefinition)* (',' primaryKeyDeclaration)? ')'
    ;

primaryKeyDeclaration
    : 'PRIMARY' 'KEY' '(' IDENTIFIER ')'
    ;

dropTable
    : 'DROP' 'TABLE' tableName
    ;

dropDatabase
    : 'DROP' 'DATABASE' databaseName
    ;

insertInto
    : 'INSERT' 'INTO' tableName '(' columnList ')' 'VALUES' '(' valueList ')'
    ;

update
    : 'UPDATE' tableName 'SET' assignmentList 'WHERE' condition
    ;

selectStatement
    : 'SELECT' columnList 'FROM' tableName ('WHERE' condition)?
    ;

deleteStatement
    : 'DELETE' 'FROM' tableName ('WHERE' condition)?
    ;


useDatabase
    : 'USE' databaseName
    ;

assignmentList
    : assignment (',' assignment)*
    ;

assignment
    : IDENTIFIER '=' value
    ;

columnList
    : '*'
    | IDENTIFIER (',' IDENTIFIER)*
    ;

valueList
    : value (',' value)*
    ;

columnDefinition
    : IDENTIFIER dataType
    ;

condition
    : condition 'AND' condition
    | condition 'OR' condition
    | '(' condition ')'
    | IDENTIFIER comparisonOperator value
    ;

comparisonOperator
    : '='
    | '>'
    | '<'
    | '>='
    | '<='
    | '!='
    ;

BOOL_LITERAL
    : ('TRUE' | 'true') | ('FALSE' | 'false');

value
    : STRING
    | NUMBER
    | DATE_LITERAL
    | 'TRUE'
    | 'FALSE'
    | NULL
    ;

dataType
    : 'INT'
    | 'INTEGER'
    | 'BOOL'
    | 'BOOLEAN'
    | 'CHAR' ('(' NUMBER ')')?
    | 'DATE'
    ;

databaseName
    : IDENTIFIER
    ;

tableName
    : (databaseName '.')? IDENTIFIER
    ;

IDENTIFIER
    : [a-zA-Z_][a-zA-Z_0-9]*
    ;

STRING
    : '\'' ( ~'\'' )* '\''
    ;

NUMBER
    : [0-9]+
    ;

DATE_LITERAL
    : DIGIT DIGIT DIGIT DIGIT '-' DIGIT DIGIT '-' DIGIT DIGIT
    ;

DIGIT
    : [0-9] ;

SEMICOLON
    : ';'
    ;

WS
    : [ \t\r\n]+ -> skip
    ;

COMMENT
    : '--' ~[\r\n]* -> skip
    ;


NULL: 'NULL';

