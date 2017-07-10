#include <iostream>
#include <vector>
#include "map.hpp"
#include "File.hpp"
#include "./lib/ptr.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using sjtu::BinaryOutput;
using sjtu::BinaryInput;
using sjtu::shared_ptr;
using sjtu::map;

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
	map<string, string> M;
	M.clear();
	file >> M;
	for (map<string, string>::iterator it = M.begin(); it != M.end(); ++it) {
		cout << it -> first << " " << it -> second << endl;
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
