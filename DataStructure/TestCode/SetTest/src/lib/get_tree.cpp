#include <iostream>
#include <vector>
#include "set.hpp"
#include "../File.hpp"
#include "./ptr.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using sjtu::BinaryOutput;
using sjtu::BinaryInput;
using sjtu::shared_ptr;
using sjtu::set;

class A {
	string str;
public:
	A() {}
	A(string s): str(s) {}
	friend BinaryOutput &operator << (BinaryOutput &out, const A &obj) {
		out << obj.str;
		return out;
	}
};

int main() {
	BinaryInput file("tree");
	//map<string, string> M;
	set<string> M;
	M.clear();
	file >> M;
std::cerr << "return" << std::endl;
	for (set<string>::iterator it = M.begin(); it != M.end(); ++it) {
		cout << *it << endl;
	}
	/*cout << M.size() << endl;
	cout << M["123"] << endl;
	map<string, string>::iterator iter = M.end();
	iter--;
	iter--;
	
	cout << iter -> first << endl;
	cout << iter -> second << endl;
	iter--;
	
	cout << iter -> first << endl;
	cout << iter -> second << endl;
	iter--;
	
	cout << iter -> first << endl;
	cout << iter -> second << endl;
	iter--;
	
	cout << iter -> first << endl;
	cout << iter -> second << endl;*/
	
	/*	
	BinaryOutput file("tree");
	A temp;
	file << temp;*/
}
