#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include "exp.tab.h"

#include "IR.h"
#include "IRPrinter.h"
#include "type.h"
#include "json/json.h"


using namespace std;
using namespace Boost::Internal;

const vector<string> cases({"example", "case1", "case2", "case3", "case4", "case5", "case6", "case7", "case8", "case9", "case10"});

extern vector<Stmt> result;
extern map<string, Expr> varMap;
extern Type var_type, data_type_i, data_type_f;
extern void scan_string(const char *s);
extern void delete_buffer();

int main(){
    /* 
    yyparse();
    cout << " ==================================================================== " << endl;
    Stmt body = StmtList::make(result);
    cout << IRPrinter().print(body) << endl;
*/
    for (const string &filename : cases){
        try{
        result.clear();

        string inpath = "./cases/" + filename + ".json";
        
        Json::Value root;
        Json::Reader reader;

        ifstream inf(inpath);
        if (!inf) continue; 

        reader.parse(inf, root);

        string name = root["name"].asString();
        string outpath = "./kernels/" + name + ".cc";

        string data_type = root["data_type"].asString();
        string kernel = root["kernel"].asString();

        vector<string> in_args;
        int in_size = root["ins"].size();
        for (int i = 0; i < in_size; i++){
            in_args.push_back(root["ins"][i].asString());
        }
        set<string> ind_set(in_args.begin(), in_args.end());

        vector<string> out_args;
        int out_size = root["outs"].size();
        for (int i = 0; i < out_size; i++){
            string id = root["outs"][i].asString();
            if (ind_set.count(id) > 0) continue;
            out_args.push_back(id);
        }

        if (data_type == "float") var_type = data_type_f;
        else var_type = data_type_i;

        scan_string(kernel.c_str());
        yyparse();
        delete_buffer();

        //Stmt body = StmtList::make(result);
        vector<Expr> in_expr;
        for (const string &s : in_args){
            in_expr.push_back(varMap[s]);
        }

        vector<Expr> out_expr;
        for (const string &s : out_args){
            out_expr.push_back(varMap[s]);
        }

        Group proc = Kernel::make(name, in_expr, out_expr, result, KernelType::CPU);

        ofstream outf(outpath);

        IRPrinter printer;
        outf << "#include \"../run.h\"\n\n";
        outf << printer.print(proc) << endl;
        }
        catch(...){}
    }

    return 0;
}
