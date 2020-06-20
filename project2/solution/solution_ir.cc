#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include "exp.tab.h"

#include "IR.h"
#include "IRPrinter.h"
#include "IRMutator.h"
#include "type.h"
#include "json/json.h"


using namespace std;
using namespace Boost::Internal;

const vector<string> cases({"case1", "case2", "case3", "case4", "case5", "case6", "case7", "case8", "case9", "case10"});
const double eps = 1e-6;

extern vector<Stmt> result;
extern map<string, Expr> varMap;
extern Type var_type, data_type_i, data_type_f;
extern void scan_string(const char *s);
extern void delete_buffer();

map<string, vector<Expr> > var_appearance_map;

bool is_same_var(const Expr& a, const Expr& b) {
	auto var_a = a.as<Var>();
	auto var_b = b.as<Var>();
	if (var_a == nullptr || var_b == nullptr) return false;
	return (IRPrinter().print(var_a) == IRPrinter().print(var_b));
}

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

Expr visit(Ref<const Var> op) override {
    //cout << "Var: " << op->name << endl;
	Expr new_var = Var::make(op->type(), "d" + op->name, op->args, op->shape);
	int val = is_same_var(new_var, grad_to) ? 1 : 0; // dx/dx = 1, dy/dx = 0

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
	else if (op->op_type == BinaryOpType::Div){
	    return Binary::make(op->type(), BinaryOpType::Div, new_a, op->b);
	}
	return op;
}

Stmt visit(Ref<const Move> op) {

    Expr new_src = Binary::make(op->src->type(), BinaryOpType::Mul, grad_from, mutate(op->src));
	// TODO: this is just an ad-hoc fix.
	new_src = Binary::make(op->src->type(), BinaryOpType::Add, grad_to, new_src); 

    return Move::make(grad_to, new_src, op->move_type);
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
    return LoopNest::make(op->index_list, new_body_list);
}


};

class SimplifyMutator: public IRMutator{
public:
bool iszero(Expr op){
	if (op->node_type() == IRNodeType::IntImm){
		return (op.as<IntImm>()->value() == 0);
	}
	else if (op->node_type() == IRNodeType::FloatImm){
		return (fabs(op.as<FloatImm>()->value()) < eps);
	}
	return false;
}

bool isone(Expr op){
	if (op->node_type() == IRNodeType::IntImm){
		return (op.as<IntImm>()->value() == 1);
	}
	else if (op->node_type() == IRNodeType::FloatImm){
		return (fabs(op.as<FloatImm>()->value() - 1.0) < eps);
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

class VarAppearanceVisitor: public IRVisitor{
public:
void visit(Ref<const Var> op) override{
    string name = op->name;
	if (var_appearance_map.count(name) == 0){ // never appeared before
	    var_appearance_map[name] = {op};
	}
	else{ // appeared before
	for (auto &t: var_appearance_map[name]){
		if (is_same_var(op, t)) return;
	}
	var_appearance_map[name].push_back(op);
	}
}

void visit(Ref<const IfThenElse> op) override {
    (op->cond).visit_expr(this);
    (op->true_case).visit_stmt(this);
	if ((op->false_case).defined()) {
		(op->false_case).visit_stmt(this);
	}
    
    return;
}    
};

class CountVarVisitor: public IRVisitor{
public:
void visit(Ref<const Var> op) override{
    in_set.insert(op->name);
}

void visit(Ref<const IfThenElse> op) override {
    (op->cond).visit_expr(this);
    (op->true_case).visit_stmt(this);
	if ((op->false_case).defined()) {
		(op->false_case).visit_stmt(this);
	}
    
    return;
}

};

string printExpr(const Expr& e) {
	IRPrinter p;
	return p.print(e);
}

class SubstituteVisitor : public IRVisitor {
public:
	vector<Expr> lhs_comp, conds;

	void visit(Ref<const Compare> op) override {
		conds.push_back(op);
	}

	void visit(Ref<const Move> op) override {
		Ref<const Var> t = (op->dst).as<Var>();
		if (t.defined()) {	
			for (auto o : t->args) {
				if (o.as<Binary>() != nullptr) {
					lhs_comp.push_back(o);
				}
			}
		}
	}

	void visit(Ref<const IfThenElse> op) override {
		(op->cond).visit_expr(this);
		(op->true_case).visit_stmt(this);
		if ((op->false_case).defined()) {
			(op->false_case).visit_stmt(this);
		}
	}
};

class SubstituteMutator : public IRMutator {
public:
	map<string, Expr> mp_sub, mp_newvar;
	map<string, int> mp_lo, mp_hi;
	vector<Expr> lhs_comp, conds;

	SubstituteMutator(const SubstituteVisitor& subVisitor) {
		this->conds = subVisitor.conds;
		this->lhs_comp = subVisitor.lhs_comp;
		for (auto cond : conds) {
			Ref<const Compare> t = cond.as<Compare>();
			string name = printExpr(t->a);
			if (t->b.as<IntImm>() != nullptr) {
				int v = t->b.as<IntImm>()->value();
				if (t->op_type == CompareOpType::LT) {
					if (mp_hi.find(name) == mp_hi.end()) {
						mp_hi[name] = 1 << 30;
					}
					mp_hi[name] = min(mp_hi[name], v);
				} else if (t->op_type == CompareOpType::GE) {
					if (mp_lo.find(name) == mp_lo.end()) {
						mp_lo[name] = -(1 << 30);
					}
					mp_lo[name] = max(mp_lo[name], v);
				}
			}
		}

		for (int i = 0; i < lhs_comp.size(); i++) {
			Expr &e = lhs_comp[i];
			Ref<const Binary> t = e.as<Binary>();
			string newVarName = string("i") + char(i + 48);
			Expr newDom = Dom::make(t->type(), mp_lo[printExpr(t)], mp_hi[printExpr(t)]);
			Expr newVar = Index::make(t->type(), newVarName, newDom, IndexType::Reduce);
			mp_newvar[newVarName] = newVar;

			mp_sub[printExpr(e)] = newVar;
			if (t->op_type == BinaryOpType::Add) {
				if (t->b.node_type() == IRNodeType::Index) {
					mp_sub[printExpr(t->b)] = Binary::make(t->type(), BinaryOpType::Sub, newVar, t->a);
				} else if (t->b.node_type() == IRNodeType::IntImm) {
					mp_sub[printExpr(t->a)] = Binary::make(t->type(), BinaryOpType::Sub, newVar, t->b);
				}
			}
		}
		for (auto &e : lhs_comp) {
			Ref<const Binary> t = e.as<Binary>();
			if (t->op_type == BinaryOpType::IDiv) {
				Expr modexpr = Binary::make(t->type(), BinaryOpType::Mod, t->a, t->b);
				Expr mulexpr = Binary::make(t->type(), BinaryOpType::Mul, mp_sub[printExpr(t)], t->b);
				mp_sub[printExpr(t->a)] = Binary::make(t->type(), BinaryOpType::Add, mulexpr, mp_sub[printExpr(modexpr)]);
			}
		}
	}

	Expr visit(Ref<const Binary> op) override {
		for (auto t : mp_sub) {
			if (printExpr(op) == t.first) {
				return t.second;
			}
		}
		Expr new_a = mutate(op->a);
    	Expr new_b = mutate(op->b);
		return Binary::make(op->type(), op->op_type, new_a, new_b);
	}

	Expr visit(Ref<const Index> op) override {
		for (auto t : mp_sub) {
			if (printExpr(op) == t.first) {
				return t.second;
			}
		}
		return op;
	}

	
	Stmt visit(Ref<const LoopNest> op) {
		std::vector<Expr> new_index_list;
		std::vector<Stmt> new_body_list;
		for (auto index : op->index_list) {
			auto it = mp_sub.find(printExpr(index));
			if (it != mp_sub.end()) {
				Ref<const Binary> e = it->second.as<Binary>();
				if (e->op_type == BinaryOpType::Sub) {
					new_index_list.push_back(e->a);
				} else if (e->op_type == BinaryOpType::Add) {
					Ref<const Binary> t = e->a.as<Binary>();
					if (t.defined()) {
						new_index_list.push_back(t->a);
						new_index_list.push_back(e->b);
					}
				}
			} else {
				new_index_list.push_back(index);
			}
		}
		for (auto body : op->body_list) {
			new_body_list.push_back(mutate(body));
		}
		return LoopNest::make(new_index_list, new_body_list);
	}

	Stmt visit(Ref<const IfThenElse> op) override {
		Expr new_cond = mutate(op->cond);
		Stmt new_true_case = mutate(op->true_case);
		Stmt new_false_case = op->false_case;
		if ((op->false_case).defined()) {
			new_false_case = mutate(op->false_case);
		}
		return IfThenElse::make(new_cond, new_true_case, new_false_case);
	}
};

int main(){
    for (const string &filename : cases) {
        try {
			cout << filename << endl;
			result.clear();
			varMap.clear();
			in_set.clear();
			var_appearance_map.clear();

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
			vector<Stmt> grad_stmt;

			DiffMutator diffMutator;
			SimplifyMutator simplifyMutator;
			VarAppearanceVisitor varAppearanceVisitor;
			CountVarVisitor countVarVisitor;

			result[0].visit_stmt(&varAppearanceVisitor);

			auto tmp = varMap[s_grad_from].as<Var>();
			Expr grad_from = Var::make(tmp->type(), "d" + tmp->name, tmp->args, tmp->shape);
			vector<Expr> out_expr;

			vector<Stmt> diffStmt;
			diffMutator.grad_from = grad_from;
			for (const string &grad_name : out_args){
				bool out_var_pushed = false;

				for (auto &tmp: var_appearance_map[grad_name]){
					auto tmp_var = tmp.as<Var>();
					Expr dtmp = Var::make(tmp->type(), "d" + grad_name, tmp_var->args, tmp_var->shape);
					if (!out_var_pushed) {
						out_expr.push_back(dtmp);
						out_var_pushed = true;
					}
					diffMutator.grad_to = dtmp;
					
					Stmt s = diffMutator.mutate(result[0]);
					s = simplifyMutator.mutate(s);
					
					s.visit_stmt(&countVarVisitor);
					diffStmt.push_back(s);
				}
			}

			vector<Expr> in_expr;
			for (const string& s: in_args){
				if (in_set.count(s) > 0) in_expr.push_back(varMap[s]);
			}
			if (in_set.count(grad_from.as<Var>()->name) > 0) in_expr.push_back(grad_from);
			
			
			for (auto &s : diffStmt) {
				IRPrinter p;
				cout << "Before substitution:" << endl;
				cout << p.print(s) << endl;

				SubstituteVisitor subVisitor;
				s.visit_stmt(&subVisitor);
				SubstituteMutator subMutator(subVisitor);
				s = subMutator.mutate(s);

				IRPrinter p2;
				cout << endl << "After:" << endl;
				cout << p2.print(s) << endl;
			}

			/* initialize out_expr */
			for (auto &d_exp : out_expr){
				auto d_var = d_exp.as<Var>();
				Expr zero_imm;
				if (d_var->type() == data_type_i)
				zero_imm = IntImm::make(data_type_i, 0);
				else zero_imm = FloatImm::make(data_type_f, 0.0);

				vector<Expr> temp_index_list;
				for (size_t i = 0; i < d_var->shape.size(); i++){
					Expr temp_dom = Dom::make(data_type_i, 0, (int) d_var->shape[i]);
					Expr temp_index = Index::make(data_type_i, "i"+ to_string(i), temp_dom, IndexType::Spatial);
					temp_index_list.push_back(temp_index);
				}

				Expr new_var = Var::make(d_var->type(), d_var->name, temp_index_list, d_var->shape);
				Stmt main_stmt = Move::make(new_var, zero_imm, MoveType::MemToMem);
				Stmt init_loop = LoopNest::make(temp_index_list, {main_stmt});
				diffStmt.insert(diffStmt.begin(), init_loop);
			}

			Group proc = Kernel::make(name, in_expr, out_expr, diffStmt, KernelType::CPU);
			
			ofstream outf(outpath);
			
			IRPrinter printer;
			outf << "#include \"../run2.h\"\n\n";
			outf << printer.print(proc) << endl;
        }
		catch(...){}
    }

    return 0;
}
