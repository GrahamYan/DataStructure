#ifndef SJTU_DATE_HPP
#define SJTU_DATE_HPP

#include<iostream>
#include<string>
#include<ctime>
#include "lib/ptr.hpp" 

//please remember when you use the constructor,the string you transferred should be one of the two following types
//2012-11-03
//2012-11-03,15:30
//
//you can use the following way to get the current time
//string s = sjtu::Date::current_time().print(); 

using std::string;

namespace sjtu {

class Date{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	
public:
	Date(string s) {
		int l = s.length();
		if (l == 10) {
			year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
			month = (s[5] - '0') * 10 + s[6] - '0';
			day = (s[8] - '0') * 10 + s[9] - '0';
			hour = 0;
			minute = 0;
		}
		else {
			year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + s[3] - '0';
			month = (s[5] - '0') * 10 + s[6] - '0';
			day = (s[8] - '0') * 10 + s[9] - '0';
			hour = (s[11] - '0') * 10 + s[12] - '0';
			minute = (s[14] - '0') * 10 + s[15] - '0'; 
		}
	}
	Date(const Date &obj) {
		year = obj.year;
		month = obj.month;
		day = obj.day;
		hour = obj.hour;
		minute = obj.minute;
	}
	Date &operator = (const Date& obj) {
		Date tmp;
		tmp.year = obj.year;
		tmp.month = obj.month;
		tmp.day = obj.day;
		tmp.hour = obj.hour;
		tmp.minute = obj.minute;
	}
	Date() : year(0) , month(0) , day(0) , hour(0) , minute(0) {};         //empty constructor 
	const int get_year() const {
		return year;
	}
	const int get_month() const {
		return month;
	}
	const int get_day() const {
		return day;
	}
	bool is_same_day (Date &obj) {
		return year == obj.year && month == obj.month && day == obj.day && hour == obj.hour && minute == obj.minute;
	}
	static Date current_time() {
		time_t tt = time(NULL);
		tm *t = localtime(&tt);
		//shared_ptr<tm> t(localtime(&tt));
		Date tmp;
		tmp.year = t -> tm_year + 1900;
		tmp.month = t -> tm_mon + 1;
		tmp.day = t -> tm_mday;
		tmp.hour = t -> tm_hour;
		tmp.minute = t -> tm_min;
		
		return tmp;
	}
	void get_next_day() {
		int m[13] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
			m[2] = 29;
		}
		if (day = m[month]) {
			day = 1;
			++month;
			if (month > 12) {
				++year;
				month = 1;
			}
		}
		else {
			++day;
		}
		return;
	}
	void go_one_day () {
		int m[13] = {0 , 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31};
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
			m[2] = 29;
		}
		if (day = m[month]) {
			day = 1;
			++month;
			if (month > 12) {
				++year;
				month = 1;
			}
		}
		else {
			++day;
		}
		return;
	}
    bool operator < (const Date &obj)const {
		if (year < obj.year) return true;
		if (year == obj.year) {
			if (month < obj.month) return true;
		}
		if (year == obj.year && month == obj.month) {
			if (day < obj.day) return true;
		}
		if (year == obj.year && month == obj.month && day == obj.day) {
			if (hour < obj.hour) return true;
		} 
		if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour) {
			if (minute < obj.minute) return true;
		} 
		return false;
	}
    bool operator > (const Date &obj) const {
		if (year > obj.year) return true;
		if (year == obj.year) {
			if (month > obj.month) return true;
		}
		if (year == obj.year && month == obj.month) {
			if (day > obj.day) return true;
		}
		if (year == obj.year && month == obj.month && day == obj.day) {
			if (hour > obj.hour) return true;
		} 
		if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour) {
			if (minute > obj.minute) return true;
		} 
		return false;
	}
    bool operator <= (const Date &obj) const {
		if (year < obj.year) return true;
		if (year == obj.year) {
			if (month < obj.month) return true;
		}
		if (year == obj.year && month == obj.month) {
			if (day < obj.day) return true;
		}
		if (year == obj.year && month == obj.month && day == obj.day) {
			if (hour < obj.hour) return true;
		} 
		if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour) {
			if (minute <= obj.minute) return true;
		} 
		return false;
	}
    bool operator >= (const Date &obj) const {
		if (year > obj.year) return true;
		if (year == obj.year) {
			if (month > obj.month) return true;
		}
		if (year == obj.year && month == obj.month) {
			if (day > obj.day) return true;
		}
		if (year == obj.year && month == obj.month && day == obj.day) {
			if (hour > obj.hour) return true;
		} 
		if (year == obj.year && month == obj.month && day == obj.day && hour == obj.hour) {
			if (minute >= obj.minute) return true;
		} 
		return false;
	}
    bool operator == (const Date &obj)const {
		return year == obj.year && month == obj.month && day == obj.day && hour == obj.hour && minute == obj.minute;
	}
	bool operator != (const Date &obj) {
		return !(year == obj.year && month == obj.month && day == obj.day && hour == obj.hour && minute == obj.minute);
	}
	string print() const{
		string ans;
		ans = year / 1000 + '0';
		ans += year % 1000 / 100 + '0';
		ans += year % 100 / 10 + '0';
		ans += year % 10 + '0';
		ans += '-';
		ans += month /10 + '0';
		ans += month % 10 + '0';
		ans += '-';
		ans += day /10 + '0';
		ans += day % 10 + '0';
		ans += ',';
		ans += hour /10 + '0';
		ans += hour % 10 + '0';
		ans += ':';
		ans += minute /10 + '0';
		ans += minute % 10 + '0';
		
		return ans;
	}
};
}

#endif
