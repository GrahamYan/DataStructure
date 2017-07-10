#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include"GeneralUser.hpp"
#include"lib/ptr.hpp"
#include"lib/map.hpp"
#include"Date.hpp"
using namespace sjtu;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	GeneralUser // lhh("lhh1998","归蓝","123456",false),
		jzh("jzh1998","PascalPrimer","000000")// ,lmy("lmxyy","小小李子","252818",true)
		;
	// cout << lhh.query_my_info() << endl;
	// cout << jzh.query_my_info() << endl;
	// cout << lmy.query_my_info() << endl;
	// cout << jzh.get_name() << endl;
	// jzh.modify_name("金之涵");
	// cout << jzh.get_name() << endl;
	// cout << jzh.query_my_info() << endl;
	// assert(!jzh.check_password("000001 "));
	// assert(jzh.check_password("000000"));
	// jzh.modify_password("111111");
	// assert(!jzh.check_password("000000"));
	// assert(jzh.check_password("111111"));
	// assert(!jzh.is_admin());
	// assert(lmy.is_admin());
	// cout << lhh.get_id() << endl;
	// cout << lmy.get_id() << endl;
	map < pair <string,Date>,Train,Compare_Date > M;

	vector <Station> _route; vector <string> _type; vector <double> _price;
	_type.push_back("一等座");
	_type.push_back("商务座");
	_type.push_back("无座");
	_type.push_back("硬座");
	_type.push_back("特等座");
	_type.push_back("二等座");
	_type.push_back("硬卧下");
	_type.push_back("软卧下");
	_type.push_back("软座");
	_type.push_back("高级软卧");
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_price.push_back(0);
	_route.push_back(Station("金之涵",Date("2017-05-08,13:55"),Date("2017-05-08,14:00"),_type,_price,0));
	for (int i = 0;i < 10;++i) _price[i] = (i+1)*10+0.5;
	_route.push_back(Station("金之之",Date("2017-05-08,14:55"),Date("2017-05-08,15:00"),_type,_price,0));
	for (int i = 0;i < 10;++i) _price[i] = (i+1)*20+0.5;
	_route.push_back(Station("全涵涵",Date("2017-05-08,15:55"),Date("2017-05-08,16:00"),_type,_price,0));

	Train tmp(true,_route,"PY12138",Date("2017-05-08,14:00"));
	M[pair <string,Date> (tmp.get_id(),tmp.get_time())] = tmp;
	// jzh.charge(20000);
	// cout << jzh.query_money() << endl;
	
	// try
	// {
	// 	jzh.refund_ticket(M.begin(),"PY12138","金之之","全涵涵","一等座",0);	
	// }
	// catch (Exception ex) { cout << ex.detail << endl; }
	
	// try
	// {
	// 	lmy.buy_ticket(M.begin(),"PY12138","金之之","全涵涵","一等座",5);
	// }
	// catch (Exception ex) { cout << ex.detail << endl; }
	// try
	// {
	// 	jzh.buy_ticket(M.begin(),"PY12138","金之之","金之之","一等座",5);
	// }
	// catch (Exception ex) { cout << ex.detail << endl; }
	// try
	// {
	// 	jzh.buy_ticket(M.begin(),"PY12138","金之之","全涵涵","一等座",2000);
	// 	cout << jzh.query_money() << endl;
	// }
	// catch (Exception ex) { cout << ex.detail << endl; }
	// jzh.charge(20000);
	// try
	// {
	// 	jzh.buy_ticket(M.begin(),"PY12138","金之之","全涵涵","一等座",0);
	// }
	// catch (Exception ex) { cout << ex.detail << endl; }

	try
	{
		jzh.refund_ticket(M.begin(),"PY12138","金之之","全涵涵","一等座",0);
	}
	catch (Exception ex) { cout << ex.detail << endl; };
	
	return 0;
}
