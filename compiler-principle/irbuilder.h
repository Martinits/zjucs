#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
// #include <llvm/Analysis/ConstantFolding.h>
#include "AbsSyntaxTree.h"

using namespace std;

enum UTD_TYPE{
    UTD_INT,
    UTD_CHAR,
    UTD_BOOL,
    UTD_REAL
};

class irBuilder{
public:
    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> *llvmIRBuilder;
    unique_ptr<llvm::Module> llvmModule;
    llvm::Function *mainFunc;
    map<string, llvm::Function*> libfuncs;
    vector<llvm::Function*> functionStack;
    map<string, ArrayType*> arrayTab;
    map<string, RecordType*> recordTab;
    map<unsigned int, llvm::BasicBlock*> labelBlock;
    unordered_map<string, Types*> usrtpdef;
    irBuilder();
    void build(Program& prog, const string outfilename);
    llvm::Value* lookupSymTab(const string& name);
    llvm::Function* getCurFunc(){
        return functionStack.back();
    }
    void pushFunc(llvm::Function* func){
        functionStack.push_back(func);
    }
    void popFunc(){
        functionStack.pop_back();
    }
};