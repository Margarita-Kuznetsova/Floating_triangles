// clang++ llvm_giver.cpp -I/usr/include -std=c++14   -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/lib -lLLVM-14   

#include <iostream>
#include <fstream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

llvm::GlobalVariable* DATA = nullptr;
llvm::GlobalVariable* COORD = nullptr;
llvm::GlobalVariable* CALCULATE_FIRST = nullptr;
llvm::LLVMContext context;
llvm::IRBuilder<> builder (context);

llvm::Value* getConst (int type , int value)
{
    llvm::Type* Ty = nullptr;
    switch (type)
    {
    case 1:
        Ty = builder.getInt1Ty ();
        break;
    case 8:
        Ty = builder.getInt8Ty ();
        break;
    case 16:
        Ty = builder.getInt16Ty ();
        break;
    case 32:
        Ty = builder.getInt32Ty ();
        break;
    case 64:
        Ty = builder.getInt64Ty ();
        break;
    default:
        std::abort ();
        break;
    }
    return llvm::ConstantInt::get (Ty , value);
}

int main ()
{
    llvm::InitializeNativeTarget ();
    llvm::InitializeNativeTargetAsmPrinter ();
    //target triple = "x86_64-pc-linux-gnu"

    //; ModuleID = 'logic.c'
    //source_filename = "logic.c"
    llvm::Module* module = new llvm::Module ("logic" , context);

    //@data = common global [400 x [200 x i32]] zeroinitializer, align 16
    llvm::Type* DataTy = llvm::ArrayType::get (
        llvm::ArrayType::get (builder.getInt32Ty () , 200) , 400);
    module->getOrInsertGlobal ("data" , DataTy);
    DATA = module->getNamedGlobal ("data");
    DATA->setLinkage (llvm::GlobalValue::CommonLinkage);
    DATA->setAlignment (llvm::MaybeAlign (16));
    DATA->setInitializer (llvm::ConstantAggregateZero::get (DataTy));

    //@coord = dso_local local_unnamed_addr global [400 x i32] zeroinitializer, align 16
    llvm::Type* CoordTy = llvm::ArrayType::get (builder.getInt32Ty () , 400);
    module->getOrInsertGlobal ("coord" , CoordTy);
    COORD = module->getNamedGlobal ("coord");
    COORD->setLinkage (llvm::GlobalValue::CommonLinkage);
    COORD->setAlignment (llvm::MaybeAlign (16));
    COORD->setInitializer (llvm::ConstantAggregateZero::get (CoordTy));

    //@calculate.first = internal unnamed_addr global i32 0, align 4
    llvm::Type* CalcFirstTy = builder.getInt32Ty ();
    module->getOrInsertGlobal ("calculate.first" , CalcFirstTy);
    CALCULATE_FIRST = module->getNamedGlobal ("calculate.first");
    CALCULATE_FIRST->setLinkage (llvm::GlobalValue::CommonLinkage);
    CALCULATE_FIRST->setAlignment (llvm::MaybeAlign (4));
    CALCULATE_FIRST->setInitializer (llvm::ConstantInt::get (builder.getInt32Ty () , 0));

    //define dso_local void @init_triangle() local_unnamed_addr #0 {
    llvm::FunctionType* funcType = llvm::FunctionType::get (
        builder.getVoidTy () , llvm::ArrayRef<llvm::Type*> ()
    ,
        false);

    //; Function Attrs: nounwind sspstrong uwtable
        //define dso_local void @init_triangle() local_unnamed_addr #0 {
    llvm::Function* mainFunc = llvm::Function::Create (funcType , llvm::Function::ExternalLinkage , "init_triangle" , module);

    //0:                                                ; preds = %1, %0
    llvm::BasicBlock* block0 = llvm::BasicBlock::Create (context , "" , mainFunc);
    builder.SetInsertPoint (block0);
    llvm::BasicBlock* block1 = llvm::BasicBlock::Create (context , "" , mainFunc);
    llvm::BasicBlock* block12 = llvm::BasicBlock::Create (context , "" , mainFunc);
    llvm::BasicBlock* block25 = llvm::BasicBlock::Create (context , "" , mainFunc);
    llvm::BasicBlock* block28 = llvm::BasicBlock::Create (context , "" , mainFunc);
    llvm::BasicBlock* block29 = llvm::BasicBlock::Create (context , "" , mainFunc);
    llvm::BasicBlock* block32 = llvm::BasicBlock::Create (context , "" , mainFunc);


    //  call void @llvm.memset.p0i8.i64(i8* noundef nonnull align 16 dereferenceable(320000) bitcast ([400 x [200 x i32]]* @data to i8*), i8 0, i64 320000, i1 false)
    llvm::Value* TmpBitcast = builder.CreateBitCast (DATA , builder.getInt8PtrTy ());
    llvm::FunctionType* llvmMemsetTy = llvm::FunctionType::get (
        builder.getVoidTy () ,
        llvm::ArrayRef<llvm::Type*>{
            llvm::PointerType::get (builder.getInt8Ty () , 0) , builder.getInt8Ty () ,
            builder.getInt64Ty () , builder.getInt1Ty ()} ,
        false);
    llvm::FunctionCallee llvmMemsetCall =
        module->getOrInsertFunction ("llvm.memset.p0i8.i64" , llvmMemsetTy);
    builder.CreateCall (llvmMemsetCall , llvm::ArrayRef<llvm::Value*>{
        TmpBitcast , getConst (8 , 0) ,
            getConst (64 , 320000) , getConst (1 , 0)});

    //  br label %1
    builder.CreateBr (block1);

    // 1: 
    builder.SetInsertPoint (block1);

    //  %2 = phi i64 [ 0, %0 ], [ %10, %1 ]
    llvm::PHINode* var2 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var2->addIncoming (llvm::ConstantInt::get (builder.getInt64Ty () , 0) , block0);

    //  %3 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %2, i64 %2
    llvm::Value* var3TyIn = llvm::ConstantInt::get (builder.getInt64Ty () , 0);
    llvm::Value* var3 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{var3TyIn , var2, var2});
    
    //  store i32 400, i32* %3, align 8
    builder.CreateAlignedStore (llvm::ConstantInt::get (builder.getInt32Ty () , 400) , var3 , llvm::MaybeAlign (8));

     //  %4 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %2
    llvm::Value* var4 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var2});

    //  %5 = trunc i64 %2 to i32
    llvm::Value* var5 = builder.CreateTrunc (var2 , builder.getInt32Ty ());
    
    //  store i32 %5, i32* %4, align 8
    builder.CreateAlignedStore (var5 , var4 , llvm::MaybeAlign (8));
    
    //  %6 = or i64 %2, 1
    llvm::Value* var6 = builder.CreateOr (var2 , getConst (64 , 1));

    //  %7 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %6, i64 %6
    llvm::Value* var7 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var6, var6});

    //  store i32 400, i32* %7, align 4
    builder.CreateAlignedStore (getConst (32 , 400) , var7 , llvm::MaybeAlign (4));

    //  %8 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %6
    llvm::Value* var8 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var6});

    //  %9 = trunc i64 %6 to i32
    llvm::Value* var9 = builder.CreateTrunc (var6 , builder.getInt32Ty ());

    //  store i32 %9, i32* %8, align 4
    builder.CreateAlignedStore (var9 , var8 , llvm::MaybeAlign (4));

    //  %10 = add nuw nsw i64 %2, 2
    llvm::Value* var10 = builder.CreateAdd (var2 , getConst (64 , 2));
    var2->addIncoming (var10 , block1);

    //  %11 = icmp eq i64 %10, 200
    llvm::Value* var11 = builder.CreateICmpEQ (
        var10 , llvm::ConstantInt::get (builder.getInt64Ty () , 200));

    //  br i1 %11, label %12, label %1
    builder.CreateCondBr (var11 , block12 , block1);


    //12:                                               ; preds = %1, %12
    builder.SetInsertPoint (block12);

    //  %13 = phi i64 [ %23, %12 ], [ 200, %1 ]
    llvm::PHINode* var13 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var13->addIncoming (llvm::ConstantInt::get (builder.getInt64Ty () , 200) , block1);

    //  %14 = sub nuw nsw i64 400, %13
    llvm::Value* var14 = builder.CreateSub (getConst (64 , 400) , var13);

    //  %15 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %13, i64 %14
    llvm::Value* var15 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var13, var14});

    //  store i32 400, i32* %15, align 8
    builder.CreateAlignedStore (getConst (32 , 400) , var15 , llvm::MaybeAlign (8));

    //  %16 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %13
    llvm::Value* var16 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var13});

    //  %17 = trunc i64 %14 to i32
    llvm::Value* var17 = builder.CreateTrunc (var14 , builder.getInt32Ty ());

    //  store i32 %17, i32* %16, align 8
    builder.CreateAlignedStore (var17 , var16 , llvm::MaybeAlign (8));

    //  %18 = or i64 %13, 1
    llvm::Value* var18 = builder.CreateOr (var13 , getConst (64 , 1));

    //  %19 = sub nsw i64 399, %13
    llvm::Value* var19 = builder.CreateSub (getConst (64 , 399) , var13);

    //  %20 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %18, i64 %19
    llvm::Value* var20 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var18, var19});

    //  store i32 400, i32* %20, align 4
    builder.CreateAlignedStore (getConst (32 , 400) , var20 , llvm::MaybeAlign (4));

    //  %21 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %18
    llvm::Value* var21 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var18});

    //  %22 = trunc i64 %19 to i32
    llvm::Value* var22 = builder.CreateTrunc (var19 , builder.getInt32Ty ());

    //  store i32 %22, i32* %21, align 4
    builder.CreateAlignedStore (var22 , var21 , llvm::MaybeAlign (4));

    //  %23 = add nuw nsw i64 %13, 2
    llvm::Value* var23 = builder.CreateAdd (var13 , getConst (64 , 2));
    var13->addIncoming (var23 , block12);

    //  %24 = icmp eq i64 %23, 400
    llvm::Value* var24 = builder.CreateICmpEQ (var23 , getConst (64 , 400));

    //  br i1 %24, label %25, label %12
    builder.CreateCondBr (var24 , block25 , block12);


    //25:                                               ; preds = %12, %29
    builder.SetInsertPoint (block25);

    //  %26 = phi i64 [ %30, %29 ], [ 0, %12 ]
    llvm::PHINode* var26 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var26->addIncoming (llvm::ConstantInt::get (builder.getInt64Ty () , 0) , block12);

    //  %27 = trunc i64 %26 to i32
    llvm::Value* var27 = builder.CreateTrunc (var26 , builder.getInt32Ty ());

    //  br label %32
    builder.CreateBr (block32);


    //28:                                               ; preds = %29
    builder.SetInsertPoint (block28);

    //  ret void
    builder.CreateRetVoid ();
    

    //29:                                               ; preds = %32
    builder.SetInsertPoint (block29);

    //  %30 = add nuw nsw i64 %26, 1
    llvm::Value* var30 = builder.CreateAdd (var26 , getConst (64 , 1));
    var26->addIncoming (var30 , block29);

    //  %31 = icmp eq i64 %30, 400
    llvm::Value* var31 = builder.CreateICmpEQ (var30 , getConst (64 , 400));

    //  br i1 %31, label %28, label %25
    builder.CreateCondBr (var31 , block28 , block25);


    //32:                                               ; preds = %25, %32
    builder.SetInsertPoint (block32);

    //  %33 = phi i64 [ 0, %25 ], [ %37, %32 ]
    llvm::PHINode* var33 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var33->addIncoming (llvm::ConstantInt::get (builder.getInt64Ty () , 0) , block25);

    //  %34 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %26, i64 %33
    llvm::Value* var34 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var26, var33});

    //  %35 = load i32, i32* %34, align 4
    llvm::Value* var35 = builder.CreateLoad (builder.getInt32Ty(), var34);

    //  %36 = trunc i64 %33 to i32
    llvm::Value* var36 = builder.CreateTrunc (var33 , builder.getInt32Ty ());

    //  tail call void @put_pixel(i32 noundef %27, i32 noundef %36, i32 noundef %35) #4
    llvm::FunctionType* PutPixelTy = llvm::FunctionType::get (
        builder.getVoidTy () ,
        llvm::ArrayRef<llvm::Type*>{
    builder.getInt32Ty() , builder.getInt32Ty () , builder.getInt32Ty ()} ,
        false);
    llvm::FunctionCallee PutPixelCall =
        module->getOrInsertFunction ("put_pixel" , PutPixelTy);
    builder.CreateCall (PutPixelCall , llvm::ArrayRef<llvm::Value*>{
        var27 , var36 , var35 });

    //  %37 = add nuw nsw i64 %33, 1
    llvm::Value* var37 = builder.CreateAdd (var33 , getConst (64 , 1));
    var33->addIncoming ( var37 , block32);

    //  %38 = icmp eq i64 %37, 200
    llvm::Value* var38 = builder.CreateICmpEQ (var37 , getConst (64 , 200));

    //  br i1 %38, label %29, label %32
    builder.CreateCondBr (var38 , block29 , block32);

    
    //; Function Attrs: nounwind sspstrong uwtable
    //define dso_local void @calculate() local_unnamed_addr #0 {
    llvm::Function* Calculate = llvm::Function::Create (funcType , llvm::Function::ExternalLinkage , "calculate" , module);
    
    llvm::BasicBlock* block_0 = llvm::BasicBlock::Create (context , "" , Calculate);
    builder.SetInsertPoint (block_0);
    llvm::BasicBlock* block_19 = llvm::BasicBlock::Create (context , "" , Calculate);
    llvm::BasicBlock* block_20 = llvm::BasicBlock::Create (context , "" , Calculate);
    llvm::BasicBlock* block_44 = llvm::BasicBlock::Create (context , "" , Calculate);
    llvm::BasicBlock* block_47 = llvm::BasicBlock::Create (context , "" , Calculate);
    llvm::BasicBlock* block_48 = llvm::BasicBlock::Create (context , "" , Calculate);
    llvm::BasicBlock* block_51 = llvm::BasicBlock::Create (context , "" , Calculate);

    //  %1 = load i32, i32* @calculate.first, align 4
    llvm::Value* var_1 = builder.CreateLoad (builder.getInt32Ty(), CALCULATE_FIRST);

    //  %2 = add nsw i32 %1, 1
    llvm::Value* var_2 = builder.CreateAdd (var_1 , getConst (32 , 1));

    //  %3 = icmp eq i32 %2, 400
    llvm::Value* var_3 = builder.CreateICmpEQ (var_2 , getConst (32 , 400));

    //  %4 = select i1 %3, i32 0, i32 %2
    llvm::Value* var_4 = builder.CreateSelect (var_3 , getConst (32 , 0), var_2);

    //  store i32 %4, i32* @calculate.first, align 4
    builder.CreateAlignedStore (var_4 , CALCULATE_FIRST , llvm::MaybeAlign (4));

    //  %5 = sdiv i32 %4, 200
    llvm::Value* var_5 = builder.CreateSDiv (var_4 , getConst (32 , 200));

    //  %6 = mul i32 %4, -2
    llvm::Value* var_6 = builder.CreateMul (var_4 , getConst (32 , -2));

    //  %7 = add i32 %6, 399
    llvm::Value* var_7 = builder.CreateAdd (var_6 , getConst (32 , 399));

    //  %8 = mul nsw i32 %7, %5
    llvm::Value* var_8 = builder.CreateMul (var_7 , var_5);

    //  %9 = add nsw i32 %8, %4
    llvm::Value* var_9 = builder.CreateAdd (var_8 , var_4);

    //  %10 = sext i32 %9 to i64
    llvm::Value* var_10 = builder.CreateSExt (var_9 , builder.getInt64Ty ());

    //  %11 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %10
    llvm::Value* var_11 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 0), var_10});

    //  store i32 400, i32* %11, align 4
    builder.CreateAlignedStore (getConst (32 , 400) , var_11 , llvm::MaybeAlign (4));

    //  %12 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 0), align 16
    llvm::Value* tmp_1 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 0) });
    llvm::Value* var_12 = builder.CreateLoad (builder.getInt32Ty(), tmp_1);

    //  %13 = sext i32 %12 to i64
    llvm::Value* var_13 = builder.CreateSExt (var_12 , builder.getInt64Ty ());

    //  %14 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %13
    llvm::Value* var_14 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 0), var_13});

    //  store i32 0, i32* %14, align 4
    builder.CreateAlignedStore (getConst (32 , 0) , var_14 , llvm::MaybeAlign (4));

    //  %15 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4
    llvm::Value* tmp_2 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 399) });
    llvm::Value* var_15 = builder.CreateLoad (builder.getInt32Ty(), tmp_2);

    //  %16 = sext i32 %15 to i64
    llvm::Value* var_16 = builder.CreateSExt (var_15 , builder.getInt64Ty ());

    //  %17 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 0, i64 %16
    llvm::Value* var_17 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 0), var_16});
    
    //  store i32 0, i32* %17, align 4
    builder.CreateAlignedStore (getConst (32 , 0) , var_17 , llvm::MaybeAlign (4));

    //  %18 = load i32, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 -1, i64 399), align 4
    llvm::Value* tmp_3 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , -1) , getConst (64 , 399) });
    llvm::Value* var_18 = builder.CreateLoad (builder.getInt32Ty(), tmp_3);

    //  br label %20
    builder.CreateBr (block_20);


    //19:                                               ; preds = %20
    builder.SetInsertPoint (block_19);

    //  store i32 %40, i32* getelementptr inbounds ([400 x i32], [400 x i32]* @coord, i64 0, i64 399), align 4
    llvm::Value* tmp_4 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , getConst (64 , 399) });
        
    //  br label %44
    builder.CreateBr (block_44);


    //20:                                               ; preds = %0, %20
    builder.SetInsertPoint (block_20);

    //  %21 = phi i32 [ %18, %0 ], [ %23, %20 ]
    llvm::PHINode* var_21 = builder.CreatePHI (builder.getInt32Ty () , 2);
    var_21->addIncoming ( var_18 , block_0);

    //  %22 = phi i64 [ 0, %0 ], [ %24, %20 ]
    llvm::PHINode* var_22 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var_22->addIncoming (llvm::ConstantInt::get (builder.getInt64Ty () , 0) , block_0);
    
    //  %23 = phi i32 [ %9, %0 ], [ %40, %20 ]
    llvm::PHINode* var_23 = builder.CreatePHI (builder.getInt32Ty () , 2);
    var_23->addIncoming ( var_9 , block_0);
    var_21->addIncoming ( var_23 , block_20);

    //  %24 = add nuw nsw i64 %22, 1
    llvm::Value* var_24 = builder.CreateAdd (var_22 , getConst (64 , 1));
    var_22->addIncoming ( var_24 , block_20);
    
    //  %25 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %24
    llvm::Value* var_25 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_24});
    
    //  %26 = load i32, i32* %25, align 4
    llvm::Value* var_26 = builder.CreateLoad (builder.getInt32Ty(), var_25);

    //  %27 = sext i32 %26 to i64
    llvm::Value* var_27 = builder.CreateSExt (var_26 , builder.getInt64Ty ());
    
    //  %28 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %27
    llvm::Value* var_28 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_22, var_27});
    
    //  store i32 0, i32* %28, align 4
    builder.CreateAlignedStore (getConst (32 , 0) , var_28 , llvm::MaybeAlign (4));
    
    //  %29 = sext i32 %21 to i64
    llvm::Value* var_29 = builder.CreateSExt (var_21 , builder.getInt64Ty ());

    //  %30 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %29
    llvm::Value* var_30 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_22, var_29});

    //  store i32 0, i32* %30, align 4
    builder.CreateAlignedStore (getConst (32 , 0) , var_30 , llvm::MaybeAlign (4));

    //  %31 = add nuw nsw i64 %22, 2
    llvm::Value* var_31 = builder.CreateAdd (var_22 , getConst (64 , 2));

    //  %32 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %31
    llvm::Value* var_32 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_31});
    
    //  %33 = load i32, i32* %32, align 4
    llvm::Value* var_33 = builder.CreateLoad (builder.getInt32Ty(), var_32);

    //  %34 = sext i32 %33 to i64
    llvm::Value* var_34 = builder.CreateSExt (var_33 , builder.getInt64Ty ());

    //  %35 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %34
    llvm::Value* var_35 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_22, var_34});
    
    //  store i32 0, i32* %35, align 4
    builder.CreateAlignedStore (getConst (32 , 0) , var_35 , llvm::MaybeAlign (4));

    //  %36 = tail call i32 @rand() #4
    llvm::FunctionType* RandTy = llvm::FunctionType::get (
        builder.getInt32Ty () ,
        false);
    llvm::FunctionCallee RandCall =
        module->getOrInsertFunction ("rand" , RandTy);
    llvm::Value* var_36 = builder.CreateCall (RandCall);

    //  %37 = srem i32 %36, 3
    llvm::Value* var_37 = builder.CreateSRem ( var_36 , getConst (32 , 3) );

    //  %38 = add nsw i32 %37, 1
    llvm::Value* var_38 = builder.CreateAdd (var_37 , getConst (32 , 1));

    //  %39 = getelementptr inbounds [400 x i32], [400 x i32]* @coord, i64 0, i64 %22
    llvm::Value* var_39 = builder.CreateGEP (
        CoordTy ,
        COORD ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_22});

    //  %40 = load i32, i32* %39, align 4
    llvm::Value* var_40 = builder.CreateLoad (builder.getInt32Ty(), var_39);
    var_23->addIncoming ( var_40 , block_20);
    builder.CreateAlignedStore ( var_40 , tmp_4 , llvm::MaybeAlign (4));

    //  %41 = sext i32 %40 to i64
    llvm::Value* var_41 = builder.CreateSExt (var_40 , builder.getInt64Ty ());

    //  %42 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %22, i64 %41
    llvm::Value* var_42 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_22, var_41});
    
    //  store i32 %38, i32* %42, align 4
    builder.CreateAlignedStore ( var_38 , var_42 , llvm::MaybeAlign (4));

    //  store i32 %23, i32* %39, align 4
    builder.CreateAlignedStore ( var_23 , var_39 , llvm::MaybeAlign (4));

    //  %43 = icmp eq i64 %24, 399
    llvm::Value* var_43 = builder.CreateICmpEQ (var_24 , getConst (64 , 399));
    
    //  br i1 %43, label %19, label %20
    builder.CreateCondBr (var_43 , block_19 , block_20);


    //44:                                               ; preds = %19, %48
    builder.SetInsertPoint (block_44);

    //  %45 = phi i64 [ 0, %19 ], [ %49, %48 ]
    llvm::PHINode* var_45 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var_45->addIncoming ( getConst (64 , 0) , block_19);
    
    //  %46 = trunc i64 %45 to i32
    llvm::Value* var_46 = builder.CreateTrunc (var_45 , builder.getInt32Ty ());

    //  br label %51
    builder.CreateBr (block_51);


    //47:                                               ; preds = %48
    builder.SetInsertPoint (block_47);

    //  ret void
    builder.CreateRetVoid ();


    //48:                                               ; preds = %51
    builder.SetInsertPoint (block_48);

    //  %49 = add nuw nsw i64 %45, 1
    llvm::Value* var_49 = builder.CreateAdd (var_45 , getConst (64 , 1));
    var_45->addIncoming ( var_49 , block_48);

    //  %50 = icmp eq i64 %49, 400
    llvm::Value* var_50 = builder.CreateICmpEQ (var_49 , getConst (64 , 400));

    //  br i1 %50, label %47, label %44
    builder.CreateCondBr (var_50 , block_47 , block_44);


    //51:                                               ; preds = %44, %51
    builder.SetInsertPoint (block_51);

    //  %52 = phi i64 [ 0, %44 ], [ %56, %51 ]
    llvm::PHINode* var_52 = builder.CreatePHI (builder.getInt64Ty () , 2);
    var_52->addIncoming ( getConst (64 , 0) , block_44);
    
    //  %53 = getelementptr inbounds [400 x [200 x i32]], [400 x [200 x i32]]* @data, i64 0, i64 %45, i64 %52
    llvm::Value* var_53 = builder.CreateGEP (
        DataTy ,
        DATA ,
        llvm::ArrayRef<llvm::Value*>{getConst (64 , 0) , var_45, var_52});

    //  %54 = load i32, i32* %53, align 4
    llvm::Value* var_54 = builder.CreateLoad (builder.getInt32Ty(), var_53);
    
    //  %55 = trunc i64 %52 to i32
    llvm::Value* var_55 = builder.CreateTrunc (var_52 , builder.getInt32Ty ());
    
    //  tail call void @put_pixel(i32 noundef %46, i32 noundef %55, i32 noundef %54) #4
    builder.CreateCall (PutPixelCall , llvm::ArrayRef<llvm::Value*>{
        var_46 , var_55 , var_54 });

    //  %56 = add nuw nsw i64 %52, 1
    llvm::Value* var_56 = builder.CreateAdd (var_52 , getConst (64 , 1));
    var_52->addIncoming ( var_56 , block_51);

    //  %57 = icmp eq i64 %56, 200
    llvm::Value* var_57 = builder.CreateICmpEQ (var_56 , getConst (64 , 200));

    //  br i1 %57, label %48, label %51
    builder.CreateCondBr (var_57 , block_48 , block_51);



    //attributes #0 = { nounwind sspstrong uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
    
    //attributes #1 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

    //attributes #2 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

    //attributes #3 = { argmemonly nofree nounwind willreturn writeonly }

    //attributes #4 = { nounwind }


    //!llvm.module.flags = !{!0, !1, !2, !3}

    //!llvm.ident = !{!4}


    //!0 = !{i32 1, !"wchar_size", i32 4}

    //!1 = !{i32 7, !"PIC Level", i32 2}

    //!2 = !{i32 7, !"PIE Level", i32 2}

    //!3 = !{i32 7, !"uwtable", i32 1}
    
    //!4 = !{!"clang version 14.0.6"}

    //!5 = !{!6, !6, i64 0}

    //!6 = !{!"int", !7, i64 0}

    //!7 = !{!"omnipotent char", !8, i64 0}
    
    //!8 = !{!"Simple C/C++ TBAA"}
    
    //!9 = distinct !{!9, !10}
    
    //!10 = !{!"llvm.loop.mustprogress"}
    
    //!11 = distinct !{!11, !10}
    
    //!12 = distinct !{!12, !10}

    //!13 = distinct !{!13, !10}

    //!14 = distinct !{!14, !10}

    //!15 = distinct !{!15, !10}
    
    //!16 = distinct !{!16, !10}

    // Dump LLVM IR
    std::string s;
    llvm::raw_string_ostream os (s);
    module->print (os , nullptr);
    os.flush ();
    std::ofstream file;
    file.open ("/home/margo/Floating triangles/llvm_giver.ll");
    file << s;
    file.close ();

    return 0;
}


