#include "subway_station_module.cpp"
//#define file_path "./data/"
#define file_path "./data/"
station stations[max_station_num];
subway lines[max_line_num];
int count_stations=0;
int count_lines=0;

int is_station_existed(string b){               //判断该站点是否已存在
    int a;
    for(a=0;a<count_stations;a++)
    {
        if(b==stations[a].get_name())
            return a;
    }
    return -1;
}

void add_nearstation_datas(subway a)            //用于给站点添加相邻站点的信息
{
    int num = atoi(a.get_total_station_num().c_str());
    for(int i=0;i<num;i++)
    {
        if(i==0)
        {
            station * temp = a.get_station(i+1);
            (a.get_station(i))->add_near_station(temp);
        }else if(i == num-1)
        {
            station * temp = a.get_station(i-1);
            (a.get_station(i))->add_near_station(temp);
        }else
        {
            station * temp = a.get_station(i-1);
            (a.get_station(i))->add_near_station(temp);
            temp = a.get_station(i+1);
            (a.get_station(i))->add_near_station(temp);
        }            
    }
}

void get_content(string filename){              //获取文本内容
    ifstream ifile;
    string path = file_path + filename;
    ifile.open(path.c_str());
    string id,full_people,total_long,station_num;
    getline(ifile,id);                              //读取地铁线路基本内容
    getline(ifile,full_people);
    getline(ifile,total_long);
    getline(ifile,station_num);
    lines[count_lines].set_id(id);                  //设置地铁线路基本内容
    lines[count_lines].set_full_people(full_people);
    lines[count_lines].set_total_long(total_long);
    lines[count_lines].set_total_station_num(station_num);
    lines[count_lines].init_station_line();
    int num = atoi(station_num.c_str());
    int i;
    for(i=0;i<num;i++)                      //读取站点信息
    {
        string name;
        int j;
        getline(ifile,name);                    
        if((j=is_station_existed(name))>=0)         //如果该站点已经读取 则在已存内容补上所属线路号
        {
            stations[j].add_belong(id);
            lines[count_lines].add_station_line(&stations[j]);
        }else                                       //如果站点不存在，则添加该站点
        {  
            stations[count_stations].set_name(name);
            stations[count_stations].add_belong(lines[count_lines].get_id());
            lines[count_lines].add_station_line(&stations[count_stations]);
            count_stations++;
        }     
    }
    ifile.close();
    add_nearstation_datas(lines[count_lines]);
    count_lines++;
}

void file_read_excute()                         //外部接口
{
    string filename1="subway_one.txt";
    string filename2="subway_two.txt";
    string filename3="subway_three.txt";
    string filename4="subway_four.txt";
    string filename6="subway_six.txt";
    string filename7="subway_seven.txt";
    string filename8="subway_eight.txt";
    get_content(filename1);
    get_content(filename2);
    get_content(filename3);
    get_content(filename4);
    get_content(filename6);
    get_content(filename7);
    get_content(filename8);
}