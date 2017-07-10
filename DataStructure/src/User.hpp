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
#include "Log.hpp"
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
        shared_ptr<Log> local;
		
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
            local = shared_ptr<Log>(new Log());
//			train.clear();
            official_identifying_code = "lmxyy";
            //std::cout << "123213211" << std::endl;
/*if (now.check_null()) {
    std::cout << "123213211" << std::endl;
}*/
		}
		
		//deconstruction
		~User() {}
		

        shared_ptr<Log> get_local_log() {
            if (now == user.end() || !((now -> second).is_admin())) {
                local -> add_information(Date::current_time().print() + ": " + "查询系统日志失败，无权限");
                throw Exception("未登录或无管理员权限。");
            }
            local -> add_information(Date::current_time().print() + ": " + "查询系统日志成功");
            return local;
        }

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
                return string("ID: " + (now -> second).get_id() + "    名字: " + (now ->second).get_name());
            }
        }

		//普通注册
        string create_user(const string &user_name, const string &password1, const string &password2) {
			if (password1 != password2) {
                local -> add_information(Date::current_time().print() + ": " + "注册用户失败，密码不一致");
                throw Exception(string("密码不一致。"));
			}
            if (password1.length() < 6||password1.length() > 15) {
                local -> add_information(Date::current_time().print() + ": " + "注册用户失败，密码不合法");
                throw Exception("密码不合法！长度需在6到15之间。");
            }
            string user_id = get_next_user_id();
			//user[user_id] = GeneralUser(user_id, user_name, password1, 0);
			user.insert(pair<string, GeneralUser>(user_id, GeneralUser(user_id, user_name, password1, 0)));
            //login(user_id, password1);
            local -> add_information(Date::current_time().print() + ": " + "注册成功，ID为" + user_id);
			return user_id;
		}
		
		//admin注册
		string create_admin(const string &user_name, const string &password1, const string &password2, const string &identifying_code) {
			if (password1 != password2) {
                local -> add_information(Date::current_time().print() + ": " + "注册管理员失败，密码不一致");
				throw Exception("密码不一致。");
			}
//std::cout << "pwd equal" <<std::endl;
            if (password1.length() < 6||password1.length() > 15) {
                local -> add_information(Date::current_time().print() + ": " + "注册管理员失败，密码不合法");
				throw Exception("密码不合法！长度需在6到15之间。");
            }
			if (identifying_code != official_identifying_code) {
                local -> add_information(Date::current_time().print() + ": " + "注册管理员失败，验证码错误");
				throw Exception("验证码错误!你忽悠我的吧!");
			}
            string user_id = get_next_user_id();
			user.insert(pair<string, GeneralUser>(user_id, GeneralUser(user_id, user_name, password1, 1)));
            local -> add_information(Date::current_time().print() + ": " + "注册管理员成功，ID为" + user_id);
            //login(user_id, password1);
//std::cout << "build admin ok" <<std::endl;
			return user_id;
        }
		
		//login
		bool login(const string &user_id, const string &password) {
            if (now != user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "登录失败，尝试重复登录");
				throw Exception("不能重复登录。");
            }
            map<string, GeneralUser>::iterator it = user.find(user_id);
			if (it == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "登录失败，用户不存在");
				throw Exception("用户不存在。");
			}
            if ((it -> second).check_password(password)) {
                //now = &(it -> second);
                now = it;
                local -> add_information(Date::current_time().print() + ": " + user_id + "登录成功");
			} else {
                local -> add_information(Date::current_time().print() + ": " + "登录失败，密码错误");
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
                local -> add_information(Date::current_time().print() + ": " + "改验证码失败，无权限");
				throw Exception("未登录或无管理员权限。");
			}
			if (original_code != official_identifying_code) {
                local -> add_information(Date::current_time().print() + ": " + "改验证码失败，验证码检验错误");
				throw Exception("验证码检验错误。");
			}
			official_identifying_code = new_code;
            local -> add_information(Date::current_time().print() + ": " + "改验证码为" + new_code);
		}
		
        shared_ptr<vector<string> > query_station(const string &train_id, const Date &time) {
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询列车" + train_id + "," + time.print() + "失败，不存在该车");
				throw Exception("列车不存在。");
            }
            local -> add_information(Date::current_time().print() + ": " + "查询列车" + train_id + "," + time.print() + "成功");
			return (it -> second).query_station();
		}
		
		shared_ptr<vector<Tickets> > query_ticket_by_id(const string &train_id, const string &start_station, const string &finish_station, const Date &start_time, const Date &finish_time, const vector<string> &level, int number) {
            local -> add_information(Date::current_time().print() + ": " + "查询列车" + train_id + "," + start_station + "," + finish_station + "," + start_time.print() + "," + finish_time.print());
			shared_ptr<vector<Tickets> > ret(new vector<Tickets>());
			for (map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(); it != train.end(); ++it) {
				if (train_id != (it -> first).first) {
					continue;
				}
                for (int i = 0; i < (int)level.size(); ++i) {
					try {
                        shared_ptr<vector<Tickets> > ticket = (it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number);
                        for (int j = 0; j < (int)ticket -> size(); ++j) {
                            ret -> push_back((*ticket)[j]);
                        }
                        //ret -> push_back((it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number));
					}
					catch(...) {
					}
				}
			}
			return ret;
		}

        shared_ptr<vector<Tickets> >query_ticket(const string &start_time, const string &finish_time, const string &start_station, const string &finish_station, const vector<string> &level, int number) {
            local -> add_information(Date::current_time().print() + ": " + "查询列车" + start_station + "," + finish_station + "," + start_time + "," + finish_time);
			shared_ptr<vector<Tickets> > ret(new vector<Tickets>());
            for (map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(); it != train.end(); ++it) {
                //(it -> second).search();
                for (int i = 0; i < (int)level.size(); ++i) {
					try {
                        shared_ptr<vector<Tickets> > ticket = (it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number);
                        for (int j = 0; j < (int)ticket -> size(); ++j) {
                            ret -> push_back((*ticket)[j]);
                        }
                        //ret -> push_back((it -> second).get_ticket(start_station, finish_station, start_time, finish_time, level[i], number));
					}
					catch(...) {
					}
				}
			}
			return ret;
		}

        string query_name() {
            if (now == user.end()) {
                throw Exception("未登录。");
            } else {
                return (now -> second).get_name();
            }
        }

        string query_identifying_code() {
            if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).query_my_info() + "查看验证码失败，未登录");
                throw Exception("未登录。");
            }
            if (!(now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).query_my_info() + "查看验证码失败，无权限");
                throw Exception("无管理员权限");
            }
            local -> add_information(Date::current_time().print() + ": " + (now -> second).query_my_info() + "查看验证码成功");
            return official_identifying_code;
        }

        double query_money() {
            if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).query_my_info() + "查看余额失败，未登录");
                throw Exception("未登录。");
            }
            local -> add_information(Date::current_time().print() + ": " + (now -> second).query_my_info() + "查看余额成功");
            return (now -> second).query_money();
        }
		
		string query_info(const string &who) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户信息失败，未登录");
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户信息失败，" + who + "不存在");
				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + "查询" + who + "的信息成功");
				return (it -> second).query_my_info();
			} else {
                local -> add_information(Date::current_time().print() + ": " + "查询用户信息失败，权限不足");
				throw Exception("权限不足。");
			}
		}
		
		shared_ptr<vector<Tickets> > query_my_tickets(const string &who) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户车票失败，未登录");
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户车票失败，" + who + "不存在");

				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + "查询" + who + "的车票成功");
				return (it -> second).query_my_tickets();
			} else {
                local -> add_information(Date::current_time().print() + ": " + "查询用户车票失败，权限不足");
				throw Exception("权限不足。");
			}
		}
		
		shared_ptr<Log> query_log(const string &who, const GeneralUser::LogType &type) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户日志失败，未登录");
				throw Exception("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "查询用户日志失败，" + who + "不存在");
				throw Exception("用户不存在。");
			}
			if (who == (now -> second).get_id() || !((it -> second).is_admin()) && (now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + "查询" + who + "的日志成功");
				return (it -> second).query_log(type);
			} else {
                local -> add_information(Date::current_time().print() + ": " + "查询用户日志失败，权限不足");
				throw Exception("权限不足。");
			}
		}
		
		bool modify_name(const string &new_name) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "修改用户名失败，未登录");
                throw Exception("未登录。");
			} else {
				if (new_name.size() == 0 || new_name.size() > 15) {
                    local -> add_information(Date::current_time().print() + ": " + "修改用户名失败，名字过长");
					throw Exception("名字过长。");
				}
				(now -> second).modify_name(new_name);
                local -> add_information(Date::current_time().print() + ": " + "修改" + (now -> second).get_id() + "的用户名为" + new_name);
				return true;
			}
		}
		
		bool modify_password(const string &original_password, const string &new_password1, const string &new_password2) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "修改密码失败，未登录");
				throw Exception("未登录。");
			}
			if (!((now -> second).check_password(original_password))) {
                local -> add_information(Date::current_time().print() + ": " + "修改密码失败，验证错误");
				throw Exception("密码验证错误。");
			}
			if (new_password1 != new_password2) {
                local -> add_information(Date::current_time().print() + ": " + "修改密码失败，前后不一致");
				throw Exception("前后密码不一致。");
			} else {
				if (new_password1.size() > 15 || new_password1.size() < 6) {
                    local -> add_information(Date::current_time().print() + ": " + "修改密码失败，长度不合法");
					throw Exception("密码不合法！长度需在6到15之间。");
				} else {
					(now -> second).modify_password(new_password1);
                    local -> add_information(Date::current_time().print() + ": " + "修改" + (now -> second).get_id() + "的密码为" + new_password1);
				}
			}
		}
		
		bool charge(double money) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "充值失败，未登录");
				throw Exception("未登录。");
			}
            //std::cout << "充值 " << money << std::endl;
            (now -> second).charge(money);
            local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "充值" + double_to_string(money) + "元");
			return true;
		}
		
		bool buy_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "购票失败，未登录");
				throw Exception("未登录。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "购票失败，列车不存在");
				throw Exception("列车不存在。");
			}
			try {
				if ((now -> second).buy_ticket(it, train_id, start_station, finish_station, level, number)) {
                    //std::cout << ((now ->second).get_name()) << "购买成功" << std::endl;
                    local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id()
                                             + string("购买 ") + string("时间为 ") + time.print()
                                             + string(" 车次为 ") + train_id
                                             + string(" 从 ") + start_station
                                             + string(" 到 ") + finish_station
                                             + string(" 的") + std::to_string(number)
                                             + string("张") + level + string("票"));
					return true;
				} else {
                    local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "购票失败");
					throw Exception("购买失败。");
				}
			}
            catch(const Exception &exp) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "购票失败，" + exp.detail);
				throw exp;
            }
			return false;
		}
		
		bool refund_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
            if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + "退购失败，未登录");
				throw Exception("未登录。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
                local -> add_information(Date::current_time().print() + ": " + "退购失败，列车不存在");
				throw Exception("列车不存在。");
			}
			try {
				if ((now -> second).refund_ticket(it, train_id, start_station, finish_station, level, number)) {
                    local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id()
                                             + string("退购 ") + string("时间为 ") + time.print()
                                             + string(" 车次为 ") + train_id
                                             + string(" 从 ") + start_station
                                             + string(" 到 ") + finish_station
                                             + string(" 的") + std::to_string(number)
                                             + string("张") + level + string("票"));
					return true;
				} else {
                    local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "退购失败");
					throw Exception("退票失败。");
				}
			}
            catch(const Exception &exp) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "退购失败，" + exp.detail);
				throw exp;
			}
			return false;
		}

        enum CheckExist{Must, Opt};
		
        bool add_daily_route(Train _train, const Date &date, const CheckExist &checkexist) {
            if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "加车失败，未登录");
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "加车失败，无管理员权限");
				throw Exception("无管理员权限。");
            }
			string train_id = _train.get_id();
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(), it2 = it;
            Date down(_train.get_time().get_year(), _train.get_time().get_month(), _train.get_time().get_day(), 0, 0);
            Date up(date.get_year(), date.get_month(), date.get_day(), 23, 59);
            if (checkexist == CheckExist::Must) {
                for (; it != train.end(); ++it) {
                    if ((it -> second).get_id() == train_id && (it -> second).get_time() >= down && (it -> second).get_time() <= up) {
                        local -> add_information(Date::current_time().print() + ": "
                                                 + (now -> second).get_id() + "加车失败，"
                                                 + _train.get_time().print() + "到"
                                                 + date.print() + "内已有该车");
                        throw Exception("所给时间内已有该车");
                    }
                }
            }
            for (; _train.get_time() <= date; _train.go_one_day()) {
                train[pair<string, Date>(train_id, _train.get_time())] = _train;
			}
            local -> add_information(Date::current_time().print() + ": "
                                     + (now -> second).get_id() + "加车成功，从"
                                     + _train.get_time().print() + "到"
                                     + date.print());
			return true;
		}
		
		/*bool delete_daily_route(const Train &_train, const Date &finish_time) {
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
					if (it2)
					train.erase(it2);
				}
			}
			return true;
		}*/
		
		bool delete_daily_route(const string &train_id, const Date &start_time, const Date &finish_time) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "删车失败，未登录");
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "删车失败，无管理员权限");
				throw Exception("无管理员权限。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin();
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second <= finish_time && (it -> second).check_empty()) {
					train.erase(it);
				}
			}
            local -> add_information(Date::current_time().print() + ": "
                                     + (now -> second).get_id() + "删车成功，从"
                                     + start_time.print() + "到"
                                     + finish_time.print());
			return true;
		}
		
		bool start_daily_sale(const string &train_id, const Date &start_time, const Date &finish_time) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "开始发售车票失败，未登录");
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "开始发售车票失败，无管理员权限");
				throw Exception("无管理员权限。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin();
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second  <= finish_time) {
					(it -> second).start_sale();
				}
			}
            local -> add_information(Date::current_time().print() + ": "
                                     + (now -> second).get_id() + "开始售票成功，从"
                                     + start_time.print() + "到"
                                     + finish_time.print());
			return true;
		}
		
		bool finish_daily_sale(const string &train_id, const Date &start_time, const Date &finish_time) {
			if (now == user.end()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "停止发售车票失败，未登录");
				throw Exception("未登录。");
			}
			if (!(now -> second).is_admin()) {
                local -> add_information(Date::current_time().print() + ": " + (now -> second).get_id() + "停止发售车票失败，无管理员权限");
				throw Exception("无管理员权限。");
			}
			map<pair<string, Date>, Train, Compare_Date>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if ((it -> first).first == train_id && (it -> first).second >= start_time && (it -> first).second  <= finish_time) {
					(it -> second).finish_sale();
				}
			}
            local -> add_information(Date::current_time().print() + ": "
                                     + (now -> second).get_id() + "停止售票成功，从"
                                     + start_time.print() + "到"
                                     + finish_time.print());
			return true;
		}
		
		/*bool start_daily_sale(const Train &_train, const Date &finish_time) {
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
		}*/
		
        
	};

}

#endif


