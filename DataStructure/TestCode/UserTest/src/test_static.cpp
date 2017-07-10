#include <bits/stdc++.h>
#include "lib/ptr.hpp"
using namespace std;

class A {
public:
	int a;
	A(int a): a(a) {};
};

class B : public A {
public:
	B(int b): A(b) {};
};

int main() {
	map<int, A> M;
	M[1] = B(1);
}
