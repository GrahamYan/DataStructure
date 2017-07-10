//初始化now_id(long long sjtu::User::now_id = 0)

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "File.hpp"
#include "Exceptions.hpp"
#include "GeneralUser.hpp"
#include "Date.hpp"
//#include "Admin.hpp"
#include "lib/map.hpp"
#include "lib/pair.hpp"
#include "lib/ptr.hpp"
#include <string>
#include <cassert>
#include <iostream>
//#include "Train.hpp"

using std::string;
//using sjtu::InconsistentPassword;
namespace sjtu {

	
	class User {
		long long now_id;
		//shared_ptr<GeneralUser> now;
		map<string, GeneralUser>::iterator now;
		map<string, GeneralUser> user;
        map<pair<string, Date>, Train, Compare_Date> train;
        string official_identifying_code;
		
		//下一个合法user_id
		string get_next_user_id() {
			while (user.find(std::to_string(now_id)) != user.end()) {
				now_id++;
			}
			return std::to_string(now_id);
		}
		
	public:
		//construction
		User() {
            //std::cout << "123213211" << std::endl;
			now_id = 0;
			now = user.end();
			user.clear();
//			train.clear();
            official_identifying_code = "lmxyy";
            //std::cout << "123213211" << std::endl;
/*if (now.check_null()) {
    std::cout << "123213211" << std::endl;
}*/
		}
		
		//deconstruction
		~User() {}
		

        bool check_login() {
            return now != user.end();
        }

        /*bool check_exist(const string &id, const string &pwd) {
            map<string, GeneralUser>::iterator it = user.find(id);
            if ((it != user.end()) && ((it -> second).password == pwd)) {
                return true;
            } else {
                return false;
            }
        }*/

        const string query_now_id() {
            if (now != user.end()) {
                return string("ID: " + (now -> second).get_id() + "  名字: " + (now ->second).get_name());
            }
        }
		//普通注册
		string create_user(const string &user_name, const string &password1, const string &password2) {
			if (password1 != password2) {
                throw Exception(string("密码不一致。"));
			}
			if (password1.length() < 6||password1.length() > 15)
                throw Exception("密码不合法！长度需在6到15之间。");
            string user_id = get_next_user_id();
			//user[user_id] = GeneralUser(user_id, user_name, password1, 0);
			user.insert(pair<string, GeneralUser>(user_id, GeneralUser(user_id, user_name, password1, 0)));
            //login(user_id, password1);
			return user_id;
		}
		
		//admin注册
		string create_admin(const string &user_name, const string &password1, const string &password2, const string &identifying_code) {
			if (password1 != password2) {
				throw Exception("密码不一致。");
			}
			if (password1.length() < 6||password1.length() > 15)
				throw Exception("密码不合法！长度需在6到15之间。");
			if (identifying_code != official_identifying_code) {
				throw Exception("验证码错误!你忽悠我的吧!");
			}
            string user_id = get_next_user_id();
			user.insert(pair<string, GeneralUser>(user_id, GeneralUser(user_id, user_name, password1, 1)));
            //login(user_id, password1);
			return user_id;
        }
		
		//login
		bool login(const string &user_id, const string &password) {
            if (now != user.end()) {
				throw Exception("不能重复登录。");
            }
            map<string, GeneralUser>::iterator it = user.find(user_id);
			if (it == user.end()) {
				throw Exception("用户不存在。");
			}
            if ((it -> second).check_password(password)) {
                //now = &(it -> second);
                now = it;
			} else {
				throw Exception("密码错误。");
			}
			return true;
		}
		
		//logout
        void logout() {
            now = user.end();
		}
		
		//改验证码
		void set_identifying_code(const string &original_code, const string &new_code) {
			if (now == user.end() || !((now -> second).is_admin())) {
				throw Exception("未登录或无管理员权限。");
			}
			if (original_code != official_identifying_code) {
				throw Exception("验证码检验错误。");
			}
			official_identifying_code = new_code;
		}
		
        shared_ptr<vector<string> > query_station(const string &train_id, const Date &time) {
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw Exception("列车不存在。");
			}
			return (it -> second).query_station();
		}
		
		shared_ptr<vector<Tickets> > query_ticket_by_id(const string &train_id, const string &start_station, const string &finish_station, const Date &start_time, const Date &finish_time, const vector<string> &level, int number) {
			shared_ptr<vector<Tickets> > ret(new vector<Tickets>());
			for (map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(); it != train.end(); ++it) {
				if (train_id != (it -> first).first) {
					continue;
				}
				for (int i = 0; i < level.size(); ++i) {
					try {
						ret -> push_back((it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number));
					}
					catch(...) {
					}
				}
			}
			return ret;
		}
		
		shared_ptr<vector<Tickets> >query_ticket(const string &start_time, const string &finish_time, const string &start_station, const string &finish_station, const vector<string> &level, int number) {
			shared_ptr<vector<Tickets> > ret(new vector<Tickets>());
			for (map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(); it != train.end(); ++it) {
				for (int i = 0; i < level.size(); ++i) {
					try {
						ret -> push_back((it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number));
					}
					catch(...) {
					}
				}
			}
			return ret;
		}
		
		string query_info(const string &who) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
				return (it -> second).query_my_info();
			} else {
				throw Exception("权限不足。");
			}
		}
		
		shared_ptr<vector<Tickets> > query_my_tickets(const string &who) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
				return (it -> second).query_my_tickets();
			} else {
				throw Exception("权限不足。");
			}
		}
		
		shared_ptr<Log> query_log(const string &who, const GeneralUser::LogType &type) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
				return (it -> second).query_log(type);
			} else {
				throw Exception("权限不足。");
			}
		}
		
		bool modify_name(const string &new_name) {
			if (now == user.end()) {
				throw Exception("未登录。");
			} else {
				if (new_name.size() == 0 || new_name.size() > 15) {
					throw Exception("名字过长。");
				}
				(now -> second).modify_name(new_name);
				return true;
			}
		}
		
		bool modify_password(const string &original_password, const string &new_password1, const string &new_password2) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			if (!((now -> second).check_password(original_password))) {
				throw Exception("密码验证错误。");
			}
			if (new_password1 != new_password2) {
				throw Exception("前后密码不一致。");
			} else {
				if (new_password1.size() > 15 || new_password1.size() < 6) {
					throw Exception("密码不合法！长度需在6到15之间。");
				} else {
					(now -> second).modify_password(new_password1);
				}
			}
		}
		
		bool charge(double money) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			(now -> second).charge(money);
			return true;
		}
		
		bool buy_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw Exception("列车不存在。");
			}
			try {
				if ((now -> second).buy_ticket(it, train_id, start_station, finish_station, level, number)) {
					return true;
				} else {
					throw Exception("购买失败。");
				}
			}
			catch(const Exception &exp) {
				throw exp;
			}
			return false;
		}
		
		bool refund_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw Exception("列车不存在。");
			}
			try {
				if ((now -> second).refund_ticket(it, train_id, start_station, finish_station, level, number)) {
					return true;
				} else {
					throw Exception("退票失败。");
				}
			}
			catch(const Exception &exp) {
				throw exp;
			}
			return false;
		}
		
		bool add_daily_route(const Train &_train, const Date &date) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
				throw Exception("无管理员权限。");
			}
			string train_id = _train.get_id();
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(), it2 = it;
			for (; it != train.end() && (it -> first).first != train_id; ++it);
			
			for (Date tmp = _train.get_time(); tmp <= date; tmp.go_one_day()) {
				while (it != train.end()) {
					it2 = it;
					++it2;
					//if (it2 != train.end() && (it2 -> first).first == train_id && (it2 -> first).second < tmp) {
					if (it2 != train.end() && it2 -> first < pair<string, Date>(train_id, tmp)) {
						++it;
						continue;
					} else {
						break;
					}
				}
				if (it == train.end()) {
					train[pair<string, Date>(train_id, tmp)] = Train(_train, tmp);
				} else {
					it2 = it;
					++it2;
					if ((it -> first).first == train_id && tmp.is_same_day((it -> first).second) || it2 != train.end() && (it2 -> first).first == train_id && tmp.is_same_day((it2 -> first).second)) {
						continue;
					} else {
						train[pair<string, Date>(train_id, tmp)] = Train(_train, tmp);
					}
				}
			}
			return true;
		}
		
		bool delete_daily_route(const Train &_train, const Date &finish_time) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
				throw Exception("无管理员权限。");
			}
			string train_id = _train.get_id();
			Date start_time = _train.get_time();
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second <= finish_time) {
					it2 = it;
					it++;
					train.erase(it2);
				}
			}
			return true;
		}
		
		bool start_daily_sale(const Train &_train, const Date &finish_time) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
				throw Exception("无管理员权限。");
			}
			string train_id = _train.get_id();
			Date start_time = _train.get_time();
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin();
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second  <= finish_time) {
					(it -> second).start_sale();
				}
			}
			return true;
		}
		
		bool finish_daily_sale(const Train &_train, const Date &finish_time) {
			if (now == user.end()) {
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
				throw Exception("无管理员权限。");
			}
			string train_id = _train.get_id();
			Date start_time = _train.get_time();
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second  <= finish_time) {
					(it -> second).finish_sale();
				}
			}
			return true;
		}
		
        
	};

}

#endif


