#include "line_calculate.cpp"

void set_time(void) //设置时间（这里精确到分钟）
{
    while(1)    
    {
        cout<<"please input the initial time:";
        cin>>time;
        float hour = get_hour(time);
        float minute = get_minute(time);
        true_time = 60*hour+minute;
        if(true_time<begin_time || true_time>end_time)
        {
            cout<<"the time is not legal!"<<endl;
            continue;
        }else 
        {
            break;
        }
    }
    if(true_time>=450.0 && true_time<=540.0) //time 7:30 - 9:00
    {
        lines[0].set_crowd(0.8);
        lines[1].set_crowd(0.5);
        lines[2].set_crowd(0.8);
        lines[3].set_crowd(0.5);
        lines[4].set_crowd(0.15);
        lines[5].set_crowd(0.15);
        lines[6].set_crowd(0.2);
    }else if(true_time>=570.0 && true_time<=900.0)//9:30-15:00
    {
        lines[0].set_crowd(0.4);
        lines[1].set_crowd(0.5);
        lines[2].set_crowd(0.4);
        lines[3].set_crowd(0.5);
        lines[4].set_crowd(0.15);
        lines[5].set_crowd(0.15);
        lines[6].set_crowd(0.65);
    }else if(true_time>=990.0 && true_time<=1110.0)
    {
        lines[0].set_crowd(0.75);
        lines[1].set_crowd(0.5);
        lines[2].set_crowd(0.75);
        lines[3].set_crowd(0.5);
        lines[4].set_crowd(0.15);
        lines[5].set_crowd(0.15);
        lines[6].set_crowd(0.2);
    }else if(true_time>=1140.0 && true_time<=1320.0)
    {
        lines[0].set_crowd(0.4);
        lines[1].set_crowd(0.5);
        lines[2].set_crowd(0.4);
        lines[3].set_crowd(0.5);
        lines[4].set_crowd(0.65);
        lines[5].set_crowd(0.65);
        lines[6].set_crowd(0.2);
    }else 
    {
        lines[0].set_crowd(0.4);
        lines[1].set_crowd(0.5);
        lines[2].set_crowd(0.4);
        lines[3].set_crowd(0.5);
        lines[4].set_crowd(0.15);
        lines[5].set_crowd(0.15);
        lines[6].set_crowd(0.2);
    }
}

subway get_line_id(string a)//获取线路号
{
    string line_id;
    int i;
    while(1)   
    {
        cout<<"please input the "<<a<<" subway line:";
        cin>>line_id;
        for(i=0;i<max_line_num;i++)
        {
            string a = lines[i].get_id();
            if(a==line_id)
                break;
        }
        if(i==max_line_num)
        {
            cout<<"the line doesn't exist!!!"<<endl;
            continue;
        }else
        { 
            return lines[i];
        }
    }   
}

station get_station_num(subway line)   //获取站点的位次
{
    string station_num;
    int i;
    while(1) //获取起始站点位次
    {
        cout<<"please input the station position:";
        cin>>station_num;
        int last = atoi(line.get_total_station_num().c_str());
        int target = atoi(station_num.c_str()) -1;
        for(i=0;i<last;i++)
        {
            if(i == target)
                break;
        }
        if(i == last)
        {
            cout<<"the station doesn't exist!!!"<<endl;
            continue;
        }else
        {
            return  *(line.get_station(i));
        }
    }
}

void show_line(void)        //展示一条线路上的站点
{
    string way;
    subway a;
    string id;

    int i;
    while(1)
    {
        cout<<"Please input the line id:";
        cin>>id;
        for(i=0;i<max_line_num;i++)
        {
            if(lines[i].get_id()== id)
            {
                a = lines[i];
                break;
            }
        }
        if(i == max_line_num)
        {
            cout<<"The input is wrongful!"<<endl;
            continue;
        }else
        {
            way += a.get_station(0)->get_name();
            for(i=1;i<atoi(a.get_total_station_num().c_str());i++)
            {
                way += (">"+a.get_station(i)->get_name());
            }
            break;
        }
    }
    cout<<endl<<way<<endl<<endl;

}

void show_change_station_message(subway a,station b)    //指定线路、起始站点，能够显示出下一站点（2个方向可选），到换乘站点可以指定换乘到另一条线路，并继续浏览到后续站点
{
    string way1="forward:";
    string way2="back:";
    way1 += ("Go from the "+b.get_name()+",");
    way2 += ("Go from the "+b.get_name()+",");
    int i;
    for(i=0;i<atoi(a.get_total_station_num().c_str());i++)  //找到指定线路的指定站点
    {
        string id = a.get_id();
        station c  = * a.get_station(i);
        if(c.get_belong().length()>=2)  //是换乘站点
        {
            string word="change line to ";
            int j;
            for(j=0;j<c.get_belong().length();j++)
            {
                string d = "";
                d += c.get_belong()[j];
                if(d!=id)
                {
                    word += (d+" ");
                }
            }
            way1 += (word+"in "+c.get_name()+",");
        }
        if(c.get_name()==b.get_name())
        {
            break;
        }
    }
    cout<<endl<<way1<<endl<<endl;
    for(i=i+1;i<atoi(a.get_total_station_num().c_str());i++)//遍历 判断是否存在换乘的站点
    {
        string id = a.get_id();
        station c  = * a.get_station(i);
        if(c.get_belong().length()>=2)  //是换乘站点
        {
            string word="change line to ";
            int j;
            for(j=0;j<c.get_belong().length();j++)
            {
                string d = "";
                d += c.get_belong()[j];
                if(d!=id)
                {
                    word += (d+" ");
                }
            }
            way2 += (word+"in "+c.get_name()+",");
        }
    }
    cout<<endl<<way2<<endl<<endl;
}

void crowd_output_first(void)   //拥挤度优先的输出
{
    int i;
    int j;
    for(i=0;i<count_crowd;i++)
    {
        for(j=0;j<count_crowd-1;j++)
        {
            float a = total[j].time*total[j].crowd;
            float b = total[j+1].time*total[j+1].crowd;
            if(a>b)
            {
                crowd_output c = total[j+1];
                total[j+1] = total[j];
                total[j]=c;
            }
        }
    }
    for(i=0;i<count_crowd;i++)
    {
        cout<<endl<<total[i].way<<endl;
        cout<<"time:"<<total[i].time<<"minutes"<<endl;
        cout<<"fare:"<<total[i].fare<<"yuan"<<endl;
        cout<<"crowding:"<<total[i].crowd<<endl;
        cout<<endl;
    }
    return;
}

void change_crowd_argc(void)    //改变拥挤度
{
    string id;
    cout<<endl<<"please input id:";
    cin>>id;
    int i;
    for(i=0;i<count_lines;i++)
    {
        if(lines[i].get_id()==id)
        {
            cout<<endl<<"please input the crowd argc:";
            float b;
            cin>>b;
            lines[i].set_crowd(b);
            cout<<"set successfully!"<<endl<<endl;
            return;
        }
    }
    cout<<endl<<"set failed!"<<endl<<endl;
}