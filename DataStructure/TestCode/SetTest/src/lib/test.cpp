#include <iostream>
#include <vector>
#include "set.hpp"
#include "../File.hpp"
#include "./ptr.hpp"
#include <string>
#include <ctime>
#include <cassert>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using sjtu::BinaryOutput;
using sjtu::BinaryInput;
using sjtu::shared_ptr;
using sjtu::set;

//namespace sjtu {

	class Train {
		string s;
		int asd;
	};
	class TT {
		std::vector<Train> aa;
	};

//}

class B {
	string b;
public:
	B() {};
	B(string b): b(b) {};
	friend BinaryOutput &operator << (BinaryOutput &out, const B &rhs) {
		out << rhs.b;
		return out;
	}
	friend BinaryInput &operator >> (BinaryInput &in, B &rhs) {
		in >> rhs.b;
		return in;
	}
};

template<typename T>
class A {
	T a;
public:
	A() {};
	A(T a): a(a) {};
	friend BinaryOutput &operator << (BinaryOutput &out, const A &rhs) {
		out << *rhs.a;
		return out;
	}
};

inline string get_s() {
	int l = rand() % 10 + 5;
	string ret = "";
	for (; l; --l) {
		ret += char('a' + rand() % 20);
	}
	return ret;
}

//const int N = 100000;
const int N = 300000;

int main() {
	srand(time(0));
	//map<string, string> M;
	set<string> M;
	M.clear();
	/*M["123"] = "321";
	M["1"] = "2";
	M["2"] = "3";
	M["3"] = "1";*/
	for (int i = 0; i < N; ++i) {
		//M[get_s()] = get_s();
		M.insert(get_s());
	}
	BinaryOutput f1("tree");
	f1 << M;
	
	for (set<string>::iterator it = M.begin(); it != M.end(); ++it) {
		cout << *it << endl;
	}
	
	//BinaryOutput f1(string("out"));
	//f1 << 123;
	
	/*BinaryInput f2(string("out"));
	int a; string str;
	f2 >> a;
	cout << a << endl;*/
	//string ttt = "123";
	//shared_ptr<string> ppp(new string(ttt));
	//*ppp = "12321321";
	 
	/*B temp("adsf");
	A<B> now(B("asdssd"));
	sjtu::shared_ptr<BinaryOutput> f1 = new BinaryOutput(string("out"));
	(*f1) << now;
	f1.~shared_ptr();
	//return 0;
	
	sjtu::shared_ptr<BinaryInput> f2(new BinaryInput(string("out")));
	string str;
	int a(0);
	(*f2) >> str;
	cout << a << endl;
	cout << str << endl;
	f2.~shared_ptr();
	//delete f1;*/
}
