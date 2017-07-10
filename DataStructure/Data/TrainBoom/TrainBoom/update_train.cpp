#include <bits/stdc++.h>
#include "../../../src/Date.hpp"
using namespace std;

typedef long long LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	ifstream fin("车次.out");
	ofstream fout("origin_train");
	set<string> S;
	S.clear();
	
	string str, str1, str2, str3;
	int cnt = 0;
	bool flag = true;
	while (fin >> str) {
		if (str.size() < 20) {	
			if (S.find(str) != S.end()) {
std::cout << str << std::endl;
				flag = false;
				continue;
			} else {
				flag = true;
				fout << str << endl;		
				S.insert(str);
			}
			
			++cnt;
			fin >> str1;
			fin >> str2;
			int c = 0;
			str = "";
			for (int i = 0; i < str2.size(); ++i) {
				if (str2[i] == ',') {
					if (++c == 3) {
						str += ',';
					}
					continue;
				}
				if (c == 1 || c == 3) {
					str += str2[i];
				}
			}
			sjtu::Date date(str);
			fout << str << " ";
			for (int i = 0; i < 30; ++i) {
				date.go_one_day();
			}
			fout << date.print() << endl;
			fout << str1 << endl << str2 << endl;
		} else {
			if (flag) {
				fout << str << endl;
			}
			//cout << str << endl;
		}
	}
	fout << "endl" << endl;
	std::cout << cnt << std::endl;
}
