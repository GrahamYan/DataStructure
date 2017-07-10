#ifndef SJTU_TICKET_HPP
#define SJTU_TICKET_HPP

#include<iostream>
#include<string>
#include"lib/ptr.hpp"
#include"Date.hpp"
//#include "GeneralUser.hpp"

using std::string;

namespace sjtu {
	
class Tickets{
	//friend class GeneralUser;
	private:
		string train_id;
		Date departure_time;
		string start_station;
		string finish_station;
		string level;
		int number;
		double price;
		
	public:
		Tickets(const string &ti ,const Date &d,const string &ss,const string &fs,const string &l,int n,double p)
			:train_id(ti),departure_time(d),start_station(ss),finish_station(fs),level(l),number(n),price(p){}
	// {
	// 		train_id = ti;
	// 		departure_time = d;
	// 		start_station = ss;
	// 		finish_station = fs;
	// 		level = l;
	// 		number = n;
	// 		price = p;
	// 	}

	//默认拷贝构造和赋值
	
		// Tickets(const Tickets &obj) {
		// 	train_id = obj.train_id;
		// 	departure_time = obj.departure_time;
		// 	start_station = obj.start_station;
		// 	finish_station = obj.finish_station;
		// 	level = obj.level;
		// 	number = obj.number;
		// 	price = obj.price;
		// }
		// Tickets &operator = (const Tickets &obj) {
		// 	train_id = obj.train_id;
		// 	departure_time = obj.departure_time;
		// 	start_station = obj.start_station;
		// 	finish_station = obj.finish_station;
		// 	level = obj.level;
		// 	number = obj.number;
		// 	price = obj.price;
			
		// 	return *this;
		// }
		bool operator == (const Tickets &obj) {
			if (train_id == obj.train_id && departure_time == obj.departure_time && start_station == obj.start_station && finish_station == obj.finish_station && level == obj.level) {
				return true;
			}
			else return false;
		}
		bool operator != (const Tickets &obj) {
			if (train_id == obj.train_id && departure_time == obj.departure_time && start_station == obj.start_station && finish_station == obj.finish_station && level == obj.level) {
				return false;
			}
			else return true;
		}
        bool operator < (const Tickets &obj)const {
			if (train_id < obj.train_id) {
				return true;
			}
			else if (train_id == obj.train_id) {
				if (departure_time < obj.departure_time) {
					return true;
				}
				else if (departure_time == obj.departure_time) {
					if (start_station < obj.start_station) {
						return true;
					}
					else if (start_station == obj.start_station) {
						if (finish_station < obj.finish_station) {
							return true;
						}
						else if (finish_station == obj.finish_station) {
							if (level < obj.level) {
								return true;
							}
							else {
								return false;
							}
						}
					}	
				}
			}
			return false;
		}
		void set_price(double p) {
			price = p;
		}
		double query_price() const {
			return price;
		}
		string query_id() const {
			return train_id;
		}
		int query_number() const {
			return number;
		} 
		/*inline void modify_number(int delta) {
			number += delta;
		}*/
		Date query_date() const {
			return departure_time;
		}
		string query_level() const {
			return level;
		}
		string query_start_station() const {
			return start_station;
		}
		string query_finish_station() const {
			return finish_station;
		}
		bool modify_number (int delta) {
			if (number + delta >= 0) {
				number += delta;
				return true;
			}
			else return false;
		}
};
}

#endif 
