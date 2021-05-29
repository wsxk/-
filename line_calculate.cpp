#include "file_read.cpp"
#define max_container 1000
float run_time = 2;         //地铁过一站的时间
float stop_time = 1;            //地铁停顿时间
float chansfer_time = 3.5;      //换乘时间
float begin_time = 360;         //起始时间为6：00
float end_time = 60*23;         //停车时间为23：00
string time;
float true_time;
float wait_time=0;                //等车时间
crowd_output total[3];          //保留结果
int count_crowd=0;
//考虑拥挤度折合时间的输出

//计算拥挤度
float crowd_cal(subway line_id)
{
    return line_id.get_crowd();
}

//计算时间的函数
float calculate_time(int pass_stations,int change_stations)
{
    float time = pass_stations * 3 + change_stations*3 +wait_time;
    return time;
}

//计算费用
float calculate_fare(float distance)
{
    float price;
    if(distance<=4)
    {
        price += 2;
    }else if(4<distance && distance<=12)
    {
        price += 2;
        distance -= 4;
        if(distance<=4)
            price += 1;
        else
            price += 2;
        
    }else if(distance>12 && distance <=24)
    {
        price += 4;
        distance -= 12;
        if(distance<=6)
            price += 1;
        else 
            price += 2;
    }else if(distance>24 && distance <=40)
    {
        price += 6;
        distance -= 24;
        if(distance <=8)
            price += 1;
        else 
            price += 2;
    }else if(distance>40 && distance<=50)
    {
        price += 9;
    }else 
    {
        price += 9;
        distance -= 50;
        distance /= 20;
        price += (int)(distance+1);
    }
    return price;
}

//获得当前时间小时
float get_hour(string time) 
{
    int length = time.length();
    int i;
    string hour;
    for(i=0;i<length;i++)
    {
        if(time[i]==':')
            break;
        hour += time[i];
    }
    return atof(hour.c_str()); 
}

//获得当前时间分钟
float get_minute(string time)
{
    int length = time.length();
    int i;
    string minute;
    for(i=0;i<length;i++)
    {
        if(time[i]==':')
            break;
    }
    for(i=i+1;i<length;i++)
    {
        minute += time[i];
    }
    return atof(minute.c_str());
}

//显示站点名称，是否换乘站点
void show_station_information(station a)
{
    cout<<a.get_name()<<endl;
    if(a.get_near_station_num()>2)
        cout<<"it's the transfer station"<<endl;
    else 
        cout<<"it's not the transfer station"<<endl;
}

//显示即将到达的地铁
void show_fastest_subway(float time)
{
    int hour = time/60;
    float minute = time - hour*60;
    int a = minute;
    if(a%3==0)
    {
        cout<<endl<<"the subway is already arrive!"<<endl<<endl;
        
    }else if(a%3==1)
    {
        cout<<endl<<"the fastest subway will arrive at 2 minutes!"<<endl<<endl;
        wait_time += 2;
    }else 
    {
        cout<<endl<<"the fastest subway will arrive at 1 minute!"<<endl<<endl;
        wait_time += 1;
    }
}

//判断是否是换线 
int if_change_line(string id,station b)
{
    string belong_lines_b  = b.get_belong();
    int j;
    for(j=0;j<belong_lines_b.length();j++)
    {
        string d = "";
        d += belong_lines_b[j];
        if(id == d)
            return 0;
    }
    
    return 1;
}

//判断获取某线路号的每站的平均距离
float gain_line_average_length(string id)
{
    int i;
    for(i=0;i<count_lines;i++)
    {
        string a = lines[i].get_id();
        if(a==id)
        {
            return atof(lines[i].get_total_long().c_str())/atof(lines[i].get_total_station_num().c_str());
        }
    }
}

//获取id对应的地铁线路
subway get_subway_by_id(string id)
{
    int i;
    for(i=0;i<count_lines;i++)
    {
        if(lines[i].get_id()==id)
            return lines[i];
    }
}
//输出不同线路的路径
void line_output(station *queue,int * before_num,int count,subway begin_subway)
{
    float distance;
    int pass_stations = 0;
    int change_stations = 0;
    int b = count;
    int test=0;
    station a = queue[count];
    station before_station;
    string  way;
    string id = begin_subway.get_id();
    string before_id;
    float crowd = 0;
    way += a.get_name();
    while(b!=0)
    {
        before_station = a; //记录前一个站点
        b = before_num[b];
        a = queue[b];
        if(if_change_line(id,a))
        {
            before_id = id;
            id = a.get_belong()[0];
            change_stations++;
            way += ("(change line "+before_id+")");
        } 
        way += ("<"+a.get_name());
        distance += gain_line_average_length(id);
        pass_stations++;
        crowd += crowd_cal(get_subway_by_id(id));
    }
    if((calculate_time(pass_stations,change_stations)+true_time)<=end_time)
    {
        cout<<endl<<way<<endl;
        cout<<"time:"<<calculate_time(pass_stations,change_stations)<<"minutes"<<endl;
        cout<<"fare:"<<calculate_fare(distance)<<"yuan"<<endl;
        cout<<"crowding:"<<crowd/pass_stations<<endl;
        cout<<endl;
        total[count_crowd].way = way;
        total[count_crowd].fare = calculate_fare(distance);
        total[count_crowd].time = calculate_time(pass_stations,change_stations);
        total[count_crowd].crowd = crowd/pass_stations;
        count_crowd++;
    }else
    {
        cout<<"No way to reach!!!"<<endl<<endl;
    }
    return;
}

//检查站点是否已经遍历过
int check_station(string *check,string a,int size)
{
    for(int i=0;i<size;i++)
    {
        if(a == check[i])
            return 1;
    }
    return 0;
}

//输出同一条线的路径
void same_line(string id,station first,station end)
{
    cout<<endl<<"same_line"<<endl;
    int i;
    subway a;
    string way;
    int order = 0;
    int pass_stations=1;
    float fare = 0;
    float crowd=0;
    for(i=0;i<count_lines;i++)
    {
        if(lines[i].get_id()==id)
        {
            a = lines[i];
            break;
        }
    }
    float length = atof(a.get_total_long().c_str())/(atoi(a.get_total_station_num().c_str())-1);
    //cout<<endl<<a.get_id()<<endl<<endl;
    for(i=0;i<atoi(a.get_total_station_num().c_str());i++)  //找到起始站点
    {
        if(a.get_station(i)->get_name()==first.get_name())
        {
            way += first.get_name();
            order = 1;
            break;
        }else if(a.get_station(i)->get_name()==end.get_name())
        {
            order = -1;
            way += end.get_name();
            break;
        }
    }
    i++;
    if(order == 1)          //正序
    {
        while(a.get_station(i)->get_name()!= end.get_name())
        {
            way += (">"+a.get_station(i)->get_name());
            i++;
            pass_stations++;
            crowd += crowd_cal(a);
        }
        way += (">"+end.get_name());
        crowd += crowd_cal(a);
        if((true_time+calculate_time(pass_stations,0))<end_time)//如果没超时
        {
            float waiting_time =  calculate_time(pass_stations,0);
            cout<<endl<<way<<endl;
            cout<<"time:"<<waiting_time<<"minutes"<<endl;
            cout<<"fare:"<<calculate_fare(pass_stations*length)<<"yuan"<<endl;
            cout<<"crowding:"<<crowd/pass_stations<<endl;
            cout<<endl;
        }else
        {
            cout<<endl<<"No way to reach!!"<<endl<<endl;    //如果超时
        }
    }else if(order == -1)       //倒序
    {
        while(a.get_station(i)->get_name()!= first.get_name())
        {
            way += ("<"+a.get_station(i)->get_name());
            i++;
            pass_stations++;
            crowd += crowd_cal(a);
        }
        crowd += crowd_cal(a);
        way += ("<"+end.get_name());  
        if((true_time+calculate_time(pass_stations,0)+wait_time)<end_time) //如果没超时
        {
            float waiting_time = calculate_time(pass_stations,0);
            cout<<endl<<way<<endl;
            cout<<"time:"<<waiting_time<<"minutes"<<endl;
            cout<<"fare:"<<calculate_fare(pass_stations*length)<<"yuan"<<endl;
            cout<<"crowding:"<<crowd/pass_stations<<endl;
            cout<<endl;
        }else 
        {
            cout<<endl<<"No way to reach!!"<<endl<<endl;    //如果超时
        }
    }

}

//不同路线的路径
void different_line(station first,station end,subway begin_subway)
{
    count_crowd = 0;
    int count_line = 0;
    station queue[max_container];  //队列
    int before_num[max_container]; //队列中的前一个的序号
    string check[max_station_num];     //站点中的序号
    int count=0;
    int count_check=0;
    int i;
    queue[count] = first;
    before_num[count]=0;
    check[count_check]= first.get_name();
    count  = 1;
    count_check=1;
    float crowd = 0;
    for(i=0;i<first.get_near_station_num();i++)
    {
        //cout<<((first.get_near_station())[i])->get_name()<<endl;
        queue[count]=*((first.get_near_station())[i]);     //
        //cout<<endl<<queue[count].get_name()<<endl;
        check[count] = ((first.get_near_station())[i])->get_name();
        before_num[count_check]= 0;
        count++;
        count_check++;
    }
    for(i=1;i<count;i++)
    {
        if(count_line == 3)
            break;
        station a = queue[i];
        if(a.get_name()==end.get_name())
        {
            line_output(queue,before_num,i,begin_subway);
            count_line++;
            continue;
        }
        for(int j=0;j<a.get_near_station_num();j++)
        {
            station c = *(a.get_near_station())[j];
            if(c.get_name()!=end.get_name())
            {
                if(!check_station(check,c.get_name(),count))
                {
                    queue[count] = c;
                    before_num[count] = i;
                    check[count_check] = c.get_name();
                    count++;
                    count_check++;
                }
            }else 
            {
                queue[count] = c;
                before_num[count]= i;
                count++;
            }
        }
    }
    return ;
}

//这是考虑了拥挤度的不同线路的输出
int line_output_avoid_crowd(station *queue,int * before_num,int count,subway begin_subway)
{
    float distance;
    int pass_stations = 0;
    int change_stations = 0;
    int b = count;
    int test=0;
    station a = queue[count];
    station before_station;
    string  way;
    string id = begin_subway.get_id();
    string before_id;
    float crowd = 0;
    way += a.get_name();
    while(b!=0)
    {
        before_station = a; //记录前一个站点
        b = before_num[b];
        a = queue[b];
        if(if_change_line(id,a))
        {
            before_id = id;
            id = a.get_belong()[0];
            change_stations++;
            way += ("(change line "+before_id+")");
        } 
        way += ("<"+a.get_name());
        distance += gain_line_average_length(id);
        pass_stations++;
        crowd += crowd_cal(get_subway_by_id(id));
    }
    if((calculate_time(pass_stations,change_stations)+true_time)<=end_time)
    {
        cout<<endl<<way<<endl;
        cout<<"time:"<<calculate_time(pass_stations,change_stations)<<"minutes"<<endl;
        cout<<"fare:"<<calculate_fare(distance)<<"yuan"<<endl;
        cout<<"crowding:"<<crowd/pass_stations<<endl;
        cout<<endl;
        total[count_crowd].way = way;
        total[count_crowd].fare = calculate_fare(distance);
        total[count_crowd].time = calculate_time(pass_stations,change_stations);
        total[count_crowd].crowd = crowd/pass_stations;
        count_crowd++;
        if(crowd>0.50)
        {
            count_crowd--;
            return 0;
        }
    }else
    {
        cout<<"No way to reach!!!"<<endl<<endl;
    }
    return 1;
}

//这是考虑了拥挤度的不同路径算法
void different_line_avoid_crowd(station first,station end,subway begin_subway)
{
    count_crowd = 0;
    int count_line = 0;
    station queue[max_container];  //队列
    int before_num[max_container]; //队列中的前一个的序号
    string check[max_station_num];     //站点中的序号
    int count=0;
    int count_check=0;
    int i;
    queue[count] = first;
    before_num[count]=0;
    check[count_check]= first.get_name();
    count  = 1;
    count_check=1;
    float crowd = 0;
    for(i=0;i<first.get_near_station_num();i++)
    {
        //cout<<((first.get_near_station())[i])->get_name()<<endl;
        queue[count]=*((first.get_near_station())[i]);     //
        //cout<<endl<<queue[count].get_name()<<endl;
        check[count] = ((first.get_near_station())[i])->get_name();
        before_num[count_check]= 0;
        count++;
        count_check++;
    }
    for(i=1;i<count;i++)
    {
        if(count_line == 3)
            break;
        station a = queue[i];
        if(a.get_name()==end.get_name())
        {
            if(line_output_avoid_crowd(queue,before_num,i,begin_subway))
            {
                count_line++;;
            }
            continue;
        }
        for(int j=0;j<a.get_near_station_num();j++)
        {
            station c = *(a.get_near_station())[j];
            if(c.get_name()!=end.get_name())
            {
                if(!check_station(check,c.get_name(),count))
                {
                    queue[count] = c;
                    before_num[count] = i;
                    check[count_check] = c.get_name();
                    count++;
                    count_check++;
                }
            }else 
            {
                queue[count] = c;
                before_num[count]= i;
                count++;
            }
        }
    }
    return ;
}

//计算最佳路线
void best_way_calculate(station first,station end,subway begin_subway,int whether_consider_crowd)
{
    string a = first.get_belong();
    //cout<<first.get_belong()<<endl;
    //cout<<end.get_belong()<<endl;
    int i ;
    for(i=0;i<a.length();i++)
    {
        string b = end.get_belong();
        for(int d = 0;d<b.length();d++)
        {
            if(a[i]==b[d])
            {
                string c="";
                c += a[i];
                //cout<<endl<<"enter the same_line"+c<<endl<<endl;  
                same_line(c,first,end);
                return;
            }
        }
    }
    if(i==a.length()) //不在同一线路
    {
        cout<<endl<<"enter the different_line"<<endl<<endl;
        if(whether_consider_crowd==0)
            different_line(first,end,begin_subway);
        else 
            different_line_avoid_crowd(first,end,begin_subway);
        return;
    }
}