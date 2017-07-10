#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cassert>
#include"Train.hpp"
#include"Station.hpp"
#include"lib/ptr.hpp"
#include"lib/vector.hpp"
using namespace sjtu;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	// struct timeb t;ftime(&t);
	// srand(t.millitm+t.time*1000);
	shared_ptr <Train> ptr; vector <Station> _route; Train Empty;
	vector <string> _type; vector <double> _price;
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

	ptr = new Train(true,_route,"PY12138",Date("2017-05-08,14:00"));
	ptr->go_one_day();
	cout << ptr->get_id() << endl;
	cout << (ptr->get_time()).print() << endl;

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之涵","金之之",Date("2017-05-09,14:00"),Date("2017-05-09,14:00"),"一等座",10);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:00"),"金之涵","金之之","一等座",10,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }
	
	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之之","全涵涵",Date("2017-05-09,14:01"),Date("2017-05-09,14:01"),"一等座",10);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:01"),"金之之","全涵涵","一等座",10,10));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之涵","金之之",Date("2017-05-09,13:59"),Date("2017-05-09,13:59"),"一等座",10);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,13:59"),"金之涵","金之之","一等座",10,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之涵","金之之",Date("2017-05-09,14:00"),Date("2017-05-09,14:00"),"一等座 ",10);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:00"),"金之涵","金之之","一等座 ",10,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之涵","金之之",Date("2017-05-09,14:00"),Date("2017-05-09,14:00"),"一等座",2001);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:00"),"金之涵","金之之","一等座",2001,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之之","金之涵",Date("2017-05-09,14:00"),Date("2017-05-09,14:00"),"一等座 ",2001);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:00"),"金之之","金之涵","一等座 ",2001,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// try
	// {
	// 	auto ticket = ptr->get_ticket("金之之","金之之",Date("2017-05-09,14:00"),Date("2017-05-09,14:00"),"一等座 ",2001);
	// 	assert(ticket == Tickets("PY12138",Date("2017-05-09,14:00"),"金之之","金之之","一等座 ",2001,10.5));
	// }
	// catch(Exception ex) { cout << ex.detail << endl; }

	// auto name = ptr->query_station();
	// for (auto it = name->begin();it != name->end();++it) cout << *it << endl;

	double money = 10000;

	try { assert(ptr->buy_ticket("金之之","全涵涵","一等座",2001,money)); }
	catch(Exception ex) { cout << ex.detail << endl; }
	cout << money << endl;

	// try { assert(ptr->refund_ticket("金之之","全涵涵","一等座",1000,money)); }
	// catch(Exception ex) { cout << ex.detail << endl; }
	// cout << money << endl;

	return 0;
}