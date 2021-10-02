%{
#include "AbsSyntaxTree.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <utility>

using namespace std;

void yyerror(const char *s) { 
    error_exit(s);
}

int yylex(void);

Program *prog;
%}

%nonassoc NON_ELSE
%nonassoc ELSE

%union {
    int intValue;
    string *stringValue;
    double doubleValue;
    bool boolValue;
    char charValue;
    Expr *expression;
    Identifier *identifier;
    ConstValue *constValue;
    Stmt *statement;
    Types *astType;
    FieldDeclaration *fieldDeclaration;
    TypeDeclaration *typeDeclaration;
    VarDeclaration *varDeclaration;
    FuncDeclaration *funcDeclaration;
    Parameter *parameter;
    AssignStmt *assignStmt;
    Routine *routine;
    Program *program;
    IfStmt *ifStmt;
    RepeatStmt *repeatStmt;
    WhileStmt *whileStmt;
    ForStmt *forStmt;
    CaseStmt *caseStmt;
    std::pair<Expr*, Stmt*> *caseExpr;
    GotoStmt *gotoStmt;
    CompoundStmt *compoundStmt;
    
    vector<Expr*> *expressionList;
    vector<Stmt*> *statementList;
    vector<ConstDeclaration*> *constDeclarationList;
    vector<VarDeclaration*> *varDeclarationList;
    vector<TypeDeclaration*> *typeDeclarationList;
    vector<Identifier*> *identifierList;
    vector<FieldDeclaration*> *fieldDeclarationList;
    vector<Parameter*> *parameterList;
    vector<FuncDeclaration*> *funcDeclarationList;
    vector<std::pair<Expr*,Stmt*>*> *caseExprList;
    
}

%token  LP RP LB RB DOT COMMA COLON MUL DIV UNEQUAL
        NOT PLUS MINUS GE GT LE LT EQUAL ASSIGN MOD
        DOTDOT SEMI AND ARRAY _BEGIN CASE CONST DO
        DOWNTO ELSE END FOR FUNCTION GOTO IF OF OR
        PACKED PROCEDURE PROGRAM RECORD REPEAT THEN
        TO TYPE UNTIL VAR WHILE

%token<intValue>    INTEGER
%token<stringValue> SYS_CONST SYS_FUNC SYS_PROC SYS_TYPE READ ID
%token<doubleValue> REAL
%token<charValue>   CHAR

%type<identifier>                       name
%type<program>                          program
%type<stringValue>                      program_head
%type<routine>                          routine routine_head sub_routine
%type<constDeclarationList>             const_part const_expr_list
%type<typeDeclarationList>              type_part type_decl_list
%type<typeDeclaration>                  type_definition
%type<varDeclarationList>               var_part var_decl_list
%type<varDeclaration>                   var_decl
%type<funcDeclarationList>              routine_part
%type<constValue>                       const_value
%type<astType>                          type_decl simple_type_decl array_type_decl record_type_decl
%type<identifierList>                   name_list
%type<fieldDeclarationList>             field_decl_list
%type<fieldDeclaration>                 field_decl
%type<funcDeclaration>                  function_decl procedure_decl function_head procedure_head
%type<parameterList>                    parameters para_decl_list
%type<parameter>                        para_type_list var_para_list val_para_list
%type<statement>                        stmt non_label_stmt else_clause
%type<assignStmt>                  assign_stmt
%type<statement>                        proc_stmt     
%type<expressionList>                   expression_list args_list 
%type<expression>                       expression expr term factor
%type<ifStmt>                      if_stmt 
%type<repeatStmt>                  repeat_stmt
%type<whileStmt>                   while_stmt
%type<forStmt>                     for_stmt
%type<boolValue>                        direction
%type<caseStmt>                    case_stmt
%type<caseExprList>               case_expr_list
%type<caseExpr>                   case_expr
%type<gotoStmt>                    goto_stmt
%type<statementList>                    stmt_list
%type<compoundStmt>                routine_body compound_stmt 


%start program
%%

name:
    ID                                                          { $$ = new Identifier($1); }
    ;

program:
    program_head routine DOT                                    {
                                                                    $$ = new Program($1, $2);
                                                                    prog = $$;
                                                                }
    ;

program_head:
    PROGRAM ID SEMI                                             { $$ = $2; }
    ;

routine:
    routine_head routine_body                                   {
                                                                    $$ = $1;
                                                                    $$->routine_body=$2;
                                                                }
    ;

routine_head:
    const_part type_part var_part routine_part                  { $$ = new Routine($1, $2, $3, $4); }
    ;

sub_routine:
    routine_head routine_body                                   {
                                                                    $$ = $1;
                                                                    $$->routine_body=$2;
                                                                }
    ;

const_part: 
    CONST const_expr_list                                       { $$ = $2; }
    | %empty                                                    { $$ = new std::vector<ConstDeclaration*>(); }
    ;

const_expr_list:
    const_expr_list name EQUAL const_value SEMI                 {
                                                                    $$ = $1;
                                                                    $$->push_back(new ConstDeclaration($2, $4));
                                                                }
    | name EQUAL const_value SEMI                               {
                                                                    $$ = new std::vector<ConstDeclaration*>();
                                                                    $$->push_back(new ConstDeclaration($1, $3));
                                                                }
    ;

const_value:
    INTEGER                                                     { $$ = new ConstValue($1); }
    | REAL                                                      { $$ = new ConstValue($1); }
    | CHAR                                                      { $$ = new ConstValue($1); }
    | SYS_CONST                                                 {
                                                                    if(*$1 == "true")
                                                                        $$ = new ConstValue(true);
                                                                    else if(*$1 == "false")
                                                                        $$ = new ConstValue(false);
                                                                    else
                                                                        $$ = new ConstValue(INT_MAX);
                                                                }
    ;

type_part: 
    TYPE type_decl_list                                         { $$ = $2; }
    | %empty                                                    { $$ = new std::vector<TypeDeclaration*>(); }
    ;

type_decl_list: 
    type_decl_list type_definition                              {
                                                                    $$ = $1;
                                                                    $$->push_back($2);
                                                                }
    | type_definition                                           {
                                                                    $$ = new std::vector<TypeDeclaration*>();
                                                                    $$->push_back($1);
                                                                }
    ;

type_definition: 
    name EQUAL type_decl SEMI                                   { $$ = new TypeDeclaration($1, $3); }
    ;

type_decl: 
    simple_type_decl                                            { $$ = $1; }
    | array_type_decl                                           { $$ = $1; }
    | record_type_decl                                          { $$ = $1; }
    ;

simple_type_decl: 
    SYS_TYPE                                                    {
                                                                    if(*$1 == "integer")
                                                                        $$ = new Types(SPL_INTEGER);
                                                                    else if(*$1 == "boolean")
                                                                        $$ = new Types(SPL_BOOLEAN);
                                                                    else if(*$1 == "real")
                                                                        $$ = new Types(SPL_REAL);
                                                                    else if(*$1 == "char")
                                                                        $$ = new Types(SPL_CHAR);
                                                                }
    | name                                                      { $$ = new Types($1); }
    | LP name_list RP                                           { $$ = new Types(new EnumType($2)); }
    | const_value DOTDOT const_value                            { $$ = new Types(new ConstRangeType($1, $3)); }
    | MINUS const_value DOTDOT const_value                      { $$ = new Types(new ConstRangeType(-*$2, $4)); }
    | MINUS const_value DOTDOT MINUS const_value                { $$ = new Types(new ConstRangeType(-*$2, -*$5)); }
    | name DOTDOT name                                          { $$ = new Types(new EnumRangeType($1, $3)); }
    ;

array_type_decl:
    ARRAY LB simple_type_decl RB OF type_decl                   { $$ = new Types(new ArrayType($6, $3)); }
    ;

record_type_decl:
    RECORD field_decl_list END                                  { $$ = new Types(new RecordType($2)); }
    ;

field_decl_list:
    field_decl_list field_decl                                  {
                                                                    $$ = $1;
                                                                    $$->push_back($2);
                                                                }
    | field_decl                                                {
                                                                    $$ = new std::vector<FieldDeclaration*>();
                                                                    $$->push_back($1);
                                                                }
    ;

field_decl:
    name_list COLON type_decl SEMI                              { $$ = new FieldDeclaration($1, $3); }
    ;

name_list:
    name_list COMMA name                                        {
                                                                    $$ = $1;
                                                                    $$->push_back($3);
                                                                }
    | name                                                      {
                                                                    $$ = new std::vector<Identifier*>();
                                                                    $$->push_back($1);
                                                                }
    ;

var_part:
    VAR var_decl_list                                           { $$ = $2; }
    | %empty                                                    { $$ = new std::vector<VarDeclaration*>(); }
    ;

var_decl_list:  
    var_decl_list var_decl                                      {
                                                                    $$ = $1;
                                                                    $$->push_back($2);
                                                                }
    | var_decl                                                  {
                                                                    $$ = new std::vector<VarDeclaration*>();
                                                                    $$->push_back($1);
                                                                }
    ;

var_decl:
    name_list COLON type_decl SEMI                              { $$ = new VarDeclaration($1, $3); }
    ;

routine_part:  
    routine_part function_decl                                  { $$ = $1; $$->push_back($2); }
    | routine_part procedure_decl                               { $$ = $1; $$->push_back($2); }
    | %empty                                                    { $$ = new std::vector<FuncDeclaration*>(); }
    ;

function_decl:
    function_head SEMI sub_routine SEMI                         {
                                                                    $$ = $1;
                                                                    $$->subRoutine=$3;
                                                                }
    ;

function_head:
    FUNCTION name parameters COLON simple_type_decl             { $$ = new FuncDeclaration($2, $3, $5); }
    ;

procedure_decl:
    procedure_head SEMI sub_routine SEMI                        {
                                                                    $$ = $1;
                                                                    $$->subRoutine=$3;
                                                                }
    ;

procedure_head:
    PROCEDURE name parameters                                   { $$ = new FuncDeclaration($2, $3); }
    ;

parameters:
    LP para_decl_list RP                                        { $$ = $2; }
    | %empty                                                    { $$ = new std::vector<Parameter*>(); }
    ;

para_decl_list:
    para_decl_list SEMI para_type_list                          {
                                                                    $$ = $1;
                                                                    $$->push_back($3);
                                                                }
    | para_type_list                                            {
                                                                    $$ = new std::vector<Parameter*>();
                                                                    $$->push_back($1);
                                                                }
    ;

para_type_list:
    var_para_list COLON simple_type_decl                        {
                                                                    $$ = $1;
                                                                    $$->type=$3;
                                                                }
    | val_para_list COLON simple_type_decl                      {
                                                                    $$ = $1;
                                                                    $$->type=$3;
                                                                }
    ;

var_para_list:
    VAR name_list                                               { $$ = new Parameter($2, true); }
    ;

val_para_list:
    name_list                                                   { $$ = new Parameter($1, false); }
    ;

routine_body:
    compound_stmt                                               { $$ = $1; }
    ;

compound_stmt
    :_BEGIN stmt_list END                                       { $$ = new CompoundStmt($2); }
    ;

stmt_list:
    stmt_list stmt SEMI                                         {
                                                                    $$ = $1;
                                                                    $$->push_back($2);
                                                                }
    | %empty                                                    { $$ = new std::vector<Stmt*>(); }
    ;

stmt:
    INTEGER COLON non_label_stmt                                {
                                                                    $$ = $3;
                                                                    $$->label=$1;
                                                                }
    | non_label_stmt                                            { $$ = $1; }
    ;

non_label_stmt:
    assign_stmt                                                 { $$ = $1; }
    | proc_stmt                                                 { $$ = $1; }
    | compound_stmt                                             { $$ = $1; }
    | if_stmt                                                   { $$ = $1; }
    | repeat_stmt                                               { $$ = $1; }
    | while_stmt                                                { $$ = $1; }
    | for_stmt                                                  { $$ = $1; }
    | case_stmt                                                 { $$ = $1; }
    | goto_stmt                                                 { $$ = $1; }
    ;

assign_stmt:
    name ASSIGN expression                                      { $$ = new AssignStmt($1, $3); }
    | name LB expression RB ASSIGN expression                   { $$ = new AssignStmt($1, $3, $6); }
    | name DOT name ASSIGN expression                           { $$ = new AssignStmt($1, $3, $5); }
    ;

proc_stmt:
    name                                                        { $$ = new ProcCall($1); }
    | name LP args_list RP                                      { $$ = new ProcCall($1, $3); }
    | SYS_PROC                                                  { $$ = new SysProcCall($1); }
    | SYS_PROC LP expression_list RP                            { $$ = new SysProcCall($1, $3); }
    | READ LP factor RP                                         { $$ = new SysProcCall($1, $3); }
    ;

if_stmt:
    IF expression THEN stmt else_clause                         { $$ = new IfStmt($2, $4, $5); }
    ;

else_clause:
    ELSE stmt                                                   { $$ = $2; }
    | %empty %prec NON_ELSE                                     { $$ = nullptr; }
    ;

repeat_stmt:
    REPEAT stmt_list UNTIL expression                           { $$ = new RepeatStmt($4, $2); }
    ;

while_stmt:
    WHILE expression DO stmt                                    { $$ = new WhileStmt($2, $4); }
    ;

for_stmt:  
    FOR name ASSIGN expression direction expression DO stmt     { $$ = new ForStmt($2, $4, $5, $6, $8); }
    ;

direction:
    TO                                                          { $$ = true; }
    | DOWNTO                                                    { $$ = false; }
    ;

case_stmt:
    CASE expression OF case_expr_list END                       { $$ = new CaseStmt($2, $4); }
    ;

case_expr_list: 
    case_expr_list case_expr                                    {
                                                                    $$ = $1;
                                                                    $$->push_back($2);
                                                                }
    | case_expr                                                 {
                                                                    $$ = new std::vector<std::pair<Expr*, Stmt*>*>();
                                                                    $$->push_back($1);
                                                                }
    ;

case_expr:
    const_value COLON stmt SEMI                                 { $$ = new std::pair<Expr*, Stmt*>($1, $3); }
    | name COLON stmt SEMI                                      { $$ = new std::pair<Expr*, Stmt*>($1, $3); }
    ;

goto_stmt:
    GOTO INTEGER                                                { $$ = new GotoStmt($2); }
    ;

expression_list:
    expression_list COMMA expression                            {
                                                                    $$ = $1;
                                                                    $$->push_back($3);
                                                                }
    | expression                                                {
                                                                    $$ = new std::vector<Expr*>();
                                                                    $$->push_back($1);
                                                                }
    ;

expression: 
    expression GE expr                                          { $$ = ConstantFold($1, MathExpr::Ops::SPL_GE, $3); }
    | expression GT expr                                        { $$ = ConstantFold($1, MathExpr::Ops::SPL_GT, $3); }
    | expression LE expr                                        { $$ = ConstantFold($1, MathExpr::Ops::SPL_LE, $3); }
    | expression LT expr                                        { $$ = ConstantFold($1, MathExpr::Ops::SPL_LT, $3); }
    | expression EQUAL expr                                     { $$ = ConstantFold($1, MathExpr::Ops::SPL_EQUAL, $3); }
    | expression UNEQUAL expr                                   { $$ = ConstantFold($1, MathExpr::Ops::SPL_UNEQUAL, $3); }
    | expr                                                      { $$ = $1; }
    ;

expr:
    expr PLUS term                                              { $$ = ConstantFold($1, MathExpr::Ops::SPL_PLUS, $3); }
    | expr MINUS term                                           { $$ = ConstantFold($1, MathExpr::Ops::SPL_MINUS, $3); }
    | expr OR term                                              { $$ = ConstantFold($1, MathExpr::Ops::SPL_OR, $3); }
    | term                                                      { $$ = $1; }
    ;

term:
    term MUL factor                                             { $$ = ConstantFold($1, MathExpr::Ops::SPL_MUL, $3); }
    | term DIV factor                                           { $$ = ConstantFold($1, MathExpr::Ops::SPL_DIV, $3); }
    | term MOD factor                                           { $$ = ConstantFold($1, MathExpr::Ops::SPL_MOD, $3); }
    | term AND factor                                           { $$ = ConstantFold($1, MathExpr::Ops::SPL_AND, $3); }
    | factor                                                    { $$ = $1; }
    ;

factor:
    name                                                        { $$ = $1; }
    | name LP args_list RP                                      { $$ = new FuncCall($1, $3); }
    | SYS_FUNC                                                  { $$ = new SysFuncCall($1); }
    | SYS_FUNC LP args_list RP                                  { $$ = new SysFuncCall($1, $3); }
    | const_value                                               { $$ = $1; }
    | LP expression RP                                          { $$ = $2; }
    | NOT factor                                                { $$ = ConstantFold(nullptr, MathExpr::Ops::SPL_NOT, $2); }
    | MINUS factor                                              { $$ = ConstantFold(nullptr, MathExpr::Ops::SPL_NEGATIVE, $2); }
    | name LB expression RB                                     { $$ = new ArrayRef($1, $3); }
    | name DOT name                                             { $$ = new RecordRef($1, $3); }
    ;

args_list:
    args_list COMMA expression                                  {
                                                                    $$ = $1;
                                                                    $$->push_back($3);
                                                                }
    | expression                                                {
                                                                    $$ = new std::vector<Expr*>();
                                                                    $$->push_back($1);
                                                                }
    ;

%%
