#ifndef SJTU_TICKET_HPP
#define SJTU_TICKET_HPP

#include<iostream>
#include<string>
#include"lib/ptr.hpp"
#include"date.hpp"

using std::string;

namespace sjtu {
	
class ticket{
	private:
		string train_id;
		date departure_time;
		string start_station;
		string finish_station;
		string level;
		int number;
		double price;
		
	public:
		ticket (string ti , date d , string ss , string fs , string l , int n , double p) {
			train_id = ti;
			departure_time = d;
			start_station = ss;
			finish_station = fs;
			level = l;
			number = n;
			price = p;
		}
		ticket (const ticket &obj) {
			train_id = obj.train_id;
			departure_time = obj.departure_time;
			start_station = obj.start_station;
			finish_station = obj.finish_station;
			level = obj.level;
			number = obj.number;
			price = obj.price;
		}
		ticket &operator = (const ticket &obj) {
			train_id = obj.train_id;
			departure_time = obj.departure_time;
			start_station = obj.start_station;
			finish_station = obj.finish_station;
			level = obj.level;
			number = obj.number;
			price = obj.price;
			
			return *this;
		}
/*		bool operator == (const ticket &obj) {
			if (train_id == obj.train_id && departure_time == obj.departure_time && strat_station == obj.start_station && finish_station == obj.finish_station && level == obj.level) {
				return true;
			}
			else return false;
		}
		bool operator != (const ticket &obj) {
			if (train_id == obj.train_id && departure_time == obj.departure_time && start_station == obj.start_station && finish_station == obj.finish_station && level == obj.level) {
				return false;
			}
			else return true;
		}*/
		bool operator < (ticket &obj) {
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
		const int query_number() {
			return number;
		} 
		const date query_date() {
			return departure_time;
		}
		const string query_level() {
			return level;
		}
		const string query_start_station() {
			return start_station;
		}
		const string query_finish_station() {
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
