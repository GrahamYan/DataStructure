//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "Exceptions.hpp"
#include "File.hpp"
#include "Station.hpp"
#include "Train.hpp"
#include "Date.hpp"
#include "User.hpp"
//using namespace std;
using namespace sjtu;
using std::string;

typedef long long LL;

string get_str(const string &str, int &i) {
	string ret = "";
	for (; str[i] != ','; ++i) {
		ret += str[i];
	}
	++i;
	return ret;
}

int get_dist(const string &str, int &i) {
	string s = get_str(str, i);
	int dist = 0;
	for (int i = 0; i < s.size() && s[i] <= '9' && s[i] >= '0'; ++i) {
		dist = dist * 10 + s[i] - '0';
	}
	return dist;
}

double get_price(const string &str, int &i) {
	string s = get_str(str, i);
	double price = 0;
	int cnt = -1;
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] == '.') {
			cnt = 0;
			continue;
		}
	//	std::cout << int(s[i]) << " ";
		if (s[i] < '0' || s[i] > '9') {
			continue;
		}
		price = price * 10 + s[i] - '0';
		if (cnt > -1) {
			++cnt;
		}
	}
	for (; cnt > 0; --cnt) {
		price /= 10;
	}
//std::cout << "str = " << s << " price = " << price << std::endl;
	return price;
}

double ppp(double price, int type) {
	if (type == 1) {
		return price;
	} else {
		return price < 0.3 ? 1000000000 : price;
	}
}

int main() {
	/*ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);*/
	User *user(new User());
	AscllInput file("in");
	string str, last = "";
	string id = "", standard("站名");
	vector<int> left_n;
	vector<string> level;
	vector<double> price;
	vector<Station> route;
	string t1, t2, t3;
	while (file >> str, str != "endl") {
		if (str.size() < 20) {
			if (id != "") {
				Train temp(false, route, id, route[0].query_departure_time());
				try {
					user -> add_daily_route(temp, route[0].query_departure_time());
				}
				catch (const Exception &exc) {
					std::cout << "error: " << exc.detail << std::endl;
					return 0;
				}
			} 
			id = str;
			route.clear();
			continue;
		}
		if (str[0] == standard[0] && str[1] == standard[1] && 
			str[2] == standard[2] && str[3] == standard[3] && 
			str[4] == standard[4] && str[5] == standard[5]) {
			level.clear();
			int cnt = 0;
			for (int i = 0; i < str.size(); ++i) {
				if (str[i] == ',') {
					++cnt;
					if (cnt > 4) {
						level.push_back("");
					}
				} else {
					if (cnt > 4) {
						level[level.size() - 1] += str[i];
					}
				}
			}
			continue;
		}
		str = str + ',';
		int type = route.size() + 1, i = 0;
		string loca = get_str(str, i);
		t1 = get_str(str, i);
		t2 = get_str(str, i);
		t3 = get_str(str, i);
		if (t3[0] != '0' && t3[0] != '1' && t3[0] != '2') {
			t3 = t1;
		}
		if (t2[0] != '0' && t2[0] != '1' && t2[0] != '2') {
			t2 = t3;
		}
		Date time1(t1 + ',' + t2), time2(t1 + ',' + t3);
		int dist = get_dist(str, i);
		price.clear();
		for (; i < str.size();) {
			price.push_back(ppp(get_price(str, i), type));
		}
		/*std::cout << time1.print() << " " <<time2.print() << std::endl;
		std::cout << dist << std::endl;
		for (int j = 0; j < price.size(); ++j) {
			std::cout << price[j] << " ";
		}
		std::cout << std::endl;*/
		route.push_back(Station(loca, time1, time2, level, price, dist));
	}

	Train temp(false, route, id, route[0].query_departure_time());
	user -> add_daily_route(temp, route[0].query_departure_time());
}
