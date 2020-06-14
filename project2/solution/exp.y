%{
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include "IR.h"
#include "RHSDecompVisitor.h"
#include "BoundInferenceVisitor.h"
#include "IRPrinter.h"
#include "type.h"

using namespace Boost::Internal;
using std::set;
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::cout;
using std::endl;
using std::stringstream;

#define YYSTYPE string

typedef vector<size_t> CList;
typedef vector<Expr> AList;

struct TRef {
    string id;
    CList *clist;
    AList *alist;
};

struct SRef {
    string id;
};

struct Const {
    void *val;
    int type;
};

Type index_type = Type::int_scalar(32);
Type data_type_i = Type::int_scalar(32);
Type data_type_f = Type::float_scalar(32);
Type var_type = data_type_f;
int temp_num = 0;

stack<void*> st;
stack<Expr> ste;
vector<Expr> cond;
vector<Stmt> result;


map<string, Expr> varMap;



int yyparse();
int yylex(void);
void yyerror(char *msg);

template <typename T>
void printVec(vector<T> vec, bool newline = 1);
void printExpr(const Expr& e);

template<typename T>
T parseConst(string str);

set<string> merge(const set<string>& a, const set<string>& b);
Stmt getMainStmt(TRef& lhs, Expr& rhs);
ExprNode *exprp(Expr &e);
set<string>& usedId(Expr& e);
bool insertExpr(vector<Expr>& arr, Expr& e);

%}

/* foo 42 3.14 */
%token ID INTV FLOATV 
/* = , ; ( ) [ ] < > */
%token EQ
/* + - */
%left PLUS MINUS
/* * / // % */
%left MUL DIV IDIV MOD
%%


/* P ::= P S | S */
p : p s
{
    //cout << "P ::= P S\n";
}
| s
{
    //cout << "P ::= S\n";
}


/* S ::= LHS = RHS; */
s : lhs EQ rhs ';'
{
    //cout << "S ::= LHS = RHS;\n";
    Stmt e = getMainStmt(*((TRef*) st.top()), ste.top()); 
    st.pop();
    ste.pop();
    result.push_back(e);
    // cout << endl << IRPrinter().print(e) << endl;
    cond.clear();

}


/* LHS ::= TRef */
lhs : tref
{
    //cout << "LHS ::= TRef\n";
}


/* RHS ::= RHS [+, -, *, /, %, //] RHS 
       | (RHS) | TRef | SRef | Const */
rhs : rhs PLUS rhs
{
    //cout << "RHS ::= RHS + RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| rhs MUL rhs
{
    //cout << "RHS ::= RHS * RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Mul, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| rhs MINUS rhs
{
    //cout << "RHS ::= RHS - RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Sub, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| rhs DIV rhs
{
    // cout << "RHS ::= RHS / RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(data_type_f, BinaryOpType::Div, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| rhs MOD rhs
{
    // cout << "RHS ::= RHS % RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Mod, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| rhs IDIV rhs
{
    // cout << "RHS ::= RHS // RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(data_type_i, BinaryOpType::IDiv, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| '(' rhs ')'
{
    // cout << "RHS ::= (RHS)\n";
    Expr e = ste.top(); ste.pop();
    exprp(e)->bracketed = 1;
    ste.push(e);
}
| tref
{
    // cout << "RHS ::= TRef\n";
    TRef *t = (TRef*) st.top(); st.pop();
    Expr e = Var::make(var_type, t->id, *(t->alist), *(t->clist));
    
    for (auto o : *(t->alist))
        usedId(e) = merge(usedId(e), usedId(o));
    ste.push(e);
}
| sref
{
    // cout << "RHS ::= SRef\n";
    SRef *t = (SRef*) st.top(); st.pop();
    Expr e = Var::make(var_type, t->id, {0}, {1});
    ste.push(e);
}
| const
{
    // cout << "RHS ::= Const\n";
    Const *t = (Const*) st.top(); st.pop();
    if (t->type == 0) {
        Expr e = IntImm::make(data_type_i, *((int*) t->val));
        ste.push(e);
    } else {
        Expr e = FloatImm::make(data_type_f, *((float*) t->val));
        ste.push(e);
    }
}

/* ================================= TRef & SRef ================================= */
/* TRef ::= Id<CList>[Alist] */
tref : ID '<' clist '>' '[' alist ']'
{
    // cout << "TRef ::= Id<CList>[Alist]\n";
    TRef *t = new TRef();
    t->id = $1;
    t->alist = (AList*) st.top(); st.pop();
    t->clist = (CList*) st.top(); st.pop();

    st.push(t);

    Expr sign_e = Var::make(var_type, t->id, *(t->alist), *(t->clist));
    varMap[t->id] = sign_e;
    
    for (int i = 0; i < t->alist->size(); i++) {
        Expr c1 = Compare::make(index_type, CompareOpType::GE, t->alist->at(i), IntImm::make(index_type, 0));
        usedId(c1) = usedId(t->alist->at(i));
        // cout << IRPrinter().print(c1) << endl;
        insertExpr(cond, c1);
        Expr c2 = Compare::make(index_type, CompareOpType::LT, t->alist->at(i), IntImm::make(index_type, t->clist->at(i)));
        usedId(c2) = usedId(t->alist->at(i));
         // cout << IRPrinter().print(c2) << endl;
        insertExpr(cond, c2);
    }
}
/* SRef ::= Id<CList> */
sref : ID '<' clist '>'
{
    // cout << " SRef ::= Id<CList>\n";
    st.pop(); // clist
    SRef *t = new SRef();
    t->id = $1;
    st.push(t);

    Expr sign_e = Var::make(var_type, t->id, {0}, {1});
    varMap[t->id] = sign_e;
}
/* CList ::= CList, IntV | IntV */
clist : clist ',' INTV
{
    // cout << "CList ::= CList, " << $3 << endl;
    CList *t = (CList*) st.top(); 
    t->push_back(parseConst<int>($3));
}
| INTV
{
    // cout << "CList ::= " << $1 << endl;
    CList *t = new CList();
    t->push_back(parseConst<int>($1));
    st.push(t);
}
/* AList ::= AList, IdExpr | IdExpr */
alist : alist ',' idexpr
{
    // cout << "AList ::= AList, IdExpr\n";
    AList *t = (AList*) st.top();
    t->push_back(ste.top());
    ste.pop();
}
| idexpr
{
    // cout << "AList ::= IdExpr\n";
    AList *t = new AList();
    t->push_back(ste.top());
    ste.pop();
    st.push(t);
}


/* (original) IdExpr ::= Id | IdExpr + IdExpr | IdExpr [+, *, //, %] IntV | (IdExpr) */
idexpr : ID
{
    // cout << "IdExpr ::= " << $1 << endl;
    Expr dom_t = Dom::make(Type::int_scalar(32), 0, 9);
    Expr t = Index::make(Type::int_scalar(32), $1, dom_t, IndexType::Spatial);
    usedId(t).insert($1);
    ste.push(t);
}
| idexpr PLUS idexpr
{
    // cout << "IdExpr ::= IdExpr + IdExpr\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(index_type, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| idexpr PLUS INTV
{
    // cout << "IdExpr ::= IdExpr + " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>($3));
    Expr t = Binary::make(index_type, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| idexpr MUL INTV
{
    // cout << "IdExpr ::= IdExpr * " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>($3));
    Expr t = Binary::make(index_type, BinaryOpType::Mul, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| idexpr IDIV INTV
{
    // cout << "IdExpr ::= IdExpr // " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>($3));
    Expr t = Binary::make(index_type, BinaryOpType::IDiv, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| idexpr MOD INTV
{
    //cout << "IdExpr ::= IdExpr % " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>($3));
    Expr t = Binary::make(index_type, BinaryOpType::Mod, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
| '(' idexpr ')'
{
    //cout << "IdExpr ::= (IdExpr)\n";
}


/* Const ::= FloatV | IntV */
const : FLOATV
{
    //cout << "Const ::= " << $1 << endl;
    Const *t = new Const;
    float *v = new float;
    *v = parseConst<float>($1);
    t->val = v, t->type = 1;
    st.push(t);
}
| INTV
{
    //cout << "Const ::= " << $1 << endl;
    Const *t = new Const;
    int *v = new int;
    *v = parseConst<int>($1);
    t->val = v, t->type = 0;
    st.push(t);
}
| MINUS const
{
    Const *t = (Const*) st.top();
    if (t->type == 0) {
        int *v = (int*) t->val;
        *v = -*v;
    } else {
        float *v = (float*) t->val;
        *v = -*v;
    }
}


%%


void yyerror(char *msg)
{
    cout << "Error encountered: " << msg << endl; 
}

template <typename T>
void printVec(vector<T> vec, bool newline) {
    for (auto t : vec) {
        cout << t << " ";
    }
    if (newline)
        cout << endl;
}

template<typename T>
T parseConst(string str) {
    stringstream ss;
    T t;
    ss << str;
    ss >> t;
    return t;
}

void printExpr(const Expr& e) {
    IRPrinter printer;
    string code = printer.print(e);
    cout << code << endl;
}

set<string> merge(const set<string>& a, const set<string>& b) {
    set<string> t;
    t.insert(a.begin(), a.end());
    t.insert(b.begin(), b.end());
    return t;
}

bool contain(vector<string>& a, const set<string>& b) {
    for (auto t : b) {
        bool flag = 0;
        for (auto r : a)
            if (t == r) {
                flag = 1; break;
            }
        if (!flag)
            return 0;
    }
    return 1;
}

vector<Expr> mapIdToExpr(map<string, Expr>& mp, vector<string> ids) {
    vector<Expr> res;
    for (auto id : ids)
        res.push_back(mp[id]);
    return res;
}

// 构造整个 Stmt
Stmt getMainStmt(TRef& lhs, Expr& rhs) {
    set<string> leftIdSet;   // 出现在 LHS 的循环变量
    vector<string> leftId, leftId1;   // 出现在 LHS 的循环变量
    map<string, Expr> mp;    // 从循环变量名到对应 Expr 的映射
    vector<Expr> stmtList;   

    for (auto e : *(lhs.alist))
        for (auto t : usedId(e)) {
            leftId.push_back(t);
            leftIdSet.insert(t);
        }

    // 为每个循环变量粗略定界
    BoundInferenceVisitor bv;
    for (auto id : leftId)
        bv.mp[id] = make_pair(0, 1 << 20);
    for (auto id : usedId(rhs))
        bv.mp[id] = make_pair(0, 1 << 20);
        
    for (auto e : cond) {
        // cout << "Condition : " << IRPrinter().print(e) << endl;
        Compare *t = (Compare*) e.get();
        if (t->op_type == CompareOpType::LT) {
            bv.lo = -(1 << 20);
            bv.hi = ((IntImm*) (t->b).get())->value();
            (t->a).visit_expr(&bv);
        } else if (t->op_type == CompareOpType::GE) {
            bv.lo = ((IntImm*) (t->b).get())->value();
            bv.hi = 1 << 20;
            (t->a).visit_expr(&bv);
        }
        /*
        for (auto t : bv.mp) {
            cout << t.first << " : [" << t.second.first << ", " << t.second.second << ")" << endl;
        }
        */
    }

    for (auto id : leftId) {
        Expr dom = Dom::make(index_type, bv.mp[id].first, bv.mp[id].second);
        mp[id] = Index::make(index_type, id, dom, IndexType::Spatial);
    }
    for (auto id : usedId(rhs)) {
        if (mp.find(id) == mp.end()) {
            Expr dom = Dom::make(index_type, bv.mp[id].first, bv.mp[id].second);
            mp[id] = Index::make(index_type, id, dom, IndexType::Reduce);
        }
    }

    // 处理 LHS 的循环变量和条件判断
    for (auto id : leftId) {
        // cout << id << endl;
        leftId1.push_back(id);
        stmtList.push_back(Var::make(index_type, id, {0}, {1}));      // 定义成 Var 只是为了将循环和条件判断区分开，无实际意义

        vector<Expr> nowCond;
        for (auto it = cond.begin(); it != cond.end(); )
            if (contain(leftId1, usedId(*it))) {
                // printExpr(*it);
                nowCond.push_back(*it);
                cond.erase(it);
            } else
                it++;
        
        if (nowCond.size() > 0) {
            Expr e = nowCond[0];
            if (nowCond.size() > 1) {
                for (int i = 1; i < nowCond.size(); i++)
                    e = Binary::make(data_type_i, BinaryOpType::And, e, nowCond[i]);
            }
            stmtList.push_back(e);
            // cout << "sum: ";
            // printExpr(e);
        }
    }

    RHSDecompVisitor visitor;
    rhs.visit_expr(&visitor);

    vector<Stmt> body;


    vector<size_t> shape;
    for (auto id : leftId)
        shape.push_back(bv.mp[id].second);

    Expr dest = Var::make(var_type, lhs.id, mapIdToExpr(mp, leftId), shape);

    // 处理 RHS 的循环变量和条件判断
    for (auto e : visitor.res) {
        

        vector<Expr> stmtList;
        vector<string> curId(leftId.begin(), leftId.end());
        vector<Expr> remCond(cond.begin(), cond.end());

        for (auto id : usedId(e.first)) {
            if (leftIdSet.find(id) != leftIdSet.end())
                continue;
            curId.push_back(id);
            stmtList.push_back(Var::make(index_type, id, {0}, {1}));

            vector<Expr> nowCond;
            for (auto it = remCond.begin(); it != remCond.end(); )
                if (contain(curId, usedId(*it))) {
                    // printExpr(*it);
                    nowCond.push_back(*it);
                    remCond.erase(it);
                } else
                    it++;

            if (nowCond.size() > 0) {
                Expr e = nowCond[0];
                if (nowCond.size() > 1) {
                    for (int i = 1; i < nowCond.size(); i++)
                        e = Binary::make(data_type_i, BinaryOpType::And, e, nowCond[i]);
                }
                stmtList.push_back(e);
            }
        }

        // 生成每个求和部分的 Stmt
        Stmt s = Move::make(
            dest, 
            Binary::make(data_type_i, e.second == 1? BinaryOpType::Add: BinaryOpType::Sub, dest, e.first),
            MoveType::MemToMem
        );

        for (int i = stmtList.size() - 1; i >= 0; i--) {
            if (stmtList[i].node_type() == IRNodeType::Var) {
                // 是循环语句
                string id = ((Var*) stmtList[i].get())->name;
                // cout << id << endl;
                // cout << (mp.find(id) == mp.end()) << endl;
                s = LoopNest::make({mp[id]}, {s});
            } else {
                // 是 if 语句
                s = IfThenElse::make(stmtList[i], s, Stmt());
            }
        }

        body.push_back(s);
        // cout << endl << IRPrinter().print(s) << endl;
    }

    // 套上 LHS 的循环和条件
    Stmt s = StmtList::make(body);
    for (int i = stmtList.size() - 1; i >= 0; i--) {
        if (stmtList[i].node_type() == IRNodeType::Var) {
            // 是循环语句
            string id = ((Var*) stmtList[i].get())->name;
            // cout << id << endl;
            s = LoopNest::make({mp[id]}, {s});
        } else {
            // 是 if 语句
            s = IfThenElse::make(stmtList[i], s, Stmt());
        }
    }

    return s;
}

ExprNode *exprp(Expr &e) {
    return (ExprNode*) e.get();
}

set<string>& usedId(Expr& e) {
    return exprp(e)->usedId;
}

// 用于去除重复的条件判断
bool insertExpr(vector<Expr>& arr, Expr& e) {
    for (auto t : arr) {
        if (IRPrinter().print(t) == IRPrinter().print(e)) {
            return 0;
        }
    }
    arr.push_back(e);
    return 1;
}

