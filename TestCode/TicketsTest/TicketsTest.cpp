#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<set>
#include"lib/ptr.hpp"
#include"Date.hpp"
#include"Tickets.hpp"
#include"lib/set.hpp"

using namespace sjtu;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	shared_ptr < Tickets > p;
	p = new Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11);
	if (*p == Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11)) puts("Yes"); else puts("No");
	if (*p == Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",5,12)) puts("Yes"); else puts("No");
	*p = Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11);
	if (*p == Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11)) puts("Yes"); else puts("No");
	if (*p != Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",5,12)) puts("Yes"); else puts("No");
	set <Tickets> S; std::set <Tickets> stdS;
	S.insert(Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11));
	stdS.insert(Tickets("G1355",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11));
	S.insert(Tickets("G1354",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11));
	stdS.insert(Tickets("G1354",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",8,11));
	S.insert(Tickets("G1354",Date::current_time(),"金之涵","金之之","一等座",8,11));
	stdS.insert(Tickets("G1354",Date::current_time(),"金之涵","金之之","一等座",8,11));
	S.insert(Tickets("G1354",Date::current_time(),"全之涵","金之之","一等座",8,11));
	stdS.insert(Tickets("G1354",Date::current_time(),"全之涵","金之之","一等座",8,11));
	cout << S.size() << ' ' << stdS.size() << endl;
	S.insert(Tickets("G1354",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",9,12));
	stdS.insert(Tickets("G1354",Date("2017-05-08,13:55"),"金之涵","金之之","一等座",9,12));
	cout << S.size() << ' ' << stdS.size() << endl;

	auto it1 = S.begin(); auto it2 = stdS.begin();
	for (;it1 != S.end()&&it2 != stdS.end();++it1,++it2) assert(*it1 == *it2);
	
	p->query_number();
	p->query_id();
	p->query_date();
	p->query_level();
	p->query_start_station();
	p->query_finish_station();
	assert(!(p->modify_number(-9)));
	assert((p->modify_number(-8)));
	return 0;
}
