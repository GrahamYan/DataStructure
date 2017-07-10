# 指南


## 注意
1. 文件名与类名保持一致
2. 每个逻辑块都要大括号
3. 传入参数尽量用const引用 

## 模块
星号表示待讨论

<div>
    <table border="0">
	  <tr>
	    <th>类名</th>
	    <th>功能</th>
	    <th> 情况</th>
	  </tr>
	  <tr>
	    <th> shared_ptr </th>
	    <th> 智能指针（lib）</th>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>set</td>
	    <td>lib</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>map</td>
	    <td>lib</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>vector</td>
	    <td>lib</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>pair</td>
	    <td>lib</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td> File</td>
	    <td>文件</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>Log</td>
	    <td>日志</td>
	    <th> 待测  </th>
	  </tr>
	  <tr>
	    <td>Date</td>
	    <td>时间</td>
	    <th> finished </th>
	  </tr>
	  <tr>
	    <td>Exceptions(哪些要)</td>
	    <td>异常处理</td>
	    <th> finished  </th>
	  </tr>
	  <tr>
	    <td>User</td>
	    <td>关于所有用户</td>
	    <th> 待测 </th>
	  </tr>
	  <tr>
	    <td>GeneralUser</td>
	    <td>一般用户</td>
	    <th> 待测  </th>
	  </tr>
	  <tr>
	    <td> Admin</td>
	    <td>管理员</td>
	    <th> 取消 </th>
	  </tr>
	  <tr>
	    <td>Station</td>
	    <td>火车站点</td>
	    <th>  finished</th>
	  </tr>
	  <tr>
	    <td>Train</td>
	    <td>单趟单日列车</td>
	    <th>  finished</th>
	  </tr>
	  <tr>
	    <td>Tickets</td>
	    <td>哪趟火车起点终点张数</td>
	    <th>finished</th>
	  </tr>
    </table>
</div>

## 具体实现
**星号表示待讨论**

空构造，拷贝构造一定要有
*operator =
变量注意清空
**以下所有＊均表示智能指针，禁止使用裸指针**

#### TicketLevel
注意：考虑到每趟车有不完全一样的两到三种票型（一等座,商务座,无座,硬座,特等座,二等座,硬卧下,软卧下,软座,高级软卧），特改为string

#### Log
单纯使用string

|类型|成员|功能|
|:------:|:------:|:------:|
|vector<string>|information|记录log|

|返回类型|成员函数|功能|
|:------:|:------:|:------:|
|BinaryInput|operator >>|文件读入|
|BinaryOutput|operator <<|文件输出|
|log|buy_log()|只返回买票历史|
|log|refund_log()|只返回退票历史|
|log|buy_refund_log()|买票退票信息|
|log|charge_log()|充值信息|
|void|modify_name(Date now, string new_name)|某时改name|
|void|modify_password(Date now, string new_password)|改password|
|void|buy_tickets(Date now, Tickets new_tickets)|买票|
|void|refund_tickets(Date now, Tickets new tickets)|退票|
|void|charge(Date now, double money)|用户充值|
|void|add_daily_route(Date now, Train new_train, Date finish_time)|增加一段时间的车次|
|void|delete_daily_route(Date now, Train new_train, Date finish_time)|取消一段时间的车次|
|void|start_daily_sale(Date now, Train new_train, Date finish_time)|开始发售一段时间的车次的车票|
|void|finish_daily_sale(Date now, Train new_train, Date finish_time)|停止发售一段时间的车次的车票|


#### Date

<div>
    <table border="0">
	  <tr>
	    <th>类型</th>
	    <th>成员</th>
	    <th>功能</th>
	  </tr>
	  <tr>
	    <th>int</th>
	    <th>year</th>
	    <th>年</th>
	  </tr>
	  <tr>
	    <th>int</th>
	    <th>month</th>
	    <th>月</th>
	  </tr>
	  <tr>
	    <th>int</th>
	    <th>day</th>
	    <th>日</th>
	  </tr>
	  <tr>
	    <th>int</th>
	    <th>hour</th>
	    <th><小时/th>
	  </tr>
	  <tr>
	    <th>int</th>
	    <th>minute</th>
	    <th>分钟</th>
	  </tr>
    </table>
</div>

<div>
    <table border="0">
	  <tr>
	    <th>返回类型</th>
	    <th>成员函数</th>
	    <th>功能</th>
	  </tr>
	  <tr>
	    <th>构造函数</th>
	    <th>Date(year, month, day, hour = 0, minute = 0)</th>
	    <th>构造函数</th>
	  </tr>
	  <tr>
	    <th>构造函数</th>
	    <th>Date(string)</th>
	    <th>通过字符串构造日期()，考虑有没有hour,minute</th>
	  </tr>
	  <tr>
	    <th>bool </th>
	    <th>is_same_day(Date, Date)</th>
	    <th>是否同一天</th>
	  </tr>
	  <tr>
	    <th>Date </th>
	    <th>current_time()</th>
	    <th>返回当前时间</th>
	  </tr>
	  <tr>
	    <th>void </th>
	    <th>go_one_day()</th>
	    <th>变为下一天</th>
	  </tr>
	  <tr>
	    <th>void </th>
	    <th>get_next_day()</th>
	    <th>下一天</th>
	  </tr>
	  <tr>
	    <th>Date(暂时不写)</th>
	    <th>operator +(Date, int )</th>
	    <th>时间向后顺延多少分钟,考虑月份里的日子数和润年，一天一天暴力</th>
	  </tr>
	  <tr>
	    <th>int(暂时不写)</th>
	    <th>operator -(Date, Date)</th>
	    <th>时间差(分钟)</th>
	  </tr>
	   <tr>
	    <th>bool</th>
	    <th>operator <(Date, Date)</th>
	    <th>比较小于</th>
	  </tr>
	   <tr>
	    <th>bool</th>
	    <th>operator >Date, Date)</th>
	    <th>比较大于</th>
	  </tr>
	   <tr>
	    <th>bool</th>
	    <th>operator <=(Date, Date)</th>
	    <th>比较小于=</th>
	  </tr>
	   <tr>
	    <th>bool</th>
	    <th>operator >=Date, Date)</th>
	    <th>比较大于=</th>
	  </tr>
	  <tr>
	    <th>string</th>
	    <th>print()</th>
	    <th>将时间打印到字符串</th>
	  </tr>
    </table>
</div>


#### Exceptions
1. 车次不存在
2. 日期不存在
3. 站点不存在或不存在于当前车次
4. 用户不存在
5. 密码错误
6. 无管理员权限
7. 票数不够
8. 用户密码设置不合理(密码长度为6-15位)
9. 余额不足

<div>
    <table border="0">
	  <tr>
	    <th>类型</th>
	    <th>成员</th>
	    <th>功能</th>
	  </tr>
    </table>
</div>

<div>
    <table border="0">
	  <tr>
	    <th>返回类型</th>
	    <th>成员函数</th>
	    <th>功能</th>
	  </tr>
    </table>
</div>


#### GeneralUser
默认密码000000
构造时强制传入user_id
不能买票

<div>
    <table border="0">
	  <tr>
	    <th>类型</th>
	    <th>成员</th>
	    <th>功能</th>
	  </tr>
	   <tr>
	    <th>string</th>
	    <th>user_id</th>
	    <th>用户id</th>
	  </tr>
	   <tr>
	    <th>string</th>
	    <th>name</th>
	    <th>用户名字</th>
	  </tr>
	   <tr>
	    <th>string</th>
	    <th>password</th>
	    <th>用户密码</th>
	  </tr>
	   <tr>
	    <th>bool</th>
	    <th>admin_or_not</th>
	    <th>是否是管理员</th>
	  </tr>
	   <tr>
	    <th>pair(Log,Log)</th>
	    <th>my_log</th>
	    <th>用户日志(订票，退票)</th>
	  </tr>
	   <tr>
	    <th>Set (Tickets) </th>
	    <th>my_ticket</th>
	    <th>订票信息</th>
	   <tr>
	    <th>double </th>
	    <th>money</th>
	    <th>账户余额</th>
	  </tr>
    </table>
</div>

<div>
    <table border="0">
	  <tr>
	    <th>返回类型</th>
	    <th>成员函数</th>
	    <th>功能</th>
	  </tr>
	  <tr>
	    <th>string</th>
	    <th>query_my_info()</th>
	    <th>返回用户基本信息，包括 user_id， name</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>modify_name(string)</th>
	    <th>修改用户名字, 不能长于15</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>modify_password(string, string,string)</th>
	    <th>修改用户密码，先验证原密码，并且新密码不长于15，后面两个新密码要一样！！！</th>
	  </tr>
	    <tr>
	    <th>bool</th>
	    <th>login(string)</th>
	    <th>检验用户登录是否成功</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>is_admin()</th>
	    <th>是否是管理员</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>buy_ticket(string train_id, Date, string start_station, string finish_station, string string level, int)</th>
	    <th>买票或失败, 管理员不能买票</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>refund_ticket(string train_id, Date, string start_station, string finish_station, string level, int)</th>
	    <th>退票或失败，管理员不能退票</th>
	  </tr>
	  <tr>
	    <th>bool</th>
	    <th>charge(double)</th>
	    <th>往账户中充钱，管理员不能充值</th>
	  </tr>
	  <tr>
	    <th>double</th>
	    <th>query_money()</th>
	    <th>询问账户余额</th>
	  </tr>
	  <tr>
	    <th> vector(Tickets) </th>
	    <th>query_my_tickets()</th>
	    <th>返回我买的票</th>
	  </tr>
	  <tr>
	    <th>*log</th>
	    <th>query_log(LogType)</th>
	    <th>返回log(注意权限), 注意返回哪种log</th>
	  </tr>
</div>

||||
|:------:|:------:|:------:|
|bool|add_daily_route(Train, finish_time,)|增加时间段内单趟列车,最多30天，判断权限|
 |bool|delete_daily_route(Train, finish_time)|删去时间段内单趟列车,最多30天，判断权限|
 |bool|start_daily_sale(train_id, start_time, finish_time,)|开始发售时间段内单趟车车票, 判断权限|
 |bool|finish_daily_sale(train_id, start_time,  finish_time)|结束发售时间段内单趟列车车票, 判断权限|


#### Admin
继承GeneralUser
不能买票

|类型|成员|描述|
|:------:|:------:|:------:|
||||
 
|返回类型|成员函数|功能|
|:------:|:------:|:------:|
|bool|add_daily_route(Train, finish_time,)|增加时间段内单趟列车,最多30天，判断权限|
 |bool|delete_daily_route(Train, finish_time)|删去时间段内单趟列车,最多30天，判断权限|
 |bool|start_daily_sale(train_id, start_time, finish_time,)|开始发售时间段内单趟车车票, 判断权限|
 |bool|finish_daily_sale(train_id, start_time,  finish_time)|结束发售时间段内单趟列车车票, 判断权限|

#### User
内嵌GeneralUser和Admin
若操作时尚未登录，则返回空容器，并提醒
查询票信息的时候要根据具体站点的时间，而不是车次的时间

|类型|成员|描述|
|:------:|:------:|:------:|
|map: user_id -> GeneralUser|user|所有用户|
|*GeneralUser|now|现在登录是谁或NULL|
| long long|now_id|目前分配到的id|
|string|official_identifying_code|管理员注册验证码|
 |map: (train_id, Date) -> Train|train|单日单趟线路|
 

|返回类型|成员函数|功能|
|:------:|:------:|:------:|
|string|register(name, password1, password2)|普通用户注册, id为空生成一个，id判重，判密码, 返回id|
|string|admin_register(name, password1, password2，identifying_code)|管理员注册, id生成一个，id判重，判密码, 返回id，管理员要check验证码|
|bool|login(user_id, password)|登录并判断是否具有管理员权限|
|bool|logout(user_id, password)|推出当前帐号|
|void|set_identifying_code(original_code, new_code)|重置验证码,强制admin|
|vector(string)|query_station(string train_id, Date time)|返回车次的所有站名|
|vector(Tickets)|query_ticket_by_id(string train_id, start_station, finish_station, Date start_time, Date finish_time, level vector<string>, int number)|根据车次和时间段以及张数查询所有列车情况, 并且若天数大于30天，只返回30天内的|
|vector(Tickets)|query_ticket(start_time,  finish_time, start_station, finish_station, level vector<string>, int number)|根据时间段，站点( 模糊搜索,判前两个字是否完全一样 ), 张数返回至多30天的车票|
|string|query_my_info()|返回个人信息，直接调用GeneralUser里的，判断now是否空,不包括密码|
|string|query_info()|返回任意非管理员且存在的用户的信息,判断权限|
|vector(Tickets)|query_my_tickets()|返回我买的票|
|shared_ptr(Log)|query_log(user_id, LogType)|返回任意存在且非管理员的log, 判断权限|
|bool|modify_name(string)|改用户名, 判断登录|
|bool|modfiy_password(string, string)|改密码, 判断登录|
|bool|charge(double)|充值|
|bool|buy_ticket(train_id, Date, start_station, finish_station, string level, int)|买票, 判断登录|
|bool|refund_ticket(train_id, Date, start_station, finish_station, string level, int)|退票, 判断登录|
 |bool|add_daily_route(Train, finish_time,)|增加时间段内单趟列车,最多30天，判断权限|
 |bool|delete_daily_route(Train, finish_time)|删去时间段内单趟列车,最多30天，判断权限|
 |bool|start_daily_sale(train_id, start_time, finish_time,)|开始发售时间段内单趟车车票, 判断权限|
 |bool|finish_daily_sale(train_id, start_time,  finish_time)|结束发售时间段内单趟列车车票, 判断权限|
 
 #### Station

|类型|成员|描述|
|:------:|:------:|:------:|
 |string|location|站名|
 |static const|MAX|人数上限2000, 用于初始化和上限判断|
 |Date|arrival_time|到站时间|
 |Date|departure_time|出发时间|
 |double|price|价格|
 |int[3]|left_number|火车开到该站该下车的人下车，该上车的人上车后的剩余人数|
 |int|dist|前缀里程|

|返回类型|成员函数|功能|
|:------:|:------:|:------:|
 |string|query_location()|站点|
 |Date|query_arrival_time()|站点|到站时间
 |double|query_price()|某种档次票价|
 |bool|is_same_location(string another_location)|模糊判断是否同一处，取前两个字|
 |int&|left_number|返回剩余张数|
 
  #### Train

|类型|成员|描述|
|:------:|:------:|:------:|
 |bool|on_sale|是否在卖|
 |vector(Station)|route|线路|
 |string|train_id|车次|
 |Date|departure_time|发车时间|

|返回类型|成员函数|功能|
|:------:|:------:|:------:|
|string|get_id|返回id|
||Train(Train, date)|通过一个Train的所有其他信息和一个日期**构造**Train|
|Date|get_time()|返回发车时间|
|Tickets|get_ticket(start_station, finish_station, start_time,  finish_time, level, number)|返回出站(start_time)在start_time到finish_time之间的票，票数不够就返回所有的票,无票throw|
|shared_ptr(vector(string))|query_station()|所有站名|
 |bool|buy_ticket(string start_station,string  finish_station, string level, int,double &money)|买票, 判断**区间是否可减以及余额是否够**，若true则减少money，且若true则改区间信息|
  |bool|refund_ticket(string start_station, string finish_station, string level, int，double &money)|退票, 增加money,改区间信息|
 |bool|start_sale()|开始发售|
 |bool|finish_sale()|结束发售|
 |bool|query_on_sale()|返回是否售票|
 
 
 #### Tickets

|类型|成员|描述|
|:------:|:------:|:------:|
|string|train_id|车次|
|Date|depature_time|发车时间|
|string|start_station|起点|
|string|finish_station|终点|
|string|level|票的级别|
|int|number|张数|
|double|price|单张价格（终点起点价格差）|

|返回类型|成员函数|功能|
|:------:|:------:|:------:|
|bool|operator <(lhs, rhs)|建立按照所有关键字的偏序，尽量先比较短的，后比较长的|
|const int|query_number()|返回张数|
|const string|query_id()|返回id|
|const Date|query_date()|返回date|
|const string|query_level()|返回level|
|const string|query_start_station()|返回起点|
|const string|query_finish_station()|返回终点|
|bool|modify_number(int delta)|加或者减, 若小于0, 返回失败|


## 特色功能
1. 音效？？？
2. 模糊搜索
3. 管理员一段时间统一操作
4. 所有车的所有站点列表

## 待讨论
1. 火车型号处理
2. 密码查询方式
3. 同一天不能有两个同样的train_id？？？
4. file的处理方式？？？？？？？rain