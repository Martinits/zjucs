#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <utility>
#include <llvm/IR/Value.h>

using namespace std;

class irBuilder;

class AstNode;

class Expr;
    class Identifier;
    class ConstValue;
    class MathExpr;
    class ArrayRef;
    class RecordRef;
        class FuncCall;
        class SysFuncCall;
class Stmt;
    class Types;
    class ConstDeclaration;
    class EnumType;
    class ArrayType;
    class ConstRangeType;
    class EnumRangeType;
    class RecordType;
    class FieldDeclaration;
    class TypeDeclaration;
    class VarDeclaration;
    class FuncDeclaration;
    class Parameter;
    class AssignStmt;
    class ProcCall;
    class SysProcCall;
    class IfStmt;
    class RepeatStmt;
    class WhileStmt;
    class ForStmt;
    class CaseStmt;
    class GotoStmt;
    class CompoundStmt;

class Routine;
class Program;

//SPL_SysTypes
enum SysTypes{
    SPL_INTEGER,
    SPL_REAL,
    SPL_CHAR,
    SPL_BOOLEAN
};

//AST_Node
class AstNode{
public:
    virtual llvm::Value* build(irBuilder& irb) = 0;
    virtual string getJson(){
        return "";
    }
    virtual ~AstNode(){}
};

//Expr:storing value
class Expr : public AstNode {
public:
    virtual ~Expr(){}
};

//id
class Identifier : public Expr{
public:
    string *name;
    Identifier(string *name):name(name){}
    string getName() { return *name; }
    virtual llvm::Value *build(irBuilder& irb);
    virtual string getJson();
    virtual ~Identifier(){}
};
// value
class ConstValue : public Expr{
public:
    SysTypes type;
    union Value{
        int i;
        double r;
        char c;
        bool b;
    }val;
    ConstValue(int i){
        val.i = i;
        type = SPL_INTEGER;
    }
    ConstValue(char c){
        val.c = c;
        type = SPL_CHAR;
    }
    ConstValue(bool b){
        val.b = b;
        type = SPL_BOOLEAN;
    }
    ConstValue(double r){
        val.r = r;
        type = SPL_REAL;
    }
    ConstValue* operator-(){
        switch(type){
            case SPL_BOOLEAN:   return new ConstValue(!val.b);
            case SPL_CHAR:      return new ConstValue(-val.c);
            case SPL_INTEGER:   return new ConstValue(-val.i);
            case SPL_REAL:      return new ConstValue(-val.r);
        }
        return nullptr;
    }
    virtual llvm::Value *build(irBuilder& irb);
    virtual string getJson();
    virtual ~ConstValue(){}
};

class MathExpr : public Expr{
public:
    enum Ops {
        SPL_PLUS,       // +
        SPL_MINUS,      // -
        SPL_MUL,        // *
        SPL_DIV,        // /
        SPL_GE,         // >=
        SPL_GT,         // >
        SPL_LE,         // <=
        SPL_LT,         // <
        SPL_EQUAL,      // =
        SPL_UNEQUAL,    // !=
        SPL_OR,         // |
        SPL_MOD,        // %
        SPL_AND,        // &
        SPL_NOT,        // not
        SPL_NEGATIVE    // -()
    };
    Expr *lhs, *rhs;
    Ops op;
    MathExpr(Expr *l, Ops op, Expr *r) : lhs(l), op(op), rhs(r){}
    
    virtual llvm::Value *build(irBuilder& irb);
    virtual string getJson();
    virtual ~MathExpr(){};
};

// arr_name[ref_index]
class ArrayRef : public Expr{
public:
    Identifier* arr_name;
    Expr* ref_index;
    ArrayRef(Identifier* an, Expr* ri) : arr_name(an), ref_index(ri){}
    llvm::Value* getRef(irBuilder& irb);
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ArrayRef(){}
};
// record.reference
class RecordRef : public Expr {
public:
    Identifier* record;
    Identifier* reference;
    RecordRef(Identifier* rec, Identifier* ref) : record(rec), reference(ref){}
    llvm::Value* getRef(irBuilder& irb);
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~RecordRef(){}
};

//Stmt:some action
class Stmt : public AstNode{
public:
    int label = -1;
    llvm::BasicBlock* nextBB = nullptr;

    void goto_prepare(irBuilder& irb);
    void goto_endup(irBuilder& irb);
    virtual ~Stmt(){}
};
// const value decl: name = value
class ConstDeclaration : public Stmt{
public:
    Identifier* name;
    ConstValue* value;
    Types* Type;
    bool isGlobal;
    ConstDeclaration(Identifier* n, ConstValue* v):name(n),value(v),isGlobal(false){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ConstDeclaration(){}
};
//type decl: name = type
class TypeDeclaration : public Stmt{
public:
    Identifier* name;
    Types* type;
    TypeDeclaration(Identifier* n, Types* at):name(n),type(at){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    string getName(){return name->getName();}
    virtual ~TypeDeclaration(){}
};

// Ast type
class Types : public Stmt{
public:
    enum TpKinds {
        SPL_ARRAY,
        SPL_RECORD,
        SPL_ENUM,
        SPL_CONST_RANGE,
        SPL_ENUM_RANGE,
        SPL_BUILD_IN,
        SPL_USER_DEFINE,
        SPL_VOID
    };
    Types(ArrayType *at):arrayType(at), type(SPL_ARRAY){}
    Types(RecordType *rt):recordType(rt), type(SPL_RECORD){}
    Types(EnumType *et) : enumType(et), type(SPL_ENUM){}
    Types(ConstRangeType *crt) : constRangeType(crt), type(SPL_CONST_RANGE){}
    Types(EnumRangeType *ert) : enumRangeType(ert), type(SPL_ENUM_RANGE){}
    Types(SysTypes bt) : sysType(bt), type(SPL_BUILD_IN){}
    Types(Identifier *udt) : userDefineType(udt), type(SPL_USER_DEFINE){}
    Types() : type(SPL_VOID){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~Types(){}
    
    llvm::Type* getllvmType(irBuilder& irb);
    llvm::Constant* initValue(irBuilder& irb, ConstValue *v);

    ArrayType *arrayType;
    RecordType *recordType;
    EnumType *enumType;
    ConstRangeType *constRangeType;
    EnumRangeType *enumRangeType;
    SysTypes sysType;
    Identifier *userDefineType;
    TpKinds type;
};

// array: ARRAY [ range ] OF type
class ArrayType : public Stmt{
public:
    Types *range;
    Types *type;
    ArrayType(Types* t, Types* r):range(r),type(t){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ArrayType(){}
};

//record : field , field , field
class RecordType : public Stmt{
public:
    vector<FieldDeclaration*> *fieldlist;
    RecordType(vector<FieldDeclaration*> *fl): fieldlist(fl){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~RecordType(){}
};

//field : name , name , name : type
class FieldDeclaration : public Stmt{
public:
    vector<Identifier*> *idlist;
    Types* type;
    FieldDeclaration(vector<Identifier*> *il, Types* t):idlist(il),type(t){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~FieldDeclaration(){}
};

//enum : [ name , name , name ]
class EnumType : public Stmt{
public:
    vector<Identifier*> *idlist;
    EnumType(vector<Identifier*> *il):idlist(il){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~EnumType(){}
};

//range : low_val .. up_val
class ConstRangeType : public Stmt{
public:
    ConstValue* upperbound;
    ConstValue* lowerbound;
    ConstRangeType(ConstValue* low, ConstValue* up):lowerbound(low),upperbound(up){}
    size_t check_get_size();

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ConstRangeType(){}
};

//range : low_name .. up_name
class EnumRangeType : public Stmt{
public:
    Identifier *lowerbound;
    Identifier *upperbound;
    llvm::Value *lowerVal, *upperVal, *lowerAddr, *upperAddr;
    EnumRangeType(Identifier* low, Identifier* up):lowerbound(low),upperbound(up){}
    size_t check_get_size();

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~EnumRangeType(){}
};

//variable : name , name , name : type
class VarDeclaration : public Stmt{
public:
    vector<Identifier*> *idlist;
    Types* type;
    bool isGlobal;
    VarDeclaration(vector<Identifier*> *il, Types* t):idlist(il),type(t),isGlobal(false){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~VarDeclaration(){}
};
// function : name param_list : ret_type
class FuncDeclaration : public Stmt {
public: 
    Identifier *name;
    vector<Parameter*> *param;
    Types *retType;
    Routine *subRoutine;
    FuncDeclaration(Identifier *n, vector<Parameter*> *p, Types *r):name(n),param(p),retType(r){}
    FuncDeclaration(Identifier *n, vector<Parameter*> *p):name(n), param(p), retType(new Types()){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~FuncDeclaration(){}
};

//param : [VAR] name , name , name : type
class Parameter : public Stmt {
public:
    bool is_var_param;
    vector<Identifier*> *idlist;
    Types *type;

    Parameter(vector<Identifier*> *il, bool iV) : idlist(il), is_var_param(iV){}
    void setType(Types *t) {
        type = t;
    }

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~Parameter(){}
};

//assign : name = expression || array[ref] = expression || name .. name = expression
class AssignStmt : public Stmt{
public:
    enum AssignType{
        ASSIGN_NORMAL,
        ASSIGN_ARRAY,
        ASSIGN_RECORD
    };
    Identifier* lvalue;
    Expr* rvalue;
    Expr* arrref;
    Identifier* rrange;
    AssignType type;
    AssignStmt(Identifier* id, Expr* e):lvalue(id),rvalue(e),type(ASSIGN_NORMAL){}
    AssignStmt(Identifier* id, Expr* ref, Expr* e):lvalue(id),arrref(ref),rvalue(e),type(ASSIGN_ARRAY){}
    AssignStmt(Identifier* id, Identifier* range, Expr* e):lvalue(id),rrange(range),rvalue(e),type(ASSIGN_RECORD){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~AssignStmt(){}
};

//call : func [ args ]
class FuncCall : public Expr, public Stmt{
public:
    Identifier* name;
    vector<Expr*> *args;
    FuncCall(Identifier* n, vector<Expr*> *p = new vector<Expr*>()):name(n),args(p){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~FuncCall(){}
};

//call : proc [ args ]
class ProcCall : public Stmt {
public:
    Identifier* name;
    vector<Expr*> *args;
    ProcCall(Identifier* n, vector<Expr*> *p = new vector<Expr*>()):name(n),args(p){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ProcCall(){}
};

//sys_func : SYS_FUNC [ args ]
class SysFuncCall : public Expr, public Stmt{
public:
    string *name;
    vector<Expr*> *args;
    SysFuncCall(string *n):name(n){}
    SysFuncCall(string *n, vector<Expr*> *p): name(n), args(p){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~SysFuncCall(){}
};

//sys_proc : 
class SysProcCall : public Stmt {
public:
    enum SysProcTp {
        SYS_PROC_WRITE,
        SYS_PROC_WRITELN,
        SYS_PROC_READ,
        SPL_ERROR_PROCEDURE
    };
    inline SysProcTp getProcTp(string *name) {
        string &sname = *name;
        if(sname == "write")        return SYS_PROC_WRITE;
        else if(sname == "writeln") return SYS_PROC_WRITELN;
        else if(sname == "read")    return SYS_PROC_READ;
        else                        return SPL_ERROR_PROCEDURE;
    }
    string *name;
    vector<Expr*> *args;
    SysProcTp sys_proc;
    SysProcCall(string *n):sys_proc(getProcTp(name)), name(n){}
    SysProcCall(string *n, vector<Expr*> *p):sys_proc(getProcTp(n)), args(p), name(n){}
    SysProcCall(string *n, Expr *e):sys_proc(getProcTp(n)), args(new vector<Expr*>()), name(n){
        args->push_back(e);
    }
    llvm::Value *SysProcWrite(irBuilder& irb, bool isLineBreak);
    llvm::Value *SysProcRead(irBuilder& irb);

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~SysProcCall(){}
};

// id + routine
class Program : public Stmt{
public:
    string* pid;
    Routine* routine;
    Program(string* id, Routine* r):pid(id),routine(r){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~Program(){}
};

//routine : const_part type_part var_part routine_part routine_body
class Routine : public AstNode{
public:
    vector<ConstDeclaration*> *const_part;
    vector<TypeDeclaration*> *type_part;
    vector<VarDeclaration*> *var_part;
    vector<FuncDeclaration*> *routine_part;
    CompoundStmt* routine_body;
    Routine(vector<ConstDeclaration*> *cp, 
            vector<TypeDeclaration*> *tp, 
            vector<VarDeclaration*> *vp, 
            vector<FuncDeclaration*> *rp):const_part(cp),type_part(tp),var_part(vp),routine_part(rp){}
    
    void setGlobal(){
        for (auto & constDecl : *const_part){
            constDecl->isGlobal=true;
        }
        for (auto & varDecl : *var_part){
            varDecl->isGlobal=true;
        }
    }
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~Routine(){}
};

class IfStmt : public Stmt {
public:
    Expr *condition;
    Stmt *thenStmt;
    Stmt *elseStmt;
    IfStmt(Expr *cond, Stmt *tS, Stmt *eS):condition(cond), thenStmt(tS), elseStmt(eS){}
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~IfStmt(){}
};

class RepeatStmt : public Stmt {
public:
    Expr *condition;
    vector<Stmt*> *repeatStmt;
    RepeatStmt(Expr *cond, vector<Stmt*> *rS) : condition(cond), repeatStmt(rS){}
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~RepeatStmt(){}
};

class WhileStmt : public Stmt {
public:
    Expr *condition;
    Stmt *stmt;
    WhileStmt(Expr *cond, Stmt *S) : condition(cond), stmt(S){}
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~WhileStmt(){}
};

class ForStmt : public Stmt {
public:
    Identifier *var;
    Expr *value;
    bool isUpTo;
    Expr *step;
    Stmt *stmt;
    ForStmt(Identifier *var, Expr *value, bool isUpTo, Expr *step, Stmt *stmt) :
                    var(var), value(value), isUpTo(isUpTo), step(step), stmt(stmt){}
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~ForStmt(){}
};

class CaseStmt : public Stmt {
public:
    Expr *value;
    vector<pair<Expr*,Stmt*>* > *CaseList;
    CaseStmt(Expr *value, vector<pair<Expr*,Stmt*>* > *CaseE) : value(value), CaseList(CaseE){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~CaseStmt(){}
};

class GotoStmt : public Stmt {
public:
    int toLabel;
    GotoStmt(int label) : toLabel(label){}

    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~GotoStmt(){}
};

class CompoundStmt : public Stmt {
public:
    vector<Stmt*> *stmtList;
    CompoundStmt(vector<Stmt*> *stmtL) : stmtList(stmtL){}
    
    virtual llvm::Value* build(irBuilder& irb);
    virtual string getJson();
    virtual ~CompoundStmt(){}
};

Expr* ConstantFold(Expr* l, MathExpr::Ops op, Expr* r);