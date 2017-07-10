//初始化now_id(long long sjtu::User::now_id = 0)

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "File.hpp"
#include "Exception.hpp"
#include "GeneralUser.hpp"
#include "Admin.hpp"
#include "lib/map.hpp"
#include "lib/pair.hpp"
#include "ptr.hpp"

using std::string;
namespace sjtu {
	
	class User {
		long long now_id;
		shared_ptr<GeneralUser> now;
		map<string, GeneralUser> user;
		map<pair<string, Date>, Train> train;
		string official_idenfitying_code;
		
		//下一个合法user_id
		long long get_next_user_id() {
			while (user.find(to_string(now_id)) != user.end()) {
				now_id++;
			}
			return now_id;
		}
		
	public:
		//construction
		User() {
			now_id = 0;
			now = nullptr;
			user.clear();
			train.clear();
			official_identifying_code = "";
		}
		
		//deconstruction
		~User() {}
		
		//普通注册
		string regigster(const string &user_name, const string &password1, const string &password2) {
			if (password1 != password2) {
				throw InconsistentPassword("密码不一致。");
			}
			if (password1.length() < 6||password1.length() > 15)
				throw PasswordIsNotValid("密码不合法！长度需在6到15之间。");
			LL user_id = get_next_user_id();
			now[user_id] = GeneralUser(user_id, user_name, password1, 0);
			login(user_id, password1);
			return user_id;
		}
		
		//admin注册
		string admin_regigster(const string &user_name, const string &password1, const string &password2, const string &identifying_code) {
			if (password1 != password2) {
				throw InconsistentPassword("密码不一致。");
			}
			if (password1.length() < 6||password1.length() > 15)
				throw PasswordIsNotValid("密码不合法！长度需在6到15之间。");
			if (identifying_code != official_identifying_code) {
				throw WrongIdentifyingCode("验证码错误。");
			}
			LL user_id = get_next_user_id();
			now[user_id] = GeneralUser(user_id, user_name, password1, 1);
			login(user_id, password1);
			return user_id;
		}
		
		//login
		bool login(const string &user_id, const string &password) {
			if (!now) {
				throw AlreadyLogin("不能重复登录。");
			}
			map<string, GeneralUser>::iterator it = M.find(user_id);
			if (it == M.end()) {
				throw UserNotExist("用户不存在。");
			}
			if (it -> second -> check_password(password)) {
				now = it -> second;
			} else {
				throw WrongPassword("密码错误。");
			}
			return true;
		}
		
		//logout
		void logout(const string &user_id, const string &password) {
			now = nullptr;
			//return true;
		}
		
		//改验证码
		void set_identifying_code(const string &original_code, const string &new_code) {
			if (now == nullptr || !(now -> is_admin())) {
				throw NotAdmin("未登录或无管理员权限。");
			}
			if (original_code != official_identifying_code) {
				throw WrongIdentifyingCode("验证码检验错误。");
			}
			official_identifying_code = new_code;
		}
		
		shared_ptr<vector<string> > query_station(const string &train_id, const Date &time) {
			map<pair<string, Date>, Train>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw TrainNotExist("列车不存在。");
			}
			return it -> query_station();
		}
		
		shared_ptr<vector<Tickets> > query_ticket_by_id(const string &train_id, const string &start_station, const string &finish_station, const Date &start_time, const Date &finish_time, const vector<string> &level, int number) {
			vector<Tickets> ret;
			ret.clear();
			for (map<pair<string, Date>, Train>::iterator it = train.begin(); it != train.end(); ++it) {
				if (train_id != it -> first -> first) {
					continue;
				}
				try {
					ret.push_back(it -> second -> get_ticket(start_station, finish_station, start_time, finish_time, level, number));
				}
				catch(...) {
				}
			}
			return ret;
		}
		
		shared_ptr<vector<Tickets> >query_ticket(const string &start_time, const string &finish_time, const string &start_station, const string &finish_station, const vector<string> &level, int number) {
			vector<Tickets> ret;
			ret.clear();
			for (map<pair<string, Date>, Train>::iterator it = train.begin(); it != train.end(); ++it) {
				try {
					ret.push_back(it -> second -> get_ticket(start_station, finish_station, start_time, finish_time, level, number));
				}
				catch(...) {
				}
			}
			return ret;
		}
		
		string query_info(const string &who) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw UserNotExist("用户不存在。");
			}
			if (who == now.get_id() || !(it -> second -> is_admin) && now -> !(is_admin)) {
				return it -> second -> query_my_info();
			} else {
				throw InsufficientPriviledge("权限不足。");
			}
		}
		
		shared_ptr<vector<Tickets> > query_my_tickets(const string &who) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw UserNotExist("用户不存在。");
			}
			if (who == now.get_id() || !(it -> second -> is_admin) && now -> !(is_admin)) {
				return it -> second -> query_my_tickets();
			} else {
				throw InsufficientPriviledge("权限不足。");
			}
		}
		
		shared_ptr<Log> query_log(const string &who, const GeneralUser::LogType &type) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			map<string, GeneralUser>::iterator it = user.find(who);
			if (it == user.end()) {
				throw UserNotExist("用户不存在。");
			}
			if (who == now.get_id() || !(it -> second -> is_admin) && now -> !(is_admin)) {
				return it -> second -> query_log();
			} else {
				throw InsufficientPriviledge("权限不足。");
			}
		}
		
		bool modify_name(const string &new_name) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			} else {
				if (new_name.size() == 0 || new_name.size() > 15) {
					throw NameTooLong("名字过长。");
				}
				now -> modify_name(new_name);
				return true;
			}
		}
		
		bool modify_password(const string &original_password, const string &new_password1, const string &new_password2) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			if (!(now -> check_password(original_password))) {
				throw InconsistentPassword("密码验证错误。");
			}
			if (new_password1 != new_password2) {
				throw InconsistentPassword("前后密码不一致。");
			} else {
				if (new_password1.size() > 15 || new_password1.size() < 6) {
					throw PasswordIsNotValid("密码不合法！长度需在6到15之间。");
				} else {
					now -> modify_password(new_password1);
				}
			}
		}
		
		bool charge(double money) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			now -> charge(money);
			return true;
		}
		
		bool buy_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			map<pair<string, Date>, Train>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw TrainNotExist("列车不存在。");
			}
			try {
				if (now -> buy_ticket(shared_ptr<Train>((it -> second)), train_id, start_station, finish_station, level, number)) {
					return true;
				} else {
					throw FailBuy("购买失败。");
				}
			}
			catch(NotUser exp) {
				throw exp;
			}
			return false;
		}
		
		bool refund_ticket(const string &train_id, const Date &time, const string &start_station, const string &finish_station, const string &level, int number) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			map<pair<string, Date>, Train>::iterator it = train.find(pair<string, Date>(train_id, time));
			if (it == train.end()) {
				throw TrainNotExist("列车不存在。");
			}
			try {
				if (now -> refund_ticket(shared_ptr<Train>((it -> second)), train_id, start_station, finish_station, level, number)) {
					return true;
				} else {
					throw Failrefund("退票失败。");
				}
			}
			catch(NotUser exp) {
				throw exp;
			}
			return false;
		}
		
		bool add_daily_route(const Train &train, const Date &date) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			if (!(now -> is_admin)) {
				throw NotAdmin("无管理员权限。")
			}
			string train_id = train -> get_id();
			map<pair<string, Date>, Train>::iterator it = train.begin(), it2 = it;
			for (; it != train.end() && it -> first -> first != train_id; ++it);
			
			for (Date tmp = train.get_time(); tmp <= date; tmp.go_one_day()) {
				while (it != train.end()) {
					it2 = it;
					++it2;
					if (it2 != train.end() && it2 -> first -> first == train_id && it2 -> first -> second < tmp) {
						++it;
						continue;
					} else {
						break;
					}
				}
				if (it == train.end()) {
					train[pair<string, Date>(train_id, tmp)] = Train(train, tmp);
				} else {
					it2 = it;
					++it2;
					if (tmp.is_same_day(it -> second -> get_time()) || it2 != train.end() && it2 -> first -> first == train_id && tmp.is_same_day(it -> first -> first -> get_time())) {
						continue;
					} else {
						train[pair<string, Date>(train_id, tmp)] = Train(train, tmp);
					}
				}
			}
			return true;
		}
		
		bool delete_daily_route(const Train &train, const Date &finish_time) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			if (!(now -> is_admin)) {
				throw NotAdmin("无管理员权限。")
			}
			string train_id = train -> get_id();
			Date start_time = train.get_time();
			map<pair<string, Date>, Train>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if (it -> first -> first == train_id && it -> first -> second >= start_time && it -> first -> second <= finish_time) {
					it2 = it;
					it++;
					train.erase(it2);
				}
			}
			return true;
		}
		
		bool start_daily_sale(const Train &train, const Date &finish_time) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			if (!(now -> is_admin)) {
				throw NotAdmin("无管理员权限。")
			}
			string train_id = train -> get_id();
			Date start_time = train.get_time();
			map<pair<string, Date>, Train>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if (it -> first -> first == train_id && it -> first -> second >= start_time && it -> first -> second <= finish_time) {
					it -> start_sale();
				}
			}
			return true;
		}
		
		bool finish_daily_sale(const Train &train, const Date &finish_time) {
			if (now == nullptr) {
				throw NotLogin("未登录。");
			}
			if (!(now -> is_admin)) {
				throw NotAdmin("无管理员权限。")
			}
			string train_id = train -> get_id();
			Date start_time = train.get_time();
			map<pair<string, Date>, Train>::iterator it = train.begin(), it2 = it;
			for (; it != train.end(); ++it) {
				if (it -> first -> first == train_id && it -> first -> second >= start_time && it -> first -> second <= finish_time) {
					it -> finish_sale();
				}
			}
			return true;
		}
		
		
	};

}

#endif


