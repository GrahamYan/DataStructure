#ifndef SJTU_LOG_HPP
#define SJTU_LOG_HPP

#include "lib/vector.hpp"
#include "lib/ptr.hpp"
#include "Date.hpp"
#include "Tickets.hpp"
#include "Train.hpp" 
#include <string>

using std::string;

namespace sjtu {

    inline string double_to_string(double x) {
        if (x < 1e-5 && x > -1e-5) {
            return "0.00";
        }
        string ret = "";
        if (x < 0.0) {
            ret += "-";
            x = -x;
        }
        int a = int(x * 100) / 100;
        x -= a;
        if (x < 0) {
            x += 1;
            a -= 1;
        }
        ret += std::to_string(a) + ".";
        int y = int(x * 100) / 100;
        ret += y < 10 ? "0" + std::to_string(y) : std::to_string(y);
        return ret;
    }
	
	class Log {
		private:
			vector<string> information;
			inline int get_pos(const string &obj) {
				for (int i = 0; i < (int)obj.size(); ++i) {
					if (obj[i] == ':' && obj[i + 1] == ' ') {
						return i;
					}
				}
			}
			inline bool check_type(int i, const string &str) {
                int j = get_pos(information[i]) + 2;
                if ((int)information[i].size() < j + (int)str.size() - 1) {
                    //std::cout << "length short" << std::endl;
					return false;
				}
//				bool flag = true;
                for (int k = 0; k < (int)str.size(); ++k) {
					if (str[k] != information[i][k + j]) {
						return false;
					}
				}
				return true;	
			}
		public:
			Log() {}
			Log(const Log &rhs): information(rhs.information) {
			}
			inline int size() {
				return information.size();
			}
            inline string &operator [](int index) {
                if (index < 0 || index >= (int)information.size()) {
                    throw Exception("Log下标越界");
                }
				return information[index];
			}
			shared_ptr<Log> buy_log() {
				int sz = information.size();
				string str("购买");
				shared_ptr<Log> ret(new Log());
				for (int i = 0;i < sz; ++i) {
                    //std::cout << information[i] << " " << check_type(i, str) << " " << std::endl;
                    if (check_type(i, str)) {
						ret -> add_information(information[i]);
                    }
				}
				return ret;
			}
			shared_ptr<Log> refund_log() {
				int sz = information.size();
				string str("退购");
				shared_ptr<Log> ret(new Log());
				for (int i = 0;i < sz; ++i) {
					if (check_type(i, str)) {
						ret -> add_information(information[i]);
					}
				}
				return ret;
			}
			shared_ptr<Log> buy_refund_log() {
				int sz = information.size();
				string str1("购买");
				string str2("退购");
				shared_ptr<Log> ret(new Log());
				for (int i = 0;i < sz; ++i) {
                    if (check_type(i, str1) || check_type(i, str2)) {
						ret -> add_information(information[i]);
					}
				}
				return ret;
			}
			shared_ptr<Log> charge_log() {
				int sz = information.size();
				string str("充值");
				shared_ptr<Log> ret(new Log());
				for (int i = 0;i < sz; ++i) {
					if (check_type(i, str)) {
						ret -> add_information(information[i]);
					}
				}
				return ret;
			}
			inline void add_information(const string &obj) {
				information.push_back(obj);
			}
			void modify_name(const Date &now, const string &new_name) {
				string str = now.print() + ": " + string("更改用户名为 ") 
								+ new_name; 
				information.push_back(str);
			}
			void modify_password(const Date &now, const string &new_password) {
				string str = now.print() + ": " +string("更改密码为 ")
								 + new_password;
				information.push_back(str);
			}
			void buy_tickets(const Date &now, const Tickets &new_tickets) {
                string str = now.print() + ": " + string("购买 ")
                                                                + string("时间为 ") + new_tickets.query_departure_date().print()
								+ string(" 车次为 ") + new_tickets.query_id()
								+ string(" 从 ") + new_tickets.query_start_station() 
								+ string(" 到 ") + new_tickets.query_finish_station()
								+ string(" 的") + std::to_string(new_tickets.query_number())
								+ string("张") + new_tickets.query_level() + string("票")
                                + string("，共计") + double_to_string(new_tickets.query_price() * new_tickets.query_number())
								+ string("元");
                information.push_back(str);
			}
            void refund_tickets(const Date &now, const Tickets &new_tickets) {
				string str = now.print() + ": " + string("退购 ")
                                                                + string("时间为 ") + new_tickets.query_departure_date().print()
								+ string(" 车次为 ") + new_tickets.query_id()
								+ string(" 从 ") + new_tickets.query_start_station()
								+ string(" 到 ") + new_tickets.query_finish_station()
								+ string(" 的") + std::to_string(new_tickets.query_number())
								+ string("张") + new_tickets.query_level() + string("票")
                                + string("，共计") + double_to_string(new_tickets.query_price() * new_tickets.query_number())
								+ string("元"); 
				information.push_back(str);
			}
			void charge(const Date &now, double money) {
				string str = now.print() + ": " + string("充值 ")
                                + string("金额为 ") + double_to_string(money)
								+ string("元"); 
				information.push_back(str);
			}
			void add_daily_route(const Date &now, const Train &new_train, const Date &finish_time) {
				string str = now.print() + "-" + finish_time.print() + ": " + string("增开 ")
								+ string("开车时间为 ") + new_train.get_time().print()
								+ string("车次为 ") + new_train.get_id() 
								+ string("的列车");
				information.push_back(str);
			}
			void delete_daily_route(const Date &now, const Train& new_train, const Date &finish_time) {
				string str = now.print() + "-" + finish_time.print() + ": " + string("增开 ")
								+ string("开车时间为 ") + new_train.get_time().print()
								+ string("车次为 ") + new_train.get_id()
								+ string("的列车"); 
				information.push_back(str);
			}
			void start_daily_sale(const Date &now, const Train& new_train, const Date &finish_time) {
				string str = now.print() + "-" + finish_time.print() + ": " + string("发售 ")
								+ string("开车时间为") + new_train.get_time().print()
								+ string("车次为 ") + new_train.get_id()
								+ string("的列车");
				information.push_back(str);
			}
			void finish_daily_sale(const Date &now, const Train& new_train, const Date &finish_time) {
				string str = now.print() + "-" + finish_time.print() + ": " + string("停止发售 ")
								+ string("开车时间为") + new_train.get_time().print()
								+ string("车次为 ") + new_train.get_id()
								+ string("的列车"); 
				information.push_back(str);
			}
		
	};
} 
#endif
