#include "utils.h"
#include "AbsSyntaxTree.h"
#include "irbuilder.h"

using namespace std;

size_t EnumRangeType::check_get_size(){
    int64_t low = 1, up = 0;
    if (this->lowerVal->getType() == this->upperVal->getType()){
        low = llvm::cast<llvm::ConstantInt>(llvm::cast<llvm::GlobalVariable>(this->lowerAddr)->getInitializer())->getSExtValue();
        up = llvm::cast<llvm::ConstantInt>(llvm::cast<llvm::GlobalVariable>(this->upperAddr)->getInitializer())->getSExtValue();
        if (low > up){
            error_exit("lower-boundary \'"+this->lowerbound->getName()+"\' is bigger than upper-boundary \'"+this->upperbound->getName()+"\'.");
        }
    }else{
        error_exit("Invalid range type.");
    }
    return up - low + 1;
}

size_t ConstRangeType::check_get_size(){
    int size = 0;
    SysTypes type = lowerbound->type;
    if (type == upperbound->type && (type == SPL_CHAR || type == SPL_INTEGER)){
        if (type == SPL_INTEGER){
            size = upperbound->val.i - lowerbound->val.i + 1;
        }else{
            size = upperbound->val.c - lowerbound->val.c + 1;
        }
    }else{
        error_exit("Invalid range type.");
    }
    if (size <= 0){
        string msg="lower-boundary \'";
        switch(this->lowerbound->type){
            case SPL_BOOLEAN:   msg+=to_string(this->lowerbound->val.b);
            case SPL_CHAR:      msg+=to_string(this->lowerbound->val.c);
            case SPL_INTEGER:   msg+=to_string(this->lowerbound->val.i);
            case SPL_REAL:      msg+=to_string(this->lowerbound->val.r);
        }
        msg+="\' is bigger than upper-boundary \'";
        switch(this->upperbound->type){
            case SPL_BOOLEAN:   msg+=to_string(this->upperbound->val.b);
            case SPL_CHAR:      msg+=to_string(this->upperbound->val.c);
            case SPL_INTEGER:   msg+=to_string(this->upperbound->val.i);
            case SPL_REAL:      msg+=to_string(this->upperbound->val.r);
        }
        msg+="\'.";
        error_exit(msg);
    }else{
        return size;
    }
}

llvm::Type* Types::getllvmType(irBuilder& irb){
    switch(this->type){
        case SPL_ARRAY:
            if(this->arrayType->range->type == SPL_CONST_RANGE){
                return llvm::ArrayType::get(this->arrayType->type->getllvmType(irb), this->arrayType->range->constRangeType->check_get_size());
            }else{
                return llvm::ArrayType::get(this->arrayType->type->getllvmType(irb), this->arrayType->range->enumRangeType->check_get_size());
            }
        case SPL_CONST_RANGE:   return irb.llvmIRBuilder->getInt32Ty();
        case SPL_ENUM_RANGE:    return irb.llvmIRBuilder->getInt32Ty();
        case SPL_BUILD_IN:
            switch (sysType){
                case SPL_INTEGER:   return irb.llvmIRBuilder->getInt32Ty();
                case SPL_REAL:      return irb.llvmIRBuilder->getDoubleTy();
                case SPL_CHAR:      return irb.llvmIRBuilder->getInt8Ty();
                case SPL_BOOLEAN:   return irb.llvmIRBuilder->getInt1Ty();
            }
            break;
        case SPL_RECORD: {
            vector<FieldDeclaration*>*& field_ptr = this->recordType->fieldlist;
            vector<llvm::Type*> recordelementType;
            for(int i = 0; i < field_ptr->size(); i++){
                size_t size = (*field_ptr)[i]->idlist->size();
                for(int j = 0; j < size; j++){
                    recordelementType.push_back((*field_ptr)[i]->type->getllvmType(irb));
                }
            }
            return llvm::StructType::get(irb.llvmContext, recordelementType);
            // return llvm::StructType::get(irb.llvmContext);
        }
        case SPL_USER_DEFINE:{
            // string tmp=this->userDefineType->getName();
            // if(irb.usrtpdef.count(tmp)!=1) error_exit("undefined type "+tmp);
            // this->type=Types::SPL_BUILD_IN;
            // switch(irb.usrtpdef[tmp]){
            //     case UTD_INT:  this->sysType=SPL_INTEGER; break;
            //     case UTD_CHAR: this->sysType=SPL_CHAR; break;
            //     case UTD_BOOL: this->sysType=SPL_BOOLEAN; break;
            //     case UTD_REAL: this->sysType=SPL_REAL; break;
            // }
            // return this->getllvmType(irb);
            // return irb.usrtpdef[tmp]->build(irb);
            error_exit("compiler failed for trying to codegen an unresolved userdefined type.", true);
        }
        case SPL_ENUM:
        case SPL_VOID: return irb.llvmIRBuilder->getVoidTy();
    }
}

// Load Variable
llvm::Value* Identifier::build(irBuilder& irb){
    llvm::Value* id_val = irb.lookupSymTab(this->getName());
    llvm::Type* id_ty = id_val->getType()->getPointerElementType();
    return new llvm::LoadInst(id_ty, id_val, "Load_id", false, irb.llvmIRBuilder->GetInsertBlock());
}

llvm::Value* ConstValue::build(irBuilder& irb){
    switch (this->type){
        case SPL_BOOLEAN:   return irb.llvmIRBuilder->getInt1(this->val.b);
        case SPL_CHAR:      return irb.llvmIRBuilder->getInt8(this->val.c);
        case SPL_INTEGER:   return irb.llvmIRBuilder->getInt32(this->val.i);
        case SPL_REAL:      return llvm::ConstantFP::get(irb.llvmIRBuilder->getDoubleTy(), this->val.r);
        default:            return nullptr;
    }
}

//math expr
llvm::Value* MathExpr::build(irBuilder& irb){
    llvm::Value* r = this->rhs->build(irb);
    if(this->op==SPL_NEGATIVE){
        if(this->lhs) error_exit("compiler failed due to inconsistent actions for negative number expression", true);
        if(r->getType()==irb.llvmIRBuilder->getInt32Ty()){
            return irb.llvmIRBuilder->CreateSub(irb.llvmIRBuilder->getInt32(0), r, "neginttmp");
        }else if(r->getType()==irb.llvmIRBuilder->getDoubleTy()){
            return irb.llvmIRBuilder->CreateFSub(llvm::ConstantFP::get(irb.llvmIRBuilder->getDoubleTy(), 0.0), r, "negdoubletmp");
        }else error_exit("a negative sign can ONLY precede INTEGER or REAL");
    }else if(this->op==SPL_NOT){
        if(this->lhs) error_exit("compiler failed due to inconsistent actions for negative number expression", true);
        return irb.llvmIRBuilder->CreateNot(r, "nottmp");
    }
    if(this->lhs==nullptr) error_exit("compiler failed due to inconsistent actions for binary expression", true);
    llvm::Value* l = this->lhs->build(irb);
    bool isDouble = l->getType()->isDoubleTy() || r->getType()->isDoubleTy();
    if(isDouble){
        if(!l->getType()->isDoubleTy()) l = irb.llvmIRBuilder->CreateUIToFP(l, irb.llvmIRBuilder->getDoubleTy(), "litod");
        else if(!r->getType()->isDoubleTy()) r = irb.llvmIRBuilder->CreateUIToFP(r, irb.llvmIRBuilder->getDoubleTy(), "ritod");
    }
    switch(this->op){
        case SPL_PLUS:      return isDouble ?  
                                irb.llvmIRBuilder->CreateFAdd(l, r, "faddtmp") 
                                : irb.llvmIRBuilder->CreateAdd(l, r, "addtmp");
        case SPL_MINUS:     return isDouble ? 
                                irb.llvmIRBuilder->CreateFSub(l, r, "fsubtmp")
                                : irb.llvmIRBuilder->CreateSub(l, r, "subtmp");
        case SPL_MUL:       return isDouble?
                                irb.llvmIRBuilder->CreateFMul(l, r, "fmultmp")
                                : irb.llvmIRBuilder->CreateMul(l, r, "multmp");
        case SPL_DIV:       return isDouble?
                                irb.llvmIRBuilder->CreateFDiv(l, r, "fdivtmp") 
                                : irb.llvmIRBuilder->CreateSDiv(l, r, "divtmp");
        case SPL_GE:        return isDouble?
                                irb.llvmIRBuilder->CreateFCmpOGE(l, r, "fgetmp")
                                : irb.llvmIRBuilder->CreateICmpSGE(l, r, "getmp");
        case SPL_GT:        return isDouble?
                                irb.llvmIRBuilder->CreateFCmpOGT(l, r, "fgttmp")
                                : irb.llvmIRBuilder->CreateICmpSGT(l, r, "gttmp");
        case SPL_LE:        return isDouble?
                                irb.llvmIRBuilder->CreateFCmpOLE(l, r, "fletmp") 
                                : irb.llvmIRBuilder->CreateICmpSLE(l, r, "letmp");
        case SPL_LT:        return isDouble?
                                irb.llvmIRBuilder->CreateFCmpOLT(l, r, "flttmp") 
                                : irb.llvmIRBuilder->CreateICmpSLT(l, r, "lttmp");
        case SPL_EQUAL:     return isDouble?
                                irb.llvmIRBuilder->CreateFCmpOEQ(l, r, "fequaltmp") 
                                : irb.llvmIRBuilder->CreateICmpEQ(l, r, "equaltmp");
        case SPL_UNEQUAL:   return isDouble?
                                irb.llvmIRBuilder->CreateFCmpONE(l, r, "fuequaltmp") 
                                : irb.llvmIRBuilder->CreateICmpNE(l, r, "uequaltmp");
        case SPL_OR:        return irb.llvmIRBuilder->CreateOr(l, r, "ortmp");
        case SPL_MOD:       return isDouble?
                                irb.llvmIRBuilder->CreateFRem(l, r, "fmodtmp")
                                : irb.llvmIRBuilder->CreateSRem(l, r, "modtmp");
        case SPL_AND:       return irb.llvmIRBuilder->CreateAnd(l, r, "andtmp");
        case SPL_NOT:       
        case SPL_NEGATIVE: error_exit("compiler failed due to inconsistent actions in MathExpression::build()", true);
    }
}

// load &arr[ref]
llvm::Value* ArrayRef::getRef(irBuilder& irb){
    string arr = this->arr_name->getName();
    llvm::Value *Ptr = irb.lookupSymTab(arr);
    llvm::Value *ref = this->ref_index->build(irb);
    llvm::Value *bottom;
    size_t sz;
    if (irb.arrayTab[arr]->range->type == Types::SPL_CONST_RANGE){
        sz=irb.arrayTab[arr]->range->constRangeType->check_get_size();
        bottom = irb.arrayTab[arr]->range->constRangeType->lowerbound->build(irb);
    }else{
        bottom = irb.arrayTab[arr]->range->enumRangeType->lowerVal;
    }
    llvm::Value *idx = irb.llvmIRBuilder->CreateSub(ref, bottom, "subtmp");
    vector<llvm::Value*> idxList;
    idxList.push_back(irb.llvmIRBuilder->getInt32(0));
    idxList.push_back(idx);
    return irb.llvmIRBuilder->CreateInBoundsGEP(Ptr, idxList, "array[idx]");
}

// load arr[ref]
llvm::Value* ArrayRef::build(irBuilder& irb){
    return irb.llvmIRBuilder->CreateLoad(this->getRef(irb), "arr[ref]");
}

// load &rec.ref
llvm::Value* RecordRef::getRef(irBuilder& irb){
    string rec = this->record->getName();
    llvm::Value* Ptr = irb.lookupSymTab(rec);
    llvm::Type* refType;
    vector<FieldDeclaration*> *field_ptr= irb.recordTab[rec]->fieldlist;
    int offset = 0;
    bool flag = false;
    for(auto & fd: *field_ptr){
        for(auto & f : *fd->idlist){
            if(f->getName() == this->reference->getName()){
                // refType = irb.lookupSymTab(this->reference->getName())->getType()->getPointerElementType();
                vector<llvm::Value*> idx{irb.llvmIRBuilder->getInt32(0), irb.llvmIRBuilder->getInt32(offset)};
                return irb.llvmIRBuilder->CreateInBoundsGEP(Ptr, idx, "record.reference");
            }
            offset++;
        }
    }
    error_exit("RECORD "+rec+" has no member called "+this->reference->getName());
}

// load rec.ref
llvm::Value* RecordRef::build(irBuilder& irb){
    return irb.llvmIRBuilder->CreateLoad(this->getRef(irb), "rec.ref");
}

//prepare
void Stmt::goto_prepare(irBuilder& irb){
    llvm::Function *cf = irb.getCurFunc();
    if(this->label >= 0){
        if(irb.labelBlock.count(this->label)<=0){
            irb.labelBlock[this->label] = llvm::BasicBlock::Create(irb.llvmContext, "_BlockLabel." + this->label, cf);
        }
        if(this->nextBB == nullptr){
            this->nextBB = llvm::BasicBlock::Create(irb.llvmContext, "_NextBlockLabel." + this->label, cf);
        }
        irb.llvmIRBuilder->CreateBr(irb.labelBlock[this->label]);
        irb.llvmIRBuilder->SetInsertPoint(irb.labelBlock[this->label]);
    }
}

//endup
void Stmt::goto_endup(irBuilder& irb){
    if (label >= 0 && nextBB != nullptr){
        irb.llvmIRBuilder->SetInsertPoint(irb.labelBlock[label]);
        irb.llvmIRBuilder->CreateBr(nextBB);
        irb.llvmIRBuilder->SetInsertPoint(nextBB);
    }
}

//Allocate stack space
llvm::AllocaInst *getLocalVarAlllocaInst(llvm::Function *cf, llvm::StringRef name, llvm::Type* type){
    return llvm::IRBuilder<>(&cf->getEntryBlock(), cf->getEntryBlock().begin()).CreateAlloca(type, nullptr, name);
}

// Push A ConstVariable into Stack
llvm::Value* ConstDeclaration::build(irBuilder& irb){
    string name = this->name->getName();
    this->Type = new Types(this->value->type);
    if(this->isGlobal){
        return new llvm::GlobalVariable(*irb.llvmModule, this->Type->getllvmType(irb), true, llvm::GlobalValue::ExternalLinkage, this->Type->initValue(irb, this->value), name);
    }else{
        return irb.llvmIRBuilder->CreateStore(this->value->build(irb), getLocalVarAlllocaInst(irb.getCurFunc(), name, this->Type->getllvmType(irb)), false);
    }
}

//initial and return Ptr
llvm::Constant* Types::initValue(irBuilder& irb, ConstValue *cv = nullptr){
    vector<llvm::Constant*> element;
    vector<llvm::Type*> recordelementType;
    llvm::StructType* recordType;
    llvm::ArrayType* arrayType;
    size_t size = 0;
    switch(this->type){
        case SPL_ARRAY:
            if(this->arrayType->range->type == SPL_CONST_RANGE){
                size = this->arrayType->range->constRangeType->check_get_size();
            }else{
                size = this->arrayType->range->enumRangeType->check_get_size();
            }
            for(int i = 0; i < size; i++){
                element.push_back(this->arrayType->type->initValue(irb, cv));
            }
            arrayType = (llvm::ArrayType*)this->getllvmType(irb);
            return llvm::ConstantArray::get(arrayType, element);
        case SPL_CONST_RANGE:case SPL_ENUM_RANGE: 
            return (cv == nullptr)? irb.llvmIRBuilder->getInt32(0) : irb.llvmIRBuilder->getInt32(cv->val.i);
        case SPL_BUILD_IN:
            switch (sysType){
                case SPL_INTEGER:   return (cv == nullptr)? 
                                        irb.llvmIRBuilder->getInt32(0) : irb.llvmIRBuilder->getInt32(cv->val.i);
                case SPL_REAL:      return (cv == nullptr)? 
                                        llvm::ConstantFP::get(irb.llvmIRBuilder->getDoubleTy(), 0.0)
                                        : llvm::ConstantFP::get(irb.llvmIRBuilder->getDoubleTy(), cv->val.r);
                case SPL_CHAR:      return (cv == nullptr)? 
                                        irb.llvmIRBuilder->getInt8(0) : irb.llvmIRBuilder->getInt8(cv->val.c);
                case SPL_BOOLEAN:   return (cv == nullptr)? 
                                        irb.llvmIRBuilder->getInt1(0) : irb.llvmIRBuilder->getInt1(cv->val.b);
            }
            break;
        case SPL_RECORD:{
            vector<FieldDeclaration*>*& field_ptr = this->recordType->fieldlist;
            for(int i = 0; i < field_ptr->size(); i++){
                size = (*field_ptr)[i]->idlist->size();
                for(int j = 0; j < size;j++){
                    // recordelementType.push_back((*field_ptr)[i]->type->getllvmType(irb));
                    element.push_back((*field_ptr)[i]->type->initValue(irb, cv));
                } 
            }
            // recordType = llvm::StructType::get(irb.llvmContext, recordelementType);
            recordType = (llvm::StructType*)this->getllvmType(irb);
            return llvm::ConstantStruct::get(recordType, element);
        }
        case SPL_ENUM:case SPL_USER_DEFINE:case SPL_VOID: 
            return nullptr;
    }
}

llvm::Value* Types::build(irBuilder& irb){
    switch (this->type){
        case SPL_ARRAY:         this->arrayType->build(irb); break;
        case SPL_CONST_RANGE:   this->constRangeType->build(irb); break;
        case SPL_ENUM_RANGE:    this->enumRangeType->build(irb); break;
        case SPL_RECORD:        this->recordType->build(irb); break;
        case SPL_ENUM:          this->enumType->build(irb); break;
        case SPL_USER_DEFINE:   
            error_exit("compiler failed for trying to codegen an unresolved userdefined type.", true);
            break;
        case SPL_BUILD_IN:      break;
        case SPL_VOID:          break;
    }
    return (llvm::Value*)this->getllvmType(irb);
}

llvm::Value* TypeDeclaration::build(irBuilder& irb){
    string tmp=this->getName();
    if(irb.usrtpdef.count(tmp)!=0) error_exit("multiple typedef of type \'"+tmp+"\'");
    switch (this->type->type){
        case Types::TpKinds::SPL_USER_DEFINE:{ 
            string dest=this->type->userDefineType->getName();
            if(irb.usrtpdef.count(dest)!=1) error_exit("undefined type "+dest);
            irb.usrtpdef[tmp]=irb.usrtpdef[dest];
            break;
        }
        default: {
            irb.usrtpdef[tmp]=this->type;
            break;
        }
        // case Types::TpKinds::SPL_BUILD_IN:{
        //     switch (this->type->sysType){
        //         case SPL_INTEGER:   irb.usrtpdef[tmp]=UTD_TYPE::UTD_INT;break;
        //         case SPL_REAL:      irb.usrtpdef[tmp]=UTD_TYPE::UTD_REAL;break;
        //         case SPL_CHAR:      irb.usrtpdef[tmp]=UTD_TYPE::UTD_CHAR;break;
        //         case SPL_BOOLEAN:   irb.usrtpdef[tmp]=UTD_TYPE::UTD_BOOL;break;
        //     }
        //     break;
        // }
        // default: error_exit("definition of a complicated type is not allowed. Only \'INTEGER\', \'BOOLEAN\', \'CHAR\', and \'REAL\' available.");
    }
    return nullptr;
}

llvm::Value* ArrayType::build(irBuilder& irb){
    return this->range->build(irb);
}

llvm::Value* RecordType::build(irBuilder& irb){
    for(auto & p: *(this->fieldlist)){
        p->build(irb);
    }
    return nullptr;
}

llvm::Value *FieldDeclaration::build(irBuilder& irb) {
    //nothing
    return nullptr;
}

llvm::Value* EnumType::build(irBuilder& irb){
    //nothing to do
    return nullptr;
}

llvm::Value* ConstRangeType::build(irBuilder& irb){
    this->check_get_size();
    return nullptr;
}

llvm::Value *EnumRangeType::build(irBuilder& irb) {
    this->upperVal = this->upperbound->build(irb);
    this->lowerVal = this->lowerbound->build(irb);
    this->upperAddr = irb.lookupSymTab(this->upperbound->getName());
    this->lowerAddr = irb.lookupSymTab(this->lowerbound->getName());
    this->check_get_size();
    return nullptr;
}

llvm::Value *VarDeclaration::build(irBuilder& irb) {
    llvm::Value* alloc = nullptr;
    llvm::Type* varType;
    llvm::Constant* initval;
    for (auto & id : *(this->idlist)){
        if(this->type->type == Types::SPL_USER_DEFINE){
            string tmp=this->type->userDefineType->getName();
            if(irb.usrtpdef.count(tmp)!=1) error_exit("undefined type "+tmp);
            varType = (llvm::Type*)irb.usrtpdef[tmp]->build(irb);
            initval = irb.usrtpdef[tmp]->initValue(irb);
            if (irb.usrtpdef[tmp]->type == Types::SPL_ARRAY){
                irb.arrayTab[id->getName()] = irb.usrtpdef[tmp]->arrayType;
            }else if(irb.usrtpdef[tmp]->type == Types::SPL_RECORD){
                irb.recordTab[id->getName()] = irb.usrtpdef[tmp]->recordType;
            }
        }else{
            if (this->type->type == Types::SPL_ARRAY){
                irb.arrayTab[id->getName()] = this->type->arrayType;
            }else if(this->type->type == Types::SPL_RECORD){
                irb.recordTab[id->getName()] = this->type->recordType;
            }
            // else if(this->type->type == Types::SPL_USER_DEFINE){
            //     string tmp=this->type->userDefineType->getName();
            //     if(irb.usrtpdef.count(tmp)!=1) error_exit("undefined type "+tmp);
            //     this->type->type=Types::SPL_BUILD_IN;
            //     switch(irb.usrtpdef[tmp]){
            //         case UTD_INT:  this->type->sysType=SPL_INTEGER; break;
            //         case UTD_CHAR: this->type->sysType=SPL_CHAR; break;
            //         case UTD_BOOL: this->type->sysType=SPL_BOOLEAN; break;
            //         case UTD_REAL: this->type->sysType=SPL_REAL; break;
            //     }
            // }
            varType = (llvm::Type*)(this->type->build(irb));
            initval = this->type->initValue(irb);
        }
        if(this->isGlobal){
            alloc = new llvm::GlobalVariable(*irb.llvmModule, varType, false, llvm::GlobalValue::ExternalLinkage, initval, id->getName());
        }else{
            alloc = getLocalVarAlllocaInst(irb.getCurFunc(), id->getName(), varType);
        }
    }
    return alloc;
}

llvm::Value *FuncDeclaration::build(irBuilder& irb) {
    //Prototype
    vector<llvm::Type*> argTypes;
    for (auto & argType : *(this->param)){
        if (argType->is_var_param){
            llvm::Type* tmp;
            switch(argType->type->sysType){
                case SPL_INTEGER:   tmp = llvm::Type::getInt32PtrTy(irb.llvmContext);break;
                case SPL_REAL:      tmp = llvm::Type::getDoublePtrTy(irb.llvmContext);break;
                case SPL_CHAR:      tmp = llvm::Type::getInt8PtrTy(irb.llvmContext);break;
                case SPL_BOOLEAN:   tmp = llvm::Type::getInt1PtrTy(irb.llvmContext);break;
                default:            error_exit("Meet unsupported pointer type.");
            }
            argTypes.insert(argTypes.end(), argType->idlist->size(), tmp);
        }else{
            argTypes.insert(argTypes.end(), argType->idlist->size(), argType->type->getllvmType(irb));
        }
    }
    llvm::FunctionType *funcType = llvm::FunctionType::get(this->retType->getllvmType(irb), argTypes, false);
    llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, this->name->getName(), irb.llvmModule.get());
    irb.pushFunc(function);
    
    //Block
    llvm::BasicBlock *newBlock = llvm::BasicBlock::Create(irb.llvmContext, "entrypoint", function, nullptr);
    irb.llvmIRBuilder->SetInsertPoint(newBlock);
    
    //Parameters
    llvm::Function::arg_iterator argIt =  function->arg_begin();
    int index = 1;
    for (auto & args : *(this->param)){
        for (auto & arg : *(args->idlist)){
            llvm::Value *alloc = nullptr;
            if (args->is_var_param){
                function->addAttribute(index, llvm::Attribute::NonNull);
                alloc = irb.llvmIRBuilder->CreateGEP(argIt++, irb.llvmIRBuilder->getInt32(0), arg->getName());
            }else{
                alloc = getLocalVarAlllocaInst(function, arg->getName(), args->type->getllvmType(irb));
                irb.llvmIRBuilder->CreateStore(argIt++, alloc);
            }
            index++;
        }
    }
    
    //Return
    llvm::Value *res = nullptr;
    if (this->retType->type != Types::SPL_VOID){
        res = getLocalVarAlllocaInst(function, this->name->getName(), this->retType->getllvmType(irb));
    }
    
    //Sub routine
    this->subRoutine->build(irb);
    
    //Return value
    if (this->retType->type != Types::SPL_VOID){
        auto returnInst = this->name->build(irb);
        irb.llvmIRBuilder->CreateRet(returnInst);
    }else{
        irb.llvmIRBuilder->CreateRetVoid();
    }
    
    //Pop back
    irb.popFunc();
    irb.llvmIRBuilder->SetInsertPoint(&(irb.getCurFunc())->getBasicBlockList().back());
    return function;
}

llvm::Value *Parameter::build(irBuilder& irb) {
    //nothing to do
    return nullptr;
}

llvm::Value *Routine::build(irBuilder& irb) {
    llvm::Value* res = nullptr;
    
    //Const declareation part
    for (auto & constDecl : *(this->const_part)){
        res = constDecl->build(irb);
    }
    //Type declareation part
    for (auto & typeDecl : *(this->type_part)){
        res = typeDecl->build(irb);
    }
    //Variable declareation part
    for (auto & varDecl : *(this->var_part)){
        res = varDecl->build(irb);
    }
    //Routine declareation part
    for (auto & routineDecl : *(this->routine_part)){
        res = routineDecl->build(irb);
    }
    
    //Routine body
    res = routine_body->build(irb);
    return res;
}

llvm::Value *Program::build(irBuilder& irb) {
    //Main function prototype
    vector<llvm::Type*> argTypes;
    llvm::FunctionType * funcType = llvm::FunctionType::get(irb.llvmIRBuilder->getVoidTy(), makeArrayRef(argTypes), false);
    irb.mainFunc = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, "main", irb.llvmModule.get());
    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(irb.llvmContext, "entrypoint", irb.mainFunc, 0);
    
    irb.pushFunc(irb.mainFunc);
    irb.llvmIRBuilder->SetInsertPoint(basicBlock);
    //Code generate
    this->routine->setGlobal();
    this->routine->build(irb);
    irb.llvmIRBuilder->CreateRetVoid();
    irb.popFunc();
    
    return nullptr;
}

llvm::Value *FuncCall::build(irBuilder& irb) {
    this->goto_prepare(irb);
    llvm::Function *function = irb.llvmModule->getFunction(this->name->getName());
    if (function == nullptr){
        error_exit("Function not defined: " + this->name->getName());
    }
    vector<llvm::Value*> args;
    llvm::Function::arg_iterator argIt =  function->arg_begin();
    for (auto & arg : *(this->args)){
        if (argIt->hasNonNullAttr()){
            llvm::Value * addr = irb.lookupSymTab(dynamic_cast<Identifier*>(arg)->getName());
            args.push_back(addr);
        }else{
            args.push_back(arg->build(irb));
        }
        argIt++;
    }
    llvm::Value *res = irb.llvmIRBuilder->CreateCall(function, args);
    this->goto_endup(irb);
    return res;
}

llvm::Value *ProcCall::build(irBuilder& irb) {
    this->goto_prepare(irb);
    llvm::Function *function = irb.llvmModule->getFunction(this->name->getName());
    if (function == nullptr){
        error_exit("Procedure not defined: " + this->name->getName());
    }
    vector<llvm::Value*> args;
    llvm::Function::arg_iterator argIt =  function->arg_begin();
    for (auto & arg : *(this->args)){
        if (argIt->hasNonNullAttr()){
            llvm::Value * addr = irb.lookupSymTab(dynamic_cast<Identifier*>(arg)->getName());
            args.push_back(addr);
        }else{
            args.push_back(arg->build(irb));
        }
        argIt++;
    }
    llvm::Value* res = irb.llvmIRBuilder->CreateCall(function, args);
    this->goto_endup(irb);
    return res;
}

llvm::Value *SysFuncCall::build(irBuilder& irb) {
    this->goto_prepare(irb);
    if(this->args->size()!=1){
        error_exit("Need exact 1 argument for sysfunction: "+*(this->name));
    }
    llvm::Function *function = nullptr;
    llvm::Value *arg=(*(this->args))[0]->build(irb);
    string callname;
    if(*(this->name)=="abs"){
        if(arg->getType()==irb.llvmIRBuilder->getInt32Ty()) callname="abs_i";
        else if(arg->getType()==irb.llvmIRBuilder->getDoubleTy()) callname="abs_d";
        else error_exit("sysfunction abs accepts only interger or double");
    }else if(*(this->name)=="chr"){
        if(arg->getType()!=irb.llvmIRBuilder->getInt32Ty()) error_exit("sysfunction chr accepts only interger");
        else callname="chr";
    }else if(*(this->name)=="ord"){
        if(arg->getType()!=irb.llvmIRBuilder->getInt8Ty()) error_exit("sysfunction ord accepts only char");
        else callname="ord";
    }else if(*(this->name)=="odd"){
        if(arg->getType()!=irb.llvmIRBuilder->getInt32Ty()) error_exit("sysfunction odd accepts only interger");
        else callname="odd";
    }else if(*(this->name)=="pred"){
        if(arg->getType()==irb.llvmIRBuilder->getInt32Ty()) callname="pred_i";
        else if(arg->getType()==irb.llvmIRBuilder->getInt8Ty()) callname="pred_c";
        else error_exit("sysfunction pred accepts only interger or char");
    }else if(*(this->name)=="succ"){
        if(arg->getType()==irb.llvmIRBuilder->getInt32Ty()) callname="succ_i";
        else if(arg->getType()==irb.llvmIRBuilder->getInt8Ty()) callname="succ_c";
        else error_exit("sysfunction succ accepts only interger or char");
    }else if(*(this->name)=="sqr"){
        if(arg->getType()==irb.llvmIRBuilder->getInt32Ty()) callname="sqr_i";
        else if(arg->getType()==irb.llvmIRBuilder->getDoubleTy()) callname="sqr_d";
        else error_exit("sysfunction sqr accepts only interger or double");
    }else if(*(this->name)=="sqrt"){
        if(arg->getType()==irb.llvmIRBuilder->getInt32Ty()) callname="sqrt_i";
        else if(arg->getType()==irb.llvmIRBuilder->getDoubleTy()) callname="sqrt_d";
        else error_exit("sysfunction sqrt accepts only interger or double");
    }else error_exit("compiler failed in parsing sysfunctions", true);
    if(irb.libfuncs.count(callname)!=1) error_exit("compiler failed in libfunction initialization", true);
    llvm::Value *res = irb.llvmIRBuilder->CreateCall(irb.libfuncs[callname], {arg}, callname);
    this->goto_endup(irb);
    return res;
}

llvm::Value *SysProcCall::SysProcWrite(irBuilder& irb, bool isLn){
    string tmpstr = "";
    vector<llvm::Value*> params;
    for(auto & arg : *(this->args)){
        llvm::Value* argValue = arg->build(irb);
        if (argValue->getType() == irb.llvmIRBuilder->getInt32Ty()){
            tmpstr += "%d";
        }else if (argValue->getType() == irb.llvmIRBuilder->getInt8Ty()){
            tmpstr += "%c";
        }else if (argValue->getType() == irb.llvmIRBuilder->getInt1Ty()){
            tmpstr += "%d";
        }else if (argValue->getType()->isDoubleTy()){
            tmpstr += "%lf";
        }else{
            error_exit("Unwritable type.");
        }
        params.push_back(argValue);
    }
    if(isLn) tmpstr += "\n";
    auto formatstring = new llvm::GlobalVariable(*irb.llvmModule,
                                                llvm::ArrayType::get(irb.llvmIRBuilder->getInt8Ty(),
                                                tmpstr.size() + 1),
                                                true,
                                                llvm::GlobalValue::ExternalLinkage,
                                                llvm::ConstantDataArray::getString(irb.llvmContext, tmpstr.c_str()),
                                                ".str");
    auto zero = llvm::Constant::getNullValue(irb.llvmIRBuilder->getInt32Ty());
    // llvm::Constant* indices[] = {zero, zero};
    auto varRef = llvm::ConstantExpr::getGetElementPtr(formatstring->getType()->getElementType(), formatstring, vector<llvm::Constant*>{zero, zero});
    params.insert(params.begin(), varRef);
    return irb.llvmIRBuilder->CreateCall(irb.libfuncs["printf"], llvm::makeArrayRef(params), "printf");
}

llvm::Value *SysProcCall::SysProcRead(irBuilder& irb){
    string tmpstr = "";
    vector<llvm::Value*> params;
    auto arg = this->args->front();
    llvm::Value *argAddr, *argValue;
    
    argAddr = irb.lookupSymTab(dynamic_cast<Identifier*>(arg)->getName());
    argValue = arg->build(irb);
    if (argValue->getType() == irb.llvmIRBuilder->getInt32Ty()){
        tmpstr += "%d";
    }else if (argValue->getType() == irb.llvmIRBuilder->getInt8Ty()){
        tmpstr += "%c";
    }else if (argValue->getType() == irb.llvmIRBuilder->getInt1Ty()){
        tmpstr += "%d";
    }else if (argValue->getType()->isDoubleTy()){
        tmpstr += "%lf";
    }else{
        error_exit("Unreadable type.");
    }
    params.push_back(argAddr);
    params.insert(params.begin(), irb.llvmIRBuilder->CreateGlobalStringPtr(tmpstr));
    return irb.llvmIRBuilder->CreateCall(irb.libfuncs["scanf"], params, "scanf");
}

llvm::Value *SysProcCall::build(irBuilder& irb) {
    llvm::Value *res = nullptr;
    this->goto_prepare(irb);
    switch (this->sys_proc) {
        case SYS_PROC_READ:         res = this->SysProcRead(irb); break;
        case SYS_PROC_WRITE:        res = this->SysProcWrite(irb, false); break;
        case SYS_PROC_WRITELN:      res = this->SysProcWrite(irb, true); break;
        case SPL_ERROR_PROCEDURE:   error_exit("Unknown System Procedure");
    }
    this->goto_endup(irb);
    return res;
}

llvm::Value *AssignStmt::build(irBuilder& irb) {
    llvm::Value *res = nullptr;
    this->goto_prepare(irb);
    switch (this->type){
        case ASSIGN_NORMAL:     res = irb.llvmIRBuilder->CreateStore(this->rvalue->build(irb), irb.lookupSymTab(this->lvalue->getName())); break;
        case ASSIGN_ARRAY:  res = irb.llvmIRBuilder->CreateStore(this->rvalue->build(irb), ArrayRef(this->lvalue, this->arrref).getRef(irb)); break;
        case ASSIGN_RECORD: res = irb.llvmIRBuilder->CreateStore(this->rvalue->build(irb), RecordRef(this->lvalue, this->rrange).getRef(irb)); break;
    }
    this->goto_endup(irb);
    return res;
}

llvm::Value *GotoStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    llvm::Value *res = nullptr;
    if (irb.labelBlock.count(this->toLabel)<=0){
        irb.labelBlock[this->toLabel] = llvm::BasicBlock::Create(irb.llvmContext, "_Label." + this->toLabel, irb.getCurFunc());
    }
    res = irb.llvmIRBuilder->CreateBr(irb.labelBlock[this->toLabel]);

    this->goto_endup(irb);
    return res;
}

llvm::Value *IfStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    
    llvm::Value *condValue = this->condition->build(irb), *thenValue = nullptr, *elseValue = nullptr;
    condValue = irb.llvmIRBuilder->CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(irb.llvmContext), 0, true), "ifCond");

    llvm::Function *TheFunction = irb.getCurFunc();
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(irb.llvmContext, "then", TheFunction);
    llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(irb.llvmContext, "else", TheFunction);
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(irb.llvmContext, "merge", TheFunction);

    //Then
    auto branch = irb.llvmIRBuilder->CreateCondBr(condValue, thenBB, elseBB);
    irb.llvmIRBuilder->SetInsertPoint(thenBB);
    thenValue = this->thenStmt->build(irb);
    irb.llvmIRBuilder->CreateBr(mergeBB);
    thenBB = irb.llvmIRBuilder->GetInsertBlock();

    //Else
    irb.llvmIRBuilder->SetInsertPoint(elseBB);
    if (this->elseStmt != nullptr)
    {
        elseValue = this->elseStmt->build(irb);
    }
    irb.llvmIRBuilder->CreateBr(mergeBB);
    elseBB = irb.llvmIRBuilder->GetInsertBlock();

    irb.llvmIRBuilder->SetInsertPoint(mergeBB);
    
    this->goto_endup(irb);
    return branch;
}

llvm::Value *RepeatStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    
    llvm::Function *TheFunction = irb.getCurFunc();
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(irb.llvmContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(irb.llvmContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(irb.llvmContext, "afterLoop", TheFunction);
    
    irb.llvmIRBuilder->CreateBr(loopBB);
    irb.llvmIRBuilder->SetInsertPoint(loopBB);
    for (auto & stmt : *(this->repeatStmt))
    {
        stmt->build(irb);
    }
    irb.llvmIRBuilder->CreateBr(condBB);
    loopBB = irb.llvmIRBuilder->GetInsertBlock();
    
    irb.llvmIRBuilder->SetInsertPoint(condBB);
    llvm::Value *condValue = this->condition->build(irb);
    condValue = irb.llvmIRBuilder->CreateICmpEQ(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(irb.llvmContext), 0, true), "repeateCond");
    auto branch = irb.llvmIRBuilder->CreateCondBr(condValue, loopBB, afterBB);
    
    irb.llvmIRBuilder->SetInsertPoint(afterBB);
    this->goto_endup(irb);
    return branch;
}

llvm::Value *WhileStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);

    llvm::Function *TheFunction = irb.getCurFunc();
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(irb.llvmContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(irb.llvmContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(irb.llvmContext, "afterLoop", TheFunction);
    
    irb.llvmIRBuilder->CreateBr(condBB);
    irb.llvmIRBuilder->SetInsertPoint(condBB);
    llvm::Value *condValue = this->condition->build(irb);
    condValue = irb.llvmIRBuilder->CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(irb.llvmContext), 0, true), "whileCond");
    auto branch = irb.llvmIRBuilder->CreateCondBr(condValue, loopBB, afterBB);
    condBB = irb.llvmIRBuilder->GetInsertBlock();
    
    irb.llvmIRBuilder->SetInsertPoint(loopBB);
    this->stmt->build(irb);
    irb.llvmIRBuilder->CreateBr(condBB);
    
    irb.llvmIRBuilder->SetInsertPoint(afterBB);
    this->goto_endup(irb);
    return branch;
}

llvm::Value *ForStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    //Init
    llvm::Function *TheFunction = irb.getCurFunc();
    llvm::Value* startValue = this->value->build(irb);
    llvm::Value* endValue = this->step->build(irb);
    llvm::Value *condValue = nullptr, *curValue = nullptr, *varValue = irb.lookupSymTab(this->var->getName());
    irb.llvmIRBuilder->CreateStore(startValue, varValue);
    
    llvm::BasicBlock *condBB = llvm::BasicBlock::Create(irb.llvmContext, "cond", TheFunction);
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(irb.llvmContext, "loop", TheFunction);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(irb.llvmContext, "afterLoop", TheFunction);
    
    irb.llvmIRBuilder->CreateBr(condBB);
    irb.llvmIRBuilder->SetInsertPoint(condBB);

    curValue = this->var->build(irb);
    if (this->isUpTo){
        condValue = irb.llvmIRBuilder->CreateICmpSLE(curValue, endValue);
    }else{
        condValue = irb.llvmIRBuilder->CreateICmpSGE(curValue, endValue);
    }
    condValue = irb.llvmIRBuilder->CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(irb.llvmContext), 0, true), "forCond");
    auto branch = irb.llvmIRBuilder->CreateCondBr(condValue, loopBB, afterBB);
    condBB = irb.llvmIRBuilder->GetInsertBlock();
    
    irb.llvmIRBuilder->SetInsertPoint(loopBB);
    this->stmt->build(irb);
    llvm::Value *tmpValue = irb.llvmIRBuilder->CreateAdd(curValue, irb.llvmIRBuilder->getInt32(this->isUpTo ? 1 : -1));
    irb.llvmIRBuilder->CreateStore(tmpValue, varValue);
    irb.llvmIRBuilder->CreateBr(condBB);
    loopBB = irb.llvmIRBuilder->GetInsertBlock();
    
    irb.llvmIRBuilder->SetInsertPoint(afterBB);
    this->goto_endup(irb);
    return branch;
}

llvm::Value *CaseStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    
    llvm::Value *cmpValue = this->value->build(irb), *condValue = nullptr;
    llvm::Function *TheFunction = irb.getCurFunc();
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(irb.llvmContext, "afterCase", TheFunction);
    vector<llvm::BasicBlock*> switchBBs, caseBBs;
    for (int i = 1; i <= this->CaseList->size(); i++){
        switchBBs.push_back(llvm::BasicBlock::Create(irb.llvmContext, "switch", TheFunction));
        caseBBs.push_back(llvm::BasicBlock::Create(irb.llvmContext, "case", TheFunction));
    }
    irb.llvmIRBuilder->CreateBr(switchBBs[0]);
    for (int i = 0; i < this->CaseList->size(); i++){
        //Switch
        irb.llvmIRBuilder->SetInsertPoint(switchBBs[i]);
        condValue = irb.llvmIRBuilder->CreateICmpEQ(cmpValue, (*CaseList)[i]->first->build(irb), "equaltmp");
        if (i < this->CaseList->size() - 1){
            irb.llvmIRBuilder->CreateCondBr(condValue, caseBBs[i], switchBBs[i + 1]);
        }else{
            irb.llvmIRBuilder->CreateCondBr(condValue, caseBBs[i], afterBB);
        }
        
        //Case
        irb.llvmIRBuilder->SetInsertPoint(caseBBs[i]);
        (*CaseList)[i]->second->build(irb);
        irb.llvmIRBuilder->CreateBr(afterBB);
    }
    
    //After
    irb.llvmIRBuilder->SetInsertPoint(afterBB);
    this->goto_endup(irb);
    return nullptr;
}

llvm::Value *CompoundStmt::build(irBuilder& irb) {
    this->goto_prepare(irb);
    llvm::Value *lastValue = nullptr;
    for (auto & stmt : *(this->stmtList)){
        lastValue = stmt->build(irb);
    }
    this->goto_endup(irb);
    return lastValue;
}

string getSysTypesString(SysTypes tp){
    switch(tp){
        case SysTypes::SPL_INTEGER: return "INTEGER";
        case SysTypes::SPL_CHAR:    return "CHAR";
        case SysTypes::SPL_BOOLEAN: return "BOOLEAN";
        case SysTypes::SPL_REAL:    return "REAL";
    }
    return "";
}

#define GET_VALUE_OF_CONSTVALUE(cv) \
        (cv->type==SysTypes::SPL_INTEGER ? cv->val.i : \
        (cv->type==SysTypes::SPL_REAL ? cv->val.r : \
        (cv->type==SysTypes::SPL_BOOLEAN ? cv->val.b : cv->val.c)))

Expr* ConstantFold(Expr* l, MathExpr::Ops op, Expr* r){
    ConstValue *cl=dynamic_cast<ConstValue*>(l), *cr=dynamic_cast<ConstValue*>(r);
    if(cr!=nullptr){
        if(op==MathExpr::SPL_NEGATIVE){
            if(l || cl) error_exit("compiler failed due to inconsistent actions for negative number expression", true);
            if(cr->type==SysTypes::SPL_INTEGER){
                return new ConstValue(-cr->val.i);
            }else if(cr->type==SysTypes::SPL_REAL){
                return new ConstValue(-cr->val.r);
            }else error_exit("a negative sign can ONLY precede INTEGER or REAL");
        }else if(op==MathExpr::SPL_NOT){
            if(l || cl) error_exit("compiler failed due to inconsistent actions for negative number expression", true);
            switch(cr->type){
                case SysTypes::SPL_BOOLEAN: return new ConstValue(!cr->val.b);
                case SysTypes::SPL_INTEGER: return new ConstValue(~cr->val.i);
                case SysTypes::SPL_CHAR: error_exit("cannot use NOT before a char");
                case SysTypes::SPL_REAL: error_exit("cannot use NOT before a real");
            }
        }
        if(cl!=nullptr){
            SysTypes tl=cl->type, tr=cr->type;
            unsigned int mask=0;
            if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_INTEGER) mask = 0x04;
            if(tl==SysTypes::SPL_REAL) mask |= 0x01;
            if(tr==SysTypes::SPL_REAL) mask |= 0x02;
            switch(op){
                case MathExpr::SPL_PLUS:    {
                    switch(mask){
                        case 0: error_exit("cannot use PLUS on char or boolean");
                        case 4: return new ConstValue(cl->val.i+cr->val.i);
                        default: return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)+(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                }
                case MathExpr::SPL_MINUS:   {
                    switch(mask){
                        case 0: error_exit("cannot use MINUS on char or boolean");
                        case 4: return new ConstValue(cl->val.i-cr->val.i);
                        default: return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)-(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                }
                case MathExpr::SPL_MUL:     {
                    switch(mask){
                        case 0: error_exit("cannot use MUL on char or boolean");
                        case 4: return new ConstValue(cl->val.i*cr->val.i);
                        default: return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)*(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                }
                case MathExpr::SPL_DIV:     {
                    if(tr==SysTypes::SPL_INTEGER && cr->val.i==0 || tr==SysTypes::SPL_REAL && cr->val.r==0.0)
                        error_exit("cannot preform an zero divsion");
                    switch(mask){
                        case 0: error_exit("cannot use DIV on char or boolean");
                        case 4: return new ConstValue(cl->val.i/cr->val.i);
                        default: return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)/(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                }
                case MathExpr::SPL_GE:      {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)>=GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)>=(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_GT:      {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)>GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)>(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_LE:      {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)<=GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)<=(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_LT:      {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)<GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)<(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_EQUAL:   {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)==GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)==(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_UNEQUAL: {
                    if(tl==tr){
                        return new ConstValue(GET_VALUE_OF_CONSTVALUE(cl)!=GET_VALUE_OF_CONSTVALUE(cr));
                    }else if(tl==SysTypes::SPL_INTEGER && tr==SysTypes::SPL_REAL || tl==SysTypes::SPL_REAL && tr==SysTypes::SPL_INTEGER){
                        return new ConstValue((double)GET_VALUE_OF_CONSTVALUE(cl)!=(double)GET_VALUE_OF_CONSTVALUE(cr));
                    }
                    error_exit("cannot preform comparison between uncompatible types, i.e. "+getSysTypesString(tl)+" and "+getSysTypesString(tr));
                }
                case MathExpr::SPL_MOD:     {
                    if(mask==4){
                        if(cr->val.i==0) error_exit("cannot MOD zero");
                        return new ConstValue(cl->val.i%cr->val.i);
                    }else error_exit("MOD can ONLY be performed on INTEGER");
                }
                case MathExpr::SPL_OR:      {
                    if(mask==4){
                        return new ConstValue(cl->val.i|cr->val.i);
                    }else if(tl==SysTypes::SPL_BOOLEAN && tr==SysTypes::SPL_BOOLEAN){
                        return new ConstValue(cl->val.b||cr->val.b);
                    }else error_exit("OR can ONLY be performed on two INTEGERs or on two BOOLEANs");
                }
                case MathExpr::SPL_AND:     {
                    if(mask==4){
                        return new ConstValue(cl->val.i&cr->val.i);
                    }else if(tl==SysTypes::SPL_BOOLEAN && tr==SysTypes::SPL_BOOLEAN){
                        return new ConstValue(cl->val.b&&cr->val.b);
                    }else error_exit("AND can ONLY be performed on two INTEGERs or on two BOOLEANs");
                }
                case MathExpr::SPL_NOT:
                case MathExpr::SPL_NEGATIVE:
                    error_exit("compiler failed due to inconsistent actions in ConstantFold()", true);
            }
        }
    }//else if(cl!=nullptr) error_exit("compiler failed due to inconsistent actions in ConstantFold()", true);
    return new MathExpr(l, op, r);
}