#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "exp.tab.h"

#include "IR.h"
#include "IRPrinter.h"
#include "type.h"
#include "json/json.h"


using namespace std;
using namespace Boost::Internal;

const vector<string> cases({"case1", "case2", "case3", "case4", "case5", "case6", "case7", "case8", "case9", "case10"});

extern vector<Stmt> result;
extern map<string, Expr> varMap;
extern Type var_type, data_type_i, data_type_f;
extern void scan_string(const char *s);
extern void delete_buffer();

pair<string, string> check_element_wise(string InputExp) {
	const char *st = InputExp.c_str();
	char same[100];
	string ret = "", common = "";
	int flag = 0;
	memset(same, 0, sizeof(same));
	int len = strlen(st);
	int i = 0;
	while (i < len) {
		if (st[i] == '<') {
			char s[100];
			memset(s, 0, sizeof(s));
			int tmp = 0;
			while (st[i] != ']')
				s[tmp] = st[i], tmp++, i++;
			s[tmp++] = st[i];
			if (strlen(same) == 0) {
				strcpy(same, s);
				for (int i = 0; i < tmp; i++)
					common = common + s[i];
			}
			else
				if (strcmp(same, s) != 0)
					return make_pair("", "");
		}
		else {
			if (flag && st[i] != ' ' && st[i] != ';')
				ret = ret + st[i];
			if (st[i] == '=')
				flag = 1;
		}
		i++;
	}
	return make_pair(ret, common);
}

string Expression_derivation(string exp, string id) {
	string ret = "";
	const char *c = exp.c_str();
	int len = strlen(c);
	int pos = -1;
	for (int i = 0; i < len; i++) {
		if (c[i] == '+') {
			pos = i;
			break;
		}
		if (c[i] == '*') {
			pos = i;
		}
	}
	if (pos == -1) {
		if (exp == id)
			return "1";
		else
			return "0";
	}
	
	if (c[pos] == '+') {
		string str1 = Expression_derivation(exp.substr(0, pos), id);
		string str2 = Expression_derivation(exp.substr(pos + 1), id);
		if (str1 == "0")
			return str2;
		if (str2 == "0")
			return str1;
		return "(" + str1 + "+" + str2 + ")";
	}
	
	if (c[pos] == '*') {
		string str1 = Expression_derivation(exp.substr(0, pos), id);
		string str2 = exp.substr(pos + 1);
		string str3 = Expression_derivation(exp.substr(pos + 1), id);
		string str4 = exp.substr(0, pos);
		if (str1 == "0" && str3 == "0")
			return "0";
		if (str1 == "0") {
			if (str3 == "1")
				return  str4;
			else
				return str3 + "*" + str4;
		}
		if (str3 == "0") {
			if (str1 == "1")
				return  str2;
			else
				return str1 + "*" + str2;
		}
		
		if (str1 == "1" && str3 == "1")
			return "(" + str2 + "+" + str4 + ")";
		if (str1 == "1")
			return "(" + str2 + "+" + "(" + str3 + "*" + str4 + "))";
		if (str3 == "1")
			return "((" + str1 + "*" + str2 + ")" + "+" + str4 + ")";
		return "((" + str1 + "*" + str2 + ")" + "+" + "(" + str3 + "*" + str4 + ")" + ")";
	}
	
}

bool checkin(string s1, string s2) {
	const char *c = s2.c_str();
	int len = strlen(c);
	int i = 0;
	while (i < len) {
		string tmp = "";
		while ((c[i] >= 'A' && c[i] <= 'Z') || (c[i] >= 'a' && c[i] <= 'z')) {
			tmp =tmp + c[i], i++;
			if (i == len) break;
		}
		if (s1 == tmp)
			return true;
		i++;
	}
	return false;
}

string element_wise(pair<string, string> pairs, string grad_id, string out_id, vector<string> in_args) {
	string ret = "d" + grad_id + pairs.second + '=' + "d" + out_id + pairs.second;
	string str = Expression_derivation(pairs.first, grad_id);
	string tmp_str = "";
	const char *c = str.c_str();
	int len = strlen(c);
	int i = 0;
	while (i < len) {
		string tmp = "";
		while ((c[i] >= 'A' && c[i] <= 'Z') || (c[i] >= 'a' && c[i] <= 'z')) {
			tmp =tmp + c[i], i++;
			if (i == len) break;
		}
		bool flag = 0;
		if (tmp != "") {
			for (const string &s : in_args) {
				if (s == tmp) {
					flag = 1;
				}
			}
			if (flag)
				tmp_str = tmp_str + tmp + pairs.second;
			else
				tmp_str = tmp_str;
		}
		if (i < len)
			tmp_str = tmp_str + c[i];
		i++;
	}
	return ret + "*" + tmp_str + ";";
}

pair<map<string, string>, pair<string, bool> > Get_identifier_range(string str) {
	const char *c = str.c_str();
	map<string, string> mp;
	map<string, bool> mark;
	mp.clear();
	mark.clear();
	string exp = "";
	bool res = 1;
	mp.clear();
	int len = strlen(c);
	int i = 0, flag = 0;
	while (i < len) {
		string tmp = "";
		while ((c[i] >= 'A' && c[i] <= 'Z') || (c[i] >= 'a' && c[i] <= 'z')) {
			tmp =tmp + c[i], i++;
			if (i == len) break;
		}
		if (flag) {
			exp = exp + tmp;
		}
		string range = "";
		if (tmp != "") {
			while (c[i] != '<') i++;
			while (c[i] != ']') {
				range = range + c[i];
				i++;
			}
			range = range + c[i];
			if (mark[tmp] && mp[tmp] != range)
				res = 0;
			mp[tmp] = range;
			mark[tmp] = 1;
		}
		if (flag && c[i] != ' ' && c[i] != ';' && c[i] != ']')
			exp += c[i];
		if (c[i] == '=')
			flag = 1;
		i++;
	}
	return make_pair(mp, make_pair(exp, res));
}

string no_transformation(string exp, map<string, string> maps, string grad_id, string out_id, vector<string> in_args) {
	string ret = "d" + grad_id + maps[grad_id] + '=' + "d" + out_id + maps[out_id];
	string str = Expression_derivation(exp, grad_id);
	string tmp_str = "";
	const char *c = str.c_str();
	int len = strlen(c);
	int i = 0;
	while (i < len) {
		string tmp = "";
		while ((c[i] >= 'A' && c[i] <= 'Z') || (c[i] >= 'a' && c[i] <= 'z')) {
			tmp =tmp + c[i], i++;
			if (i == len) break;
		}
		bool flag = 0;
		if (tmp != "") {
			for (const string &s : in_args) {
				if (s == tmp) {
					flag = 1;
				}
			}
			if (flag)
				tmp_str = tmp_str + tmp + maps[tmp];
			else
				tmp_str = tmp_str;
		}
		if (i < len)
			tmp_str = tmp_str + c[i];
		i++;
	}
	return ret + "*" + tmp_str + ";";
}

int main(){
    for (const string &filename : cases) {
        try {
			cout << filename << endl;
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
				string id = "d" + root["outs"][i].asString();
				if (ind_set.count(id) > 0) continue;
				in_args.push_back(id);
				//out_args.push_back(id);
			}

			int grad_size = root["grad_to"].size();
			for (int i = 0; i < grad_size; i++) {
				string id = "d" + root["grad_to"][i].asString();
				out_args.push_back(id);
			}

			if (data_type == "float") var_type = data_type_f;
			else var_type = data_type_i;

			//检查表达式是否为element-wise的
			pair<string, string> pr = check_element_wise(kernel);

			//cout << pr.first << " " << pr.second << endl;
		
			if (pr.first != "") {
				string grad_exp = "";
				int grad_size = root["grad_to"].size();
				for (int i = 0; i < grad_size; i++)
					grad_exp = grad_exp + element_wise(pr, root["grad_to"][i].asString(), root["outs"][0].asString(), in_args);

				cout << grad_exp << endl;
				//cout << kernel << endl;
				scan_string(grad_exp.c_str());
				yyparse();
				delete_buffer();

				//Stmt body = StmtList::make(result);
				vector<Expr> in_expr;
				for (const string &s : in_args){
					if (checkin(s, grad_exp)) {
						in_expr.push_back(varMap[s]);
						//cout << s << endl;
					}
				}

				vector<Expr> out_expr;
				for (const string &s : out_args){
					out_expr.push_back(varMap[s]);
				}

				Group proc = Kernel::make(name, in_expr, out_expr, result, KernelType::CPU);

				ofstream outf(outpath);

				IRPrinter printer;
				outf << "#include \"../run2.h\"\n\n";
				outf << printer.print(proc) << endl;
				continue;
			}

			//End of element-wise

			pair<map<string, string>, pair<string, bool> > pairs = Get_identifier_range(kernel);
			map<string, string> mp = pairs.first;
			string exp = pairs.second.first;
			bool flag = 1;
			//检查是否有下标的算术变换
			for (pair<string, string> pr : mp) {
				string st = pr.second;
				if (st.find("+") != st.npos || st.find("*") != st.npos ||
					st.find("%") != st.npos || st.find("-") != st.npos || st.find("//") != st.npos)
					flag = 0;
			}
			if (flag && pairs.second.second) {
				string grad_exp = "";
				int grad_size = root["grad_to"].size();
				for (int i = 0; i < grad_size; i++)
					grad_exp = grad_exp + no_transformation(exp, mp, root["grad_to"][i].asString(), root["outs"][0].asString(), in_args);
				cout << grad_exp << endl;
				scan_string(grad_exp.c_str());
				yyparse();
				delete_buffer();

				//Stmt body = StmtList::make(result);
				vector<Expr> in_expr;
				for (const string &s : in_args){
					if (checkin(s, grad_exp)) {
						in_expr.push_back(varMap[s]);
						//cout << s << endl;
					}
				}

				vector<Expr> out_expr;
				for (const string &s : out_args){
					out_expr.push_back(varMap[s]);
				}

				Group proc = Kernel::make(name, in_expr, out_expr, result, KernelType::CPU);

				ofstream outf(outpath);

				IRPrinter printer;
				outf << "#include \"../run2.h\"\n\n";
				outf << printer.print(proc) << endl;
				continue;
			}
				//}
        }
		catch(...){}
    }

    return 0;
}
