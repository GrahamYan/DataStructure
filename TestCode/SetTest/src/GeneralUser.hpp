#ifndef SJTU_GENERALUSER_HPP
#define SJTU_GENERALUSER_HPP

#include<string>
#include"Exceptions.hpp"
#include"File.hpp"
#include"lib/ptr.hpp"

using std::string;
using namespace sjtu
{
	class GeneralUser
	{
	private:
		string user_id,name,password;
		bool admin_or_not; pair <Log,Log> my_log;
		set <Tickets> my_ticket; double money;
		// 构造函数部分
	public:
		GeneralUser(const string &_user_id,const string &_name,const string &_password,bool _admin_or_not):
			user_id(_user_id),name(_name),password(_password),admin_or_not(_admin_or_not)
		{
			if (password.length() < 6||password.length() > 15)
				throw PasswordIsNotValid();
		}

		//默认析构函数

		//返回用户基本信息，包括 user_id，name
		string query_my_info() const
		{
			string ret = "";
			ret += "User ID: " + user_id + "\n";
			ret += "姓名： " + name + "\n";
			return string;
		}

		//修改用户名字, 不能长于15
		bool modify_name(const string &_name) 
		{
			if (_name.length()&&_name.length() > 15) return false;
			name = _name; return true;
		}

		//修改密码
		bool modify_password(const string &_password,const string &npassword1,const string &npassword2)
		{
			if (_password != password) return false;
			if (npassword1.length() < 6||npassword1.length() > 15) return false;
			if (npassword1 != npassword2) return false;
			password != npassword1; return true;
		}
		
		//是否是管理员
		bool is_admin() const { return admin_or_not; }

		//买票或失败, 管理员不能买票
		bool buy_ticket(shared_ptr <Train> obj,const string &train_id,const Date &date,const string &start_station,const string &finish_station,const string &level,int num)
		{
			if (admin_or_not) return false;
			if (obj->buy_ticket(start_station,finish_station,level,num))
			{
				auto it = my_ticket.find()
				return true;
			}
			return false;
		}

		//退票或失败，管理员不能退票
		bool refund_ticket(shared_ptr <Train> obj,const string &train_id,const Date &date,const string &start_station,const string &finish_station,const string &level,int num)
		{
			if (admin_or_not) return false;
			if (obj->refund_ticket(start_station,finish_station,level,num))
			{
				return true;
			}
			return false;
		}
		//往账户里面充钱
		bool charge(double inc)
		{
			if (admin_or_not) return false;
			money += inc; return true;
		}

		//查询账户余额
		double query_money() const { return money; }
		
		//返回我买的票
		shared_ptr < vector <Tickets> > query_my_tickets() const
		{
			shared_ptr < vector <Tickets> > ret = new vector <Tickets>;
			for (auto it = my_ticket.begin();it != my_ticket.end();++it)
				(*ret).push_back(*it);
			return ret;
		}

		//返回log(注意权限), 注意返回哪种log
		shared_ptr < pair <Log,Log> > query_log() const
		{
			shared_ptr < pair <Log,Log> > ret = new pair <Log,Log> (my_log);
			return ret;
		}
	}
}

#endif
