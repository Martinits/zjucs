#include "AbsSyntaxTree.h"
#include "irbuilder.h"
#include "utils.h"

using namespace std;

irBuilder::irBuilder(){
    llvmIRBuilder = new llvm::IRBuilder<>(llvmContext);
    llvmModule=unique_ptr<llvm::Module>(new llvm::Module("main", llvmContext));
    //libfuncs
    struct libfuncinfo{
        string name;
        llvm::Type *rettp;
        vector<llvm::Type*> params;
        bool isvararg;
    };
    const vector<libfuncinfo> libfuncnames={
        {"printf", llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt8PtrTy()}, true },
        {"scanf",  llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt8PtrTy()}, true },
        {"abs_i",  llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt32Ty()},   false},
        {"abs_d",  llvmIRBuilder->getDoubleTy(), {llvmIRBuilder->getDoubleTy()},  false},
        {"chr",    llvmIRBuilder->getInt8Ty(),   {llvmIRBuilder->getInt32Ty()},   false},
        {"ord",    llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt8Ty()},    false},
        {"odd",    llvmIRBuilder->getInt1Ty(),   {llvmIRBuilder->getInt32Ty()},   false},
        {"pred_i", llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt32Ty()},   false},
        {"pred_c", llvmIRBuilder->getInt8Ty(),   {llvmIRBuilder->getInt8Ty()},    false},
        {"succ_i", llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt32Ty()},   false},
        {"succ_c", llvmIRBuilder->getInt8Ty(),   {llvmIRBuilder->getInt8Ty()},    false},
        {"sqr_i",  llvmIRBuilder->getInt32Ty(),  {llvmIRBuilder->getInt32Ty()},   false},
        {"sqr_d",  llvmIRBuilder->getDoubleTy(), {llvmIRBuilder->getDoubleTy()},  false},
        {"sqrt_i", llvmIRBuilder->getDoubleTy(), {llvmIRBuilder->getInt32Ty()},   false},
        {"sqrt_d", llvmIRBuilder->getDoubleTy(), {llvmIRBuilder->getDoubleTy()},  false}
    };
    for(auto & n : libfuncnames){
        auto functmp = llvm::Function::Create(llvm::FunctionType::get(n.rettp, llvm::makeArrayRef(n.params), n.isvararg), llvm::Function::ExternalLinkage, llvm::Twine(n.name), llvmModule.get());
        functmp->setCallingConv(llvm::CallingConv::C);
        libfuncs[n.name]=functmp;
    }
}

void irBuilder::build(Program& prog, const string outfilename){
    prog.build(*this);
    error_code ec;
    llvm::raw_fd_ostream outfile(outfilename, ec);
    if(ec){
        error_exit("Fail to create output stream for "+outfilename+", redirecting output to std::cout.");
        llvmModule->print(llvm::outs(), nullptr);
    }else{
        llvmModule->print(outfile, nullptr);
    }
    outfile.close();
}

llvm::Value* irBuilder::lookupSymTab(const string& id){
    llvm::Value *tmp=nullptr;
    for(auto it=functionStack.rbegin();it!=functionStack.rend();++it){
        tmp=(*it)->getValueSymbolTable()->lookup(id);
        if(tmp!=nullptr){
            verbose("found "+id+" in "+(string)((*it)->getName()));
            return tmp;
        }
    }
    tmp=llvmModule->getGlobalVariable(id);
    if(tmp==nullptr) error_exit("Undefined variable or function: "+id);
    else{
        verbose("found "+id+" as global");
        return tmp;
    }
    return nullptr;
}
