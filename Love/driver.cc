//------------------------------------------------------------------------------
//
// driver.cpp -- main entry point
//
//------------------------------------------------------------------------------

#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"

#include "parser.hpp"
#include <fstream>
#include <stack>

IScope *currentScope = new Scope(nullptr);
std::stack<llvm::Function *> stackFunction;

llvm::LLVMContext *Context;
llvm::IRBuilder<> *Builder;
llvm::Module *Module;

static int currentinlinePos = 0;
std::pair<std::string, std::string> ParseOptions(int argc, char *argv[]);

class Printer {
public:
  Printer() {
    // @.str = constant [4 x i8] c"%d\0A\00", align 1
    llvm::Type *PRINT_STRTy = llvm::ArrayType::get(Builder->getInt8Ty(), 4);
    Module->getOrInsertGlobal(".int_string", PRINT_STRTy);
    int_string = Module->getNamedGlobal(".int_string");
    int_string->setLinkage(llvm::GlobalValue::InternalLinkage);
    int_string->setAlignment(llvm::MaybeAlign(1));
    int_string->setInitializer(
        llvm::ConstantDataArray::getString(*Context, "%d\n", true));

    llvm::FunctionType *PrintfTy = llvm::FunctionType::get(
        Builder->getInt32Ty(), llvm::ArrayRef<llvm::Type *>{}, true);
    llvm::FunctionCallee PrintfTyCallee =
        Module->getOrInsertFunction("printf", PrintfTy);
    llvm::FunctionType *PrintTy = llvm::FunctionType::get(
        Builder->getVoidTy(), Builder->getInt32Ty(), false);

    int_print = llvm::Function::Create(PrintTy, llvm::Function::ExternalLinkage,
                                       "__print_int", Module);
    llvm::BasicBlock *PrintBB =
        llvm::BasicBlock::Create(*Context, "", int_print);
    Builder->SetInsertPoint(PrintBB);
    llvm::Value *PrintArg = static_cast<llvm::Value *>(int_print->arg_begin());
    Builder->CreateCall(PrintfTyCallee,
                        llvm::ArrayRef<llvm::Value *>{int_string, PrintArg});
    Builder->CreateRetVoid();
  }

private:
  llvm::GlobalVariable *int_string = nullptr;
  llvm::Function *int_print;
};

int main(int argc, char *argv[]) {
  auto [fileName, outName] = ParseOptions(argc, argv);
  if (fileName.empty())
    return 1;

  FILE *f = fopen(fileName.data(), "r");
  if (!f) {
    perror("Cannot open file");
    return 1;
  }
  yyin = f;

  Context = new llvm::LLVMContext;
  Module = new llvm::Module("love.module", *Context);
  Builder = new llvm::IRBuilder<>(*Context);

  Printer();

  // single __pcl_start function for void module

  yyparse();
  
  std::cout << "Saving module to: " << outName << "\n";

  std::error_code EC;
  llvm::raw_fd_ostream outfile{outName, EC};
  if (EC) {
    llvm::errs() << EC.message().c_str() << "\n";
  }

  Module->print(outfile, nullptr);
  outfile.close();

  if (outfile.has_error()) {
    llvm::errs() << "Error printing to file: " << outfile.error().message()
                 << "\n";
  }

  fclose(f);

  delete Builder;
  delete Context;
  delete currentScope;
  return 0;
}

void PrintError(char const *errmsg) {
  std::cerr << "Error: " << errmsg << " - Line " << yylineno << ", Column "
            << currentinlinePos << std::endl;
  exit(1);
}

void BeginToken(char *t, int *yyinlinePos) {
  yylloc.first_line = yylineno;
  yylloc.first_column = *yyinlinePos;
  yylloc.last_line = yylineno;
  *yyinlinePos += strlen(t);
  yylloc.last_column = *yyinlinePos;

  currentinlinePos = *yyinlinePos;
}

namespace po = boost::program_options;

std::pair<std::string, std::string> ParseOptions(int argc, char *argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()("help", "Usage: ./calculator <file>.love");
  desc.add_options()("file,f", po::value<std::string>(), "File to compile");
  desc.add_options()("output,o", po::value<std::string>(),
                     "Where return binary");

  po::variables_map args;
  po::store(po::command_line_parser(argc, argv).options(desc).run(), args);
  po::notify(args);

  std::pair<std::string, std::string> out;
  if (!args.count("file")) {
    std::cout << desc;
    return out;
  }

  out.first = args["file"].as<std::string>();
  if (!args.count("output"))
    out.second = out.first + ".ll";
  else
    out.second = args["output"].as<std::string>();

  return out;
}