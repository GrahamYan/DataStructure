#ifndef	SJTU_STATION_HPP
#define SJTU_STATION_HPP

#include <string>
#include "Date.hpp"
#include "lib/pair.hpp"
#include "lib/vector.hpp"

using std::string;

namespace sjtu {
	
	class Station {
	public:
		const static int MAXN = 2000;
		struct Node {
			double price;
			string level;
			int left_n;
			Node(double _price, const string &_level, int _left_n): 
				price(_price), level(_level), left_n(_left_n) {
			}
		};
	
	private:		
		string location;
		Date arrival_time, departure_time;
		vector<Node> types;
		int dist;
		
	public:
		Station(const string &_location, const Date &_arrival_time, const Date &_departure_time, const vector<Node> &_types, int _dist): 
			location(_location), arrival_time(_arrival_time), 
			departure_time(_departure_time), types(_types), dist(_dist) {
		}
		Station(const string &_location, const Date &_arrival_time, const Date &_departure_time, const vector<string> &_type, const vector<double> &_price, int _dist): 
			location(_location), arrival_time(_arrival_time), 
			departure_time(_departure_time), dist(_dist) {
			types.clear();
			for (int i = 0; i < (int)_price.size(); ++i) {
				types.push_back(Node(_price[i], _type[i], MAXN));
			}
		}
		
		const string query_location() const {
			return location;
		}
		
		const Date query_arrival_time() const {
			return arrival_time;
		}
		
		const Date query_departure_time() const {
			return departure_time;
		}
		
		const int query_single_number(const string &request) const {
			for (int i = 0; i < types.size(); ++i) {
				if (types[i].level == request) {
					return types[i].left_n;
				}
			}
            throw Exception("未找到" + request + "票");
		}
		
		const double query_single_price(const string &request) const {
			for (int i = 0; i < types.size(); ++i) {
				if (types[i].level == request) {
					return types[i].price;
				}
			}
            throw Exception("未找到" + request + "票");
		}
		
		vector<Node> query_types() {
			return types;
		}
		
		vector<double> query_specified_price(const vector<string> &request) {
			vector<double> ret;
			for (int i = 0; i < (int)request.size(); ++i) {
				try {
					ret.push_back(query_single_price(request[i]));
				} 
                catch (const Exception &exp) {
					throw exp;
				}
			}
			return ret;
		}
		
		const bool is_same_location(const string &another) const {
			for (int i = 0; i < 6 && i < location.size() && i < another.size(); ++i) {
				if (another[i] != location[i]) {
					return false;
				}
			}
			return true;
		}
		
		const bool modify_number(const string &request, int delta) {
			for (int i = 0; i < types.size(); ++i) {
				if (types[i].level == request) {
					types[i].left_n += delta;
					return true;
				}
			}
            throw Exception("未找到" + request + "票");
			return false;
		}
	};
	
}

#endif
