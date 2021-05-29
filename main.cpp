#include "main_func.cpp"

int main(){
    int button;
    int control=0;
    string originating_station_num;
    subway originating_line;
    station originating_station;
    string terminus_station_num;
    station terminus_station;
    subway terminus_line;
    subway a;
    station b;
    cout<<"loading..."<<endl;
    file_read_excute();
    cout<<"load datas successfully!"<<endl;
    cout<<"------------------------------------Welcome to Wuhan subway system!--------------------------------------------"<<endl;
    while(1)
    {   
        cout<<"Please select the following options:"<<endl;
        cout<<"1:take subway(fare) 2:show line station  3:browse line change_station message 4:set time 5:take subway(time) 6:change crowd argc 7:take subway(avoid crowd) 99:quit"<<endl;
        cout<<"Your selection:";
        cin>>button;
        switch(button)
        {
            case 1:
                originating_line=get_line_id("originating");  //获得起始站点的线路id
                originating_station = get_station_num(originating_line);//获取起始站点
                show_station_information(originating_station); //打印起始站信息
                terminus_line = get_line_id("terminus");    //获得终点站线路的id
                terminus_station = get_station_num(terminus_line); //获取终点站的站点信息
                show_station_information(terminus_station);//打印终点站信息 
                //cout<<originating_station.get_name()<<endl<<terminus_station.get_name()<<endl;
                /*cout<<originating_station.get_near_station()[0]->get_name()<<endl;
                cout<<originating_station.get_near_station()[1]->get_name()<<endl;
                cout<<originating_station.get_near_station()[2]->get_name()<<endl;
                cout<<originating_station.get_near_station()[3]->get_name()<<endl;*/
                best_way_calculate(originating_station,terminus_station,terminus_line,0);  //计算线路
                break;
            case 2:
                show_line();
                break;
            case 3:
                a = get_line_id("");
                b = get_station_num(a);
                show_change_station_message(a,b);
                break;
            case 4:
                set_time(); //设置时间
                show_fastest_subway(true_time);         //显示地铁最快到达的时间
                break;
            case 5:
                cout<<endl<<"when you input button 5,please ensure you have input button 1 before!"<<endl<<endl;
                crowd_output_first();
                break;
            case 6:
                change_crowd_argc();
                break;
            case 7:
                originating_line=get_line_id("originating");  //获得起始站点的线路id
                originating_station = get_station_num(originating_line);//获取起始站点
                show_station_information(originating_station); //打印起始站信息
                terminus_line = get_line_id("terminus");    //获得终点站线路的id
                terminus_station = get_station_num(terminus_line); //获取终点站的站点信息
                show_station_information(terminus_station);//打印终点站信息 
                //cout<<originating_station.get_name()<<endl<<terminus_station.get_name()<<endl;
                /*cout<<originating_station.get_near_station()[0]->get_name()<<endl;
                cout<<originating_station.get_near_station()[1]->get_name()<<endl;
                cout<<originating_station.get_near_station()[2]->get_name()<<endl;
                cout<<originating_station.get_near_station()[3]->get_name()<<endl;*/
                best_way_calculate(originating_station,terminus_station,terminus_line,1);  //计算线路
                break;
            case 99:
                control=1;
                break;
            default:
                cout<<"The selection is wrongful!!!"<<endl;
                break;
        }
        if(control == 1)            //退出程序
        {
            cout<<endl;
            cout<<"Thanks to use the Wuhan subway system!!!"<<endl;
            cout<<"Looking forward to using the system again!"<<endl;
            break;
        }
    }
    system("pause");
    return 0;
}
