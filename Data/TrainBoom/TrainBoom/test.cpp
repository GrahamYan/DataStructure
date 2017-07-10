#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#include "../../../src/Date.hpp"
#include "../../../src/File.hpp"
#include "../../../src/User.hpp"
#include "../../../src/Train.hpp"
#include "../../../src/Station.hpp"
#include "../../../src/Tickets.hpp"
#include <string>

namespace sjtu {

using std::string;

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
    if (s == "-") {
        return 1000000000.00;
    }
    double price = 0;
    int cnt = -1;
    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == '.') {
            cnt = 0;
            continue;
        }
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
    return price;
}

/*double ppp(double price, int type) {
    if (type == 1) {
        return price;
    } else {
        return price < 0.3 ? 1000000000 : price;
    }
}*/

enum Request{Must, Optional};

void get_train_from_file(shared_ptr<User> user, const string &file_name, const Request &req) {
    AscllInput file(file_name);
    string str, last = "";
    string id = "", standard("站名");
    vector<int> left_n;
    vector<string> level;
    vector<double> price;
    vector<Station> route;
    string t1, t2, t3;
    Date start_time, finish_time;
    while (file >> str, str != "endl") {
        if (str.size() < 20) {
            if (id != "") {
                Train temp(true, route, id, start_time);
                try {
                    for (; temp.get_time() <= finish_time; temp.go_one_day()) {
                        user -> add_daily_route(temp, temp.get_time());
                    }
                }
                catch (const Exception &exc) {
                    if (req == Request::Must) {
                        throw exc;
                    }
                }
            }

            id = str;
            route.clear();
            file >> str;
            start_time = Date(str);
            file >> str;
            finish_time = Date(str);
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
            t3 = t2;
        }
        if (t2[0] != '0' && t2[0] != '1' && t2[0] != '2') {
            t2 = t3;
        }
        Date time1(t1 + ',' + t2), time2(t1 + ',' + t3);
        int dist = get_dist(str, i);
        price.clear();
        for (; i < str.size();) {
            //price.push_back(ppp(get_price(str, i), type));
            price.push_back(get_price(str, i));
        }
//std::cout << time1.print() << " " << time2.print() << std::endl;
        route.push_back(Station(loca, time1, time2, level, price, dist));
    }

    Train temp(true, route, id, start_time);
    try {
        for (; temp.get_time() <= finish_time; temp.go_one_day()) {
            user -> add_daily_route(temp, temp.get_time());
        }
    }
    catch (const Exception &exc) {
        if (req == Request::Must) {
            throw exc;
        }
    }
}

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	ifstream fin("FinalMushroom.out");
	ofstream fout("Mushroom");
	string str;
	sjtu::Date max_date;
	int total = 0;
	while (fin >> str) {
		++total;
		fout << str << " ";
		for (int i = 0; i < 12; ++i) {
			fin >> str;
			fout << str << " ";
		}
		fin >> str;
		string s = "2017-0";
		s += str[5];
		s += "-";
		if (str[str.size() - 2] == '-') {
			s += '0';
		} else {
			s += str[str.size() - 2];
		}
		s += str[str.size() - 1];
		fout << s << std::endl;	
		//std::cout << s << " " << total << std::endl;
		if (s == "2017-04-31") {
			std::cout << "wrong" << std::endl;
			return 0;
		}
		sjtu::Date temp(s);
		if (temp > max_date) {
			max_date = temp;
		}
	}
	std::cout << total << " " << max_date.print() << std::endl;
}
