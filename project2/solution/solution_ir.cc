#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include "exp.tab.h"

#include "IR.h"
#include "IRPrinter.h"
#include "IRMutator.h"
#include "type.h"
#include "json/json.h"


using namespace std;
using namespace Boost::Internal;

//const vector<string> cases({"case1", "case2", "case3", "case4", "case5", "case6", "case7", "case8", "case9", "case10"});
const vector<string> cases({"case1", "case2", "case3", "case4", "case5", "case6", "case7", "case8", "case9"});
const double eps = 1e-6;

extern vector<Stmt> result;
extern map<string, Expr> varMap;
extern Type var_type, data_type_i, data_type_f;
extern void scan_string(const char *s);
extern void delete_buffer();


set<string> in_set; // set of in_args in final code 

class DiffMutator: public IRMutator{
public:
Expr grad_from, grad_to;

Expr visit(Ref<const IntImm> op) override {
    return IntImm::make(data_type_i, 0);
}

Expr visit(Ref<const FloatImm> op) override {
    return FloatImm::make(data_type_f, 0.0);
}

Expr visit(Ref<const Var> op) override { // TODO: diff actions for diff indices. e.g. A[i, j] and A[i-1, j]
    //cout << "Var: " << op->name << endl;
	int val = ("d" + op->name == (grad_to.as<Var>())->name) ? 1 : 0; // dx/dx = 1, dy/dx = 0

	if (op->type() == data_type_i) return IntImm::make(data_type_i, val);
	else return FloatImm::make(data_type_f, val);
}

Expr visit(Ref<const Binary> op) override {
    Expr new_a = mutate(op->a);
    Expr new_b = mutate(op->b);
	
	if (op->op_type == BinaryOpType::Add || op->op_type == BinaryOpType::Sub){// (a \pm b)' = da \pm db
	    return Binary::make(op->type(), op->op_type, new_a, new_b);
	}
    else if (op->op_type == BinaryOpType::Mul){ // (a * b)' = a * db + b * da
	    Expr adb = Binary::make(op->type(), BinaryOpType::Mul, op->a, new_b);
		Expr bda = Binary::make(op->type(), BinaryOpType::Mul, new_a, op->b);
	    return Binary::make(op->type(), BinaryOpType::Add, adb, bda);
	}
	// TODO: division (by a constant)
	return op;
}

Stmt visit(Ref<const Move> op) {

    Expr new_src = Binary::make(op->src->type(), BinaryOpType::Mul, grad_from, mutate(op->src));
	// TODO: this is just an ad-hoc fix.
	new_src = Binary::make(op->src->type(), BinaryOpType::Add, grad_to, new_src); 

    Stmt e = Move::make(grad_to, new_src, op->move_type);

	//IRPrinter debug_printer;
	//cout << "Move: " << debug_printer.print(e) << endl;

	return e;
}

Stmt visit(Ref<const IfThenElse> op) override {

    Stmt new_true_case = mutate(op->true_case);
	Stmt new_false_case = op->false_case;
	if ((op->false_case).defined()) {
		new_false_case = mutate(op->false_case);
	}
    return IfThenElse::make(op->cond, new_true_case, new_false_case);
}

Stmt visit(Ref<const LoopNest> op) override {

    std::vector<Stmt> new_body_list;
    for (auto body : op->body_list) {
        new_body_list.push_back(mutate(body));
    }
    Stmt e =  LoopNest::make(op->index_list, new_body_list);
	//IRPrinter debug_printer;
	//cout << "Loop: " << debug_printer.print(e) << endl;
	return e;
}



};

class SimplifyMutator: public IRMutator{
public:
bool iszero(Expr op){
	if (op->node_type() == IRNodeType::IntImm){
		return (op.as<IntImm>()->value() == 0);
	}
	else if (op->node_type() == IRNodeType::FloatImm){
		return (std::abs(op.as<FloatImm>()->value()) < eps);
	}
	return false;
}

bool isone(Expr op){
	if (op->node_type() == IRNodeType::IntImm){
		return (op.as<IntImm>()->value() == 1);
	}
	else if (op->node_type() == IRNodeType::FloatImm){
		return (std::abs(op.as<FloatImm>()->value() - 1.0) < eps);
	}
	return false;
}

Expr visit(Ref<const Binary> op) override {
    Expr new_a = mutate(op->a);
    Expr new_b = mutate(op->b);
	if (op->op_type == BinaryOpType::Add || op->op_type == BinaryOpType::Sub){
		if (iszero(new_a)) return new_b;
		if (iszero(new_b)) return new_a;
		// TODO: merge constants
	}
    else if (op->op_type == BinaryOpType::Mul){ // (a * b)' = a * db + b * da
		if (isone(new_a) || iszero(new_b)) return new_b; // 1*b = b, a*0 = 0
		if (isone(new_b) || iszero(new_a)) return new_a; // a*1 = 1, 0*b = 0
		// TODO: merge constants
	}
	return Binary::make(op->type(), op->op_type, new_a, new_b);
}

Stmt visit(Ref<const IfThenElse> op) override {

    Stmt new_true_case = mutate(op->true_case);
	Stmt new_false_case = op->false_case;
	if ((op->false_case).defined()) {
		new_false_case = mutate(op->false_case);
	}
    return IfThenElse::make(op->cond, new_true_case, new_false_case);
}


};

class CountVarVisitor: public IRVisitor{
public:
void visit(Ref<const Var> op) override{
    in_set.insert(op->name);
}

void visit(Ref<const IfThenElse> op) {
    (op->cond).visit_expr(this);
    (op->true_case).visit_stmt(this);
	if ((op->false_case).defined()) {
		(op->false_case).visit_stmt(this);
	}
    
    return;
}

};

int main(){
    for (const string &filename : cases) {
        try {
			cout << filename << endl;
			result.clear();
			varMap.clear();
			in_set.clear();

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
			string s_grad_from = root["outs"][0].asString();

			vector<string> in_args;
			int in_size = root["ins"].size();
			for (int i = 0; i < in_size; i++){
				in_args.push_back(root["ins"][i].asString());
			}
			
			vector<string> out_args;
			int grad_size = root["grad_to"].size();
			for (int i = 0; i < grad_size; i++) {
				string id = root["grad_to"][i].asString();
				out_args.push_back(id);
			}

			if (data_type == "float") var_type = data_type_f;
			else var_type = data_type_i;

			scan_string(kernel.c_str());
			yyparse();
			delete_buffer();
			/* start autodiff */
			IRPrinter debug_printer;
			cout << "original code: " << debug_printer.print(result[0]) << endl;
			vector<Stmt> grad_stmt;

			DiffMutator diffMutator;
			SimplifyMutator simplifyMutator;
			CountVarVisitor countVarVisitor;

			auto tmp = varMap[s_grad_from].as<Var>();
			Expr grad_from = Var::make(tmp->type(), "d" + tmp->name, tmp->args, tmp->shape);
			vector<Expr> grad_expr, out_expr;
			for (const string &s : out_args){
				grad_expr.push_back(varMap[s]);
			}

			
			vector<Stmt> diffStmt;
			diffMutator.grad_from = grad_from;
			for (int i = 0; i < grad_expr.size(); i++){
				auto tmp = grad_expr[i].as<Var>();
				Expr dtmp = Var::make(tmp->type(), "d" + tmp->name, tmp->args, tmp->shape);
				out_expr.push_back(dtmp);
				diffMutator.grad_to = dtmp;

				Stmt s = diffMutator.mutate(result[0]);
				s = simplifyMutator.mutate(s);

				IRPrinter debug_printer;
				cout << "after diffMutator: " << debug_printer.print(s) << endl;
				s.visit_stmt(&countVarVisitor);
				diffStmt.push_back(s);
			}
			cout << "goo!\n";
			
			vector<Expr> in_expr;
			for (const string& s: in_args){
				if (in_set.count(s) > 0) in_expr.push_back(varMap[s]);
			}
			if (in_set.count(grad_from.as<Var>()->name) > 0) in_expr.push_back(grad_from);
			
			Group proc = Kernel::make(name, in_expr, out_expr, diffStmt, KernelType::CPU);
			
			ofstream outf(outpath);
			
			IRPrinter printer;
			outf << "#include \"../run2.h\"\n\n";
			outf << printer.print(proc) << endl;
			cout << "code: \n" << printer.print(proc) << endl;
        }
		catch(...){}
    }

    return 0;
}
