#include <iostream>
#include <ctime>
#include <algorithm>
#include "set.hpp"
#include "ptr.hpp"
#include "map.hpp"

using sjtu::set;
using sjtu::map;
using std::string;

inline string get_string() {
	string str;
	int l = rand() % 10;
	for (; l; --l) {
		str = str + char(rand() % 120 + 1);
	}
	return str;
}

int main() {
	/*map<int, int> M;
	M[12] = 12;
	M[13] = 13;
	M[21] = 21;
	M[31] = 31;
	
	map<int, int>::iterator it = M.find(12);
	M.erase(it);
	it = M.find(13);
	M.erase(it);
	it = M.find(12);
	M.erase(it);
	it = M.find(13);
	M.erase(it);*/
	/*S.insert(12);
	S.insert(13);
	S.insert(21);
	S.insert(31);
	
	set<int>::iterator it = S.find(12);
	S.erase(it);
	it = S.find(21);
	S.erase(it);
	it = S.find(31);
	S.erase(it);*/
	
	srand(time(0));
	int N = 100000;
	string a[100000];
	set<string> S;
	for (int i = 0; i < N; ++i) {
		a[i] = get_string();
	}
	std::sort(a, a + N);
	N = std::unique(a, a + N) - a;
	for (int i = 0; i < N; ++i) {
		S.insert(a[i]);
	}
	set<string>::iterator it2 = S.begin();
	++it2;
	for (set<string>::iterator it = S.begin(); it2 != S.end(); ++it, ++it2) {
assert(*it < *it2);
cout << *it << endl;
	}
	
}
