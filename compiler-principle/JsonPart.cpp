#include "AbsSyntaxTree.h"
#include "irbuilder.h"
#include "utils.h"



string getNameJson(string name) {
    return "{ \"name\" : \"" + name + "\" }";
}

string getValueJson(string name, string value) {
    return "{ \"name\" : \"" + name + "\", \"value\" : \"" + value + "\" }";
}

string getJsonWithChildren(string name, string children) {
    string s = "{ \"name\" : \"" + name + "\", \"children\" : [ " + children + " ] }";
    return s;
}

string getValueJsonWithChildren(string name, string value, string children) {
    return "{ \"name\" : \"" + name + "\", \"value\" : \"" + value + "\", \"children\" : [ " + children + " ] }";
}

string MergeChildren(string child1, string child2){
    return child1 + ", " + child2;
}

string Program::getJson() {
    // string children = getNameJson(*pid) + ", " + routine->getJson();
    return getJsonWithChildren("Program: "+*pid, routine->getJson());
    // string children = getNameJson(*pid) + ", " + routine->getJson();
    // return getJsonWithChildren("Program", children);
}

string Identifier::getJson() {
    return getJsonWithChildren("Identifier", getNameJson(*name));
}

string ConstValue::getJson(){
    string t;
    string v;
    switch(type) {
        case SPL_BOOLEAN:
            t = "Boolean";
            v = val.b ? "true" : "false";
            break;
        case SPL_CHAR:
            t = "Char";
            v = string(1, val.c);
            break;
        case SPL_INTEGER:
            t = "Integer";
            v = to_string(val.i);
            break;
        case SPL_REAL:
            t = "Real";
            v = to_string(val.r);
            break;
    }
    return getJsonWithChildren(t, getNameJson(v));
}


string ConstDeclaration::getJson() {
    string children = name->getJson() + ", " + value->getJson();
    return getJsonWithChildren("ConstDeclaration", children);
}

string EnumType::getJson() {
    string children = "";
    if(idlist && (int)idlist->size() > 0) {
        int i = 0;
        for(; i < (int)idlist->size()-1; i++) {
            children += (*idlist)[i]->getJson() + ", ";
        }
        children += (*idlist)[i]->getJson();
    }
    return getJsonWithChildren("EnumType", children);
}

string ArrayType::getJson() {
    // string children = getJsonWithChildren("type", type->getJson()) + ", " + getJsonWithChildren("range", range->getJson());
    string children = type->getJson() + ", " + range->getJson();
    return getJsonWithChildren("ArrayType", children);
}

string ConstRangeType::getJson() {
    // string children = getJsonWithChildren("lowerbound", lowerbound->getJson()) + ", " + getJsonWithChildren("upperbound", upperbound->getJson());
    string children = lowerbound->getJson() + ", " + upperbound->getJson();
    return getJsonWithChildren("ConstRangeType", children);
}

string EnumRangeType::getJson() {
    // string children = getJsonWithChildren("lowerbound", lowerbound->getJson()) + ", " + getJsonWithChildren("upperbound", upperbound->getJson());
    string children = lowerbound->getJson() + ", " + upperbound->getJson();
    return getJsonWithChildren("EnumRangeType", children);
}

string FieldDeclaration::getJson() {
    string idListChildren = "";
    if(idlist && (int)idlist->size() > 0) {
        int i = 0;
        for(; i < (int)idlist->size() - 1; i++) {
            idListChildren += (*idlist)[i]->getJson() + ", ";
        }
        idListChildren += (*idlist)[i]->getJson();
    }
    string children = type->getJson() + "," + getJsonWithChildren("idlist", idListChildren);
    return getJsonWithChildren("FieldDeclaration", children); 
}

string RecordType::getJson() {
    string children = "";
    if(fieldlist && (int)fieldlist->size() > 0){
        int i = 0;
        for(; i < (int)fieldlist->size()-1; i++) {
            children += (*fieldlist)[i]->getJson() + ", ";
        }
        children += (*fieldlist)[i]->getJson();
    }
    return getJsonWithChildren("RecordType", children);
}

string Types::getJson() {
    switch (type) {
    case SPL_ARRAY:
        return arrayType->getJson();
        break;
    case SPL_RECORD:
        return recordType->getJson();
        break;
    case SPL_ENUM:
        return enumType->getJson();
        break;
    case SPL_CONST_RANGE:
        return constRangeType->getJson();
        break;
    case SPL_ENUM_RANGE:
        return enumRangeType->getJson();
        break;
    case SPL_BUILD_IN:
        switch (sysType)
        {
        case SPL_INTEGER:
            return getJsonWithChildren("SysTypes", getNameJson("Integer"));
            break;
        case SPL_REAL:
            return getJsonWithChildren("SysTypes", getNameJson("Real"));
            break;
        case SPL_CHAR:
            return getJsonWithChildren("SysTypes", getNameJson("Char"));
            break;
        case SPL_BOOLEAN:
            return getJsonWithChildren("SysTypes", getNameJson("Boolean"));
            break;
        default:
            break;
        }
        break;
    case SPL_USER_DEFINE:
        return userDefineType->getJson();
        break;
    default:
        break;
    }
}

string TypeDeclaration::getJson() {
    string children = name->getJson() + ", " + type->getJson();
    return getJsonWithChildren("TypeDeclaration", children);
}

string VarDeclaration::getJson() {
    string idListChildren = "";
    if(idlist && (int)idlist->size() > 0) {
        int i = 0;
        for(; i < (int)idlist->size() - 1; i++) {
            idListChildren += (*idlist)[i]->getJson() + ", ";
        }
        idListChildren += (*idlist)[i]->getJson();
    }
    string children = getJsonWithChildren("idListChildren", idListChildren) + ", " + type->getJson();
    return getJsonWithChildren("VarDeclaration", children);
    
}

string FuncDeclaration::getJson() {
    string paraListChildren = "";
    if(param && (int)param->size() > 0) {
        int i = 0;
        for(; i < (int)param->size() - 1; i++) {
            paraListChildren += (*param)[i]->getJson() + ", ";
        }
        paraListChildren += (*param)[i]->getJson();
    }
    string children = name->getJson() + ", " + getJsonWithChildren("paraListChildren", paraListChildren) + ", " + retType->getJson() + ", " + subRoutine->getJson();
    return getJsonWithChildren("FuncDeclaration", children);
    
}

string Parameter::getJson() {
    string idListChildren = "";
    if(idlist && (int)idlist->size() > 0) {
        int i = 0;
        for(; i < (int)idlist->size() - 1; i++) {
            idListChildren += (*idlist)[i]->getJson() + ", ";
        }
        idListChildren += (*idlist)[i]->getJson();
    }
    string children = getJsonWithChildren("Boolean", is_var_param ? getNameJson("true") : getNameJson("false")) + ", " + getJsonWithChildren("idListChildren", idListChildren) + ", " + type->getJson();
    return getJsonWithChildren("Parameter", children);
    
}

string Routine::getJson() {
    string constListChildren = "";
    if(const_part && (int)const_part->size() > 0) {
        int i = 0;
        for(; i < (int)const_part->size() - 1; i++) {
            constListChildren += (*const_part)[i]->getJson() + ", ";
        }
        constListChildren += (*const_part)[i]->getJson();   
    }

    string typeListChildren = "";
    if(type_part && (int)type_part->size() > 0) {
        int i = 0;
        for(; i < (int)type_part->size() - 1; i++) {
            typeListChildren += (*type_part)[i]->getJson() + ", ";
        }
        typeListChildren += (*type_part)[i]->getJson();
    }
    
    string varListChildren = "";
    if(var_part && (int)var_part->size() > 0) {
        int i = 0;
        for(; i < (int)var_part->size() - 1; i++) {
            varListChildren += (*var_part)[i]->getJson() + ", ";
        }
        varListChildren += (*var_part)[i]->getJson();
    }

    string routineListChildren = "";
    if(routine_part && (int)routine_part->size() > 0) {
        int i = 0;
        for(; i < (int)routine_part->size() - 1; i++) {
            routineListChildren += (*routine_part)[i]->getJson() + ", ";
        }
        routineListChildren += (*routine_part)[i]->getJson();
    }

    string children = getJsonWithChildren("constListChildren", constListChildren) + ", " + getJsonWithChildren("typeListChildren", typeListChildren) + ", " + getJsonWithChildren("varListChildren", varListChildren) + ", " + getJsonWithChildren("routineListChildren", routineListChildren) + ", " + routine_body->getJson();
    return getJsonWithChildren("Routine", children); 
}

string AssignStmt::getJson() {
    string children;
    switch (type)
    {
    case ASSIGN_NORMAL:
        children = lvalue->getJson() + ", " + rvalue->getJson();
        break;
    case ASSIGN_ARRAY:
        children = lvalue->getJson() + ", " + arrref->getJson() + ", " + rvalue->getJson();
        break;
    case ASSIGN_RECORD:
        children = lvalue->getJson() + ", " + rrange->getJson() + ", " + rvalue->getJson();
        break;
    default:
        break;
    }
    return getJsonWithChildren("AssignStmt", children);

}

string MathExpr::getJson() {
    string children;
    switch(op) {
        case SPL_PLUS:
            children += lhs->getJson() + ", " + getNameJson("+") + ", " + rhs->getJson();
            break;
        case SPL_MINUS:
            children += lhs->getJson() + ", " + getNameJson("-") + ", " + rhs->getJson();
            break;
        case SPL_MUL:
            children += lhs->getJson() + ", " + getNameJson("*") + ", " + rhs->getJson();
            break;
        case SPL_DIV:
            children += lhs->getJson() + ", " + getNameJson("/") + ", " + rhs->getJson();
            break;
        case SPL_GE:
            children += lhs->getJson() + ", " + getNameJson(">=") + ", " + rhs->getJson();
            break;
        case SPL_GT:
            children += lhs->getJson() + ", " + getNameJson(">") + ", " + rhs->getJson();
            break;
        case SPL_LE:
            children += lhs->getJson() + ", " + getNameJson("<=") + ", " + rhs->getJson();
            break;
        case SPL_LT:
            children += lhs->getJson() + ", " + getNameJson("<") + ", " + rhs->getJson();
            break;
        case SPL_EQUAL:
            children += lhs->getJson() + ", " + getNameJson("=") + ", " + rhs->getJson();
            break;
        case SPL_UNEQUAL:
            children += lhs->getJson() + ", " + getNameJson("!=") + ", " + rhs->getJson();
            break;
        case SPL_OR:
            children += lhs->getJson() + ", " + getNameJson("|") + ", " + rhs->getJson();
            break;
        case SPL_MOD:
            children += lhs->getJson() + ", " + getNameJson("%") + ", " + rhs->getJson();
            break;
        case SPL_AND:
            children += lhs->getJson() + ", " + getNameJson("&") + ", " + rhs->getJson();
            break;
        case SPL_NOT:
            children += /* lhs->getJson() + ", " +  */getNameJson("^") + ", " + rhs->getJson();
            break;
    }
    return getJsonWithChildren("MathExpr", children);
}

string ArrayRef::getJson() {
    string children = arr_name->getJson() + ", " + ref_index->getJson();
    return getJsonWithChildren("ArrayRef", children);
}

string RecordRef::getJson() {
    string children = record->getJson() + ", " + reference->getJson();
    return getJsonWithChildren("RecordRef", children);
}

string FuncCall::getJson() {
    string argListChildren = "";
    if(args && (int)args->size()  > 0) {
        int i = 0;
        for(; i < (int)args->size() - 1; i++) {
            argListChildren += (*args)[i]->getJson() + ", ";
        }
        argListChildren += (*args)[i]->getJson();
    }
    string children = name->getJson() + "," + getJsonWithChildren("args", argListChildren);
    return getJsonWithChildren("FuncCall", children); 

}

string ProcCall::getJson() {
    string argListChildren = "";
    if(args && (int)args->size() > 0) {
        int i = 0;
        for(; i < (int)args->size() - 1; i++) {
            argListChildren += (*args)[i]->getJson() + ", ";
        }
        argListChildren += (*args)[i]->getJson();
    }
    string children = name->getJson() + "," + getJsonWithChildren("args", argListChildren);
    return getJsonWithChildren("ProcCall", children); 
}

string SysFuncCall::getJson() {
    string argListChildren = "";
    if(args && (int)args->size() > 0) {
        int i = 0;
        for(; i < (int)args->size() - 1; i++) {
            argListChildren += (*args)[i]->getJson() + ", ";
        }
        argListChildren += (*args)[i]->getJson();
    }
    string children = getNameJson(*name) + "," + getJsonWithChildren("args", argListChildren);
    return getJsonWithChildren("SysFuncCall", children); 

}

string SysProcCall::getJson() {
    string argListChildren = "";
    if(args && (int)args->size() > 0){
        int i = 0;
        for(; i < (int)args->size() - 1; i++) {
            argListChildren += (*args)[i]->getJson() + ", ";
        }
        argListChildren += (*args)[i]->getJson();
    }
    string children = getNameJson(*name)+ "," + getJsonWithChildren("args", argListChildren) + ", " ;
    switch(sys_proc) {
        case SYS_PROC_WRITE:
            children += getNameJson("SYS_PROC_WRITE");
            break;
        case SYS_PROC_WRITELN:
            children += getNameJson("SYS_PROC_WRITELN");
            break;
        case SYS_PROC_READ:
            children += getNameJson("SYS_PROC_READ");
            break;
        case SPL_ERROR_PROCEDURE:
            children += getNameJson("SPL_ERROR_PROCEDURE");
            break;
    }
    return getJsonWithChildren("SysProcCall", children); 

}


string IfStmt::getJson() {
    string children = condition->getJson() + ", " + thenStmt->getJson() + ", " + elseStmt->getJson();
    return getJsonWithChildren("IfStmt", children);
}

string RepeatStmt::getJson() {
    string repeatListChildren = "";
    if(repeatStmt && (int)repeatStmt->size() > 0) {
        int i = 0;
        for(; i < (int)repeatStmt->size() - 1; i++) {
            repeatListChildren += (*repeatStmt)[i]->getJson() + ", ";
        }
        repeatListChildren += (*repeatStmt)[i]->getJson();
    }
    string children = condition->getJson() + "," + getJsonWithChildren("repeatStmt", repeatListChildren);
    return getJsonWithChildren("RepeatStmt", children); 
}

string WhileStmt::getJson() {
    string children = condition->getJson() + ", " + stmt->getJson();
    return getJsonWithChildren("WhileStmt", children);
}

string ForStmt::getJson() {
    // string children = var->getJson() + ", " + value->getJson() + ", " + getJsonWithChildren("Boolean", isUpTo ? "true" : "false") + ", " + step->getJson() + ", " + stmt->getJson();
    string children = var->getJson() + ", " + value->getJson() + ", " + getNameJson(isUpTo ? "true" : "false") + ", " + step->getJson() + ", " + stmt->getJson();

    return getJsonWithChildren("ForStmt", children);
}  

string CaseStmt::getJson() {
    string caseListChildren = "";
    if(CaseList && (int)CaseList->size() > 0) {
        int i = 0;
        for(; i < (int)CaseList->size() - 1; i++) {
            caseListChildren += getJsonWithChildren("Pair", (*CaseList)[i]->first->getJson() + ", " + (*CaseList)[i]->second->getJson()) + ", ";
        }
        caseListChildren += getJsonWithChildren("Pair", (*CaseList)[i]->first->getJson() + ", " + (*CaseList)[i]->second->getJson());
    }
    string children = value->getJson() + getJsonWithChildren("caseListChildren", caseListChildren);
    return getJsonWithChildren("CaseStmt", children);
}    

string GotoStmt::getJson() {
    return getJsonWithChildren("GotoStmt", getNameJson(to_string(toLabel)));
}    

string CompoundStmt::getJson() {
    string children = "";
    if(stmtList && (int)stmtList->size() > 0) {
        int i = 0;
        for(; i < (int)stmtList->size()-1; i++) {
            children += (*stmtList)[i]->getJson() + ", ";
        }
        children += (*stmtList)[i]->getJson();
    }
    return getJsonWithChildren("CompoundStmt", children);
}
