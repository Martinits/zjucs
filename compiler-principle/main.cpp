#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "irbuilder.h"
#include "utils.h"
#include "parser.hpp"

// #define MYDEBUG

using namespace std;

extern int yyparse();
extern Program *prog;

const char* opts_str=":vo:lsbar:d:nhmt";

//settings
SETTING settings={
    .input_file_name="",
    .output_file_name_noext="a",
    .verbose=false,
    .emit_ll=false,
    .emit_tree=false,
    .emit_asm=false,
    .emit_obj=false,
    .emit_exe=true,
    .crt_lib_path="/lib/x86_64-linux-gnu/",
    .dl_path="/lib64/ld-linux-x86-64.so.2"
};

void help(bool isfull = false){
    cout << endl;
    if(isfull){
        cout << "Manual for spl compiler - designed for Ubuntu 64bit, especially Ubuntu 2004" << endl << endl
             << "Description: A simple compiler for \"Simple Pascal Language\"" << endl << endl
             << "Options:" << endl
             << "         NOTE: Option syntax follows GNU conventions," << endl
             << "               see https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html for details ." << endl << endl
             << "         -a    emit all intermedia files, i.e. tree visualization file, llvmIR file(.ll), asm file(.s), and object file(.o) ." << endl
             << "               output file name will be like \"<exe name>.<ll|s|o>\" ." << endl
             << "               by default, this compiler will ONLY emit executable-elf-file(hereinafter referred to as \033[1mexe\033[0m) ." << endl
             << "               this option will cover -t, -l, -b, and -s, see Examples for details ." << endl << endl
             << "         -b    emit object file(.o) ." << endl << endl
             << "         -d    specify the path of dynamic linker that output exe will need during run time ." << endl
             << "               by default it is /lib64/ld-linux-x86-64.so.2 ." << endl << endl
             << "         -h    show short usage ." << endl << endl
             << "         -l    emit llvmIR file(.ll) ." << endl << endl
             << "         -m    show manual (what you are reading right now) ." << endl << endl
             << "         -n    do not emit exe ." << endl << endl
             << "         -o    specify output file, default is \"a\" ." << endl << endl
             << "         -r    specify the path of c-runtime-library, default is /lib/x86_64-linux-gnu/ ." << endl << endl
             << "         -s    emit asm file(.s) ." << endl << endl
             << "         -t    emit tree visualization file ." << endl << endl
             << "         -v    enable verbose, by default it is closed ." << endl << endl
             << "Examples:" << endl
             << "  \033[1mspl input.spl\033[0m" << endl
             << "               input \"input.spl\", output \"a\" as exe" << endl << endl
             << "  \033[1mspl input.spl -o opt\033[0m" << endl
             << "               input \"input.spl\", output \"opt\" as exe" << endl << endl
             << "  \033[1mspl input.spl -o opt -l\033[0m" << endl
             << "               input \"input.spl\", output \"opt\" as exe, \"opt.ll\" as llvmIR" << endl << endl
             << "  \033[1mspl input.spl -o opt -lt\033[0m" << endl
             << "               input \"input.spl\", output \"opt\" as exe, \"opt.ll\" as llvmIR, \"d3Visualization/tree.json\" as tree visualization file" << endl << endl
             << "  \033[1mspl input.spl -o opt -ls\033[0m" << endl
             << "               input \"input.spl\", output \"opt\" as exe, \"opt.ll\" as llvmIR, \"opt.s\" as asm file" << endl << endl
             << "  \033[1mspl input.spl -o opt -a\033[0m" << endl
             << "               input \"input.spl\", output \"opt\" as exe, \"opt.ll\" as llvmIR, \"opt.s\" as asm file, \"opt.o\" as object file" << endl << endl
             << "  \033[1mspl input.spl -o opt -ln\033[0m" << endl
             << "               input \"input.spl\", output \"opt.ll\" as llvmIR" << endl << endl
             << "  \033[1mspl input.spl -o opt -an\033[0m" << endl
             << "               input \"input.spl\", output \"opt.ll\" as llvmIR, \"opt.s\" as asm file, \"opt.o\" as object file" << endl << endl;
    }else{
        cout << "Usage: spl <input_file> [-vtlsban]" << endl
             << "           [-o output_file]" << endl
             << "           [-r c_runtime_library_path]" << endl
             << "           [-d dynamic_linker_path]" << endl;
    }
    cout << endl;
}

void arg_error_exit(string msg, int exit_code = 1){
    cerr << "[\033[33mARGUMENT ERROR\033[0m] " << msg << endl;
    cerr << "Use \"-h\" for short usage and \"-m\" for manual of details" << endl;
    exit(exit_code);
}

int param_process(int argc, char**argv){
    map<char, string> opts;
    vector<string> non_opts;
    int c;
    opterr=0;
    while((c=getopt(argc, argv, opts_str)) != -1){
        switch (c){
            case '?': {
                string tmp="invalid option: \'";
                tmp+=(char)optopt;
                tmp+="\'";
                arg_error_exit(tmp);
                return 1;
            }
            case ':': {
                string tmp="option \'";
                tmp+=(char)optopt;
                tmp+="\' needs exactly one argument.";
                arg_error_exit(tmp);
                return 1;
            }
            default:
                if(opts.count(c)<=0){
                    opts[c]=(optarg ? string(optarg) : "");
                }
                break;
        }
    }
    for(int i=optind;i<argc;i++) non_opts.push_back(string(argv[i]));

    //man
    if(opts.count('m')==1){
        help(true);
        exit(0);
    }
    //help
    if(opts.count('h')==1){
        help();
        exit(0);
    }
    //input file
    if(non_opts.size()<1) arg_error_exit("no input files.");
    else if(non_opts.size()>1){
        string tmp="multiple input files: ";
        for(auto &p : non_opts) tmp+=p+" ";
        arg_error_exit(tmp);
    }else settings.input_file_name=non_opts[0];
    //output file
    if(opts.count('o')==1){
        settings.output_file_name_noext=opts['o'];
    }
    //verbose
    if(opts.count('v')==1){
        settings.verbose=true;
    }
    //emits
    if(opts.count('n')==1){
        settings.emit_exe=false;
    }
    if(opts.count('a')==1){
        settings.emit_ll=true;
        settings.emit_tree=true;
        settings.emit_asm=true;
        settings.emit_obj=true;
    }else{
        if(opts.count('l')==1){
            settings.emit_ll=true;
        }
        if(opts.count('t')==1){
            settings.emit_tree=true;
        }
        if(opts.count('s')==1){
            settings.emit_asm=true;
        }
        if(opts.count('b')==1){
            settings.emit_obj=true;
        }
    }
    //crtlibpath
    if(opts.count('r')==1){
        settings.crt_lib_path=opts['r'];
    }
    //dlpath
    if(opts.count('d')==1){
        settings.dl_path=opts['d'];
    }
    return 0;
}

int tree_visualize(){
    string json=prog->getJson();
    ofstream os("d3Visualization/tree.json", ios::out);
    if(!os.is_open()) error_exit("cannot open json file d3Visualization/tree.json for output");
    os << json << endl;
    os.close();

    fstream jsfile("d3Visualization/index.js", ios::in);
    if(!jsfile.is_open()) error_exit("cannot open js file d3Visualization/index.js", true);
    stringstream ss;
    ss << jsfile.rdbuf();
    jsfile.close();
    string js(ss.str());
    size_t pos=js.find("var dataset")+11;
    string tmp=js.substr(0, pos);
    while(js[pos]!='\n') pos++;
    // js.insert(js.find("var dataset")+11, " = "+json);
    js=tmp+" = "+json+js.substr(pos);
    // cout << js;
    jsfile.open("d3Visualization/index.js", ios::out);
    if(!jsfile.is_open()) error_exit("cannot open js file d3Visualization/index.js", true);
    jsfile << js;
    jsfile.close();
    return 0;
}

#ifndef MYDEBUG
extern int lldlink(int argc, const char *argv[]);
extern int llccompiler(int argc, char *argv[]);
int compile_link(){
    string arg1=settings.output_file_name_noext+".ll";
    string arg4=settings.output_file_name_noext+".o";
    const char *llcargv[]={
        "llvmstaticcompiler",
        "--filetype=obj",
        arg1.c_str(),
        "-o",
        arg4.c_str(),
        NULL
    };
    int llcargc=0;
    const char **tmp=llcargv;
    while(*tmp++!=NULL) llcargc++;
    if(settings.emit_exe || settings.emit_obj){
        verbose("Object file builing...");
        int llcret;
        pid_t pid=fork();
        if(pid==0){
            exit(llccompiler(llcargc, const_cast<char**>(llcargv)));
        }else if(pid>0){
            waitpid(pid, &llcret, 0);
        }else error_exit("compiler failed during creating sub process.");
        if(llcret!=0) return llcret;
        verbose("Object file built.");
    }
    if(settings.emit_asm){
        verbose("Asm file building...");
        int llcret;
        pid_t pid=fork();
        if(pid==0){
            llcargv[1]="--filetype=asm";
            arg4=settings.output_file_name_noext+".s";
            llcargv[4]=arg4.c_str();
            exit(llccompiler(llcargc, const_cast<char**>(llcargv)));
        }else if(pid>0){
            waitpid(pid, &llcret, 0);
        }else error_exit("compiler failed during creating sub process.");
        if(llcret!=0) return llcret;
        verbose("Asm file built.");
    }

    arg4=settings.output_file_name_noext+".o";
    const char *lldargv[]={
        "llvmlinker",
        "lib/rt/crt1.o",
        "lib/rt/crti.o",
        "lib/rt/libspl.o",
        arg4.c_str(),
        "lib/rt/crtn.o",
        "-o",
        settings.output_file_name_noext.c_str(),
        "-L",
        settings.crt_lib_path.c_str(),
        "-lc",
        "-lm",
        "-dynamic-linker",
        settings.dl_path.c_str(),
        NULL
    };
    int lldargc=0;
    tmp=lldargv;
    while(*tmp++!=NULL) lldargc++;
    if(settings.emit_exe){
        verbose("Linking...");
        int lldret=lldlink(lldargc, lldargv);
        if(lldret!=0) return lldret;
        verbose("Link done.");
    }
    verbose("Removing useless intermedia files...");
    if(!settings.emit_obj){
        string tmp=settings.output_file_name_noext+".o";
        remove(tmp.c_str());
    }
    if(!settings.emit_ll){
        string tmp=settings.output_file_name_noext+".ll";
        remove(tmp.c_str());
    }
    verbose("Done.");
    return 0;
}
#endif

int main(int argc, char *argv[]){
    //init
    //param process
    int ret=param_process(argc, argv);
    if(ret!=0) return ret;

    //redirect input to file
    if(freopen(settings.input_file_name.c_str(), "r", stdin)==NULL){
        error_exit("cannot open file "+settings.input_file_name);
    }

    //parse
    verbose("Parsing...");
    if(yyparse()!=0){
        error_exit("parser failed");
    }
    verbose("Parse done.");

    //ast visualize
    if(settings.emit_tree){
        int ret=tree_visualize();
        if(ret!=0) return ret;
    }
    
    //irbuild
    verbose("IR generating...");
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    irBuilder irbuilder;
    irbuilder.build(*prog, settings.output_file_name_noext+".ll");
    verbose("IR generation done.");

    //call static compiler llc and linker lld
#ifndef MYDEBUG
    return compile_link();
#else
    return 0;
#endif
}
