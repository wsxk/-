#include <iostream>
#include <fstream>
#include <stdlib.h>
#define max_line_num 7          //最大的地铁线路数量
#define max_station_num 300     //最大的站点数量
using namespace std;

class station{            //站点类型
    private:
    string name;                    //站点名
    string belong_line;             //站点位于哪些线路中
    station **near_station;         //站点的邻近站点
    int count;                      //记录站点的邻近站点数
    public:
    station(){                      //站点类型的初始化函数
        name="";
        belong_line="";
        near_station=(station **)malloc(sizeof(station *)*max_line_num);
        count=0;
    }
    string get_name(){              //接口，获得站点的名字
        return name;
    }
    void set_name(string strings){     //设置站点名字
        name = strings;
    }
    void add_belong(string id){         //添加站点的 新的所属线路
        belong_line += id;
    }
    int if_belong(string id){           //判断站点是否位于该线路中
        int i;
        i=belong_line.find(id);
        if(i>=0)
            return 1;
        return 0;
    }
    string get_belong(){                //获取站点的所属线路
        return belong_line;
    }
    void add_near_station(station *a){  //添加站点的邻近站点
        near_station[count++]=a;
    }
    station ** get_near_station(){      //获得站点的所有邻近站点
        return near_station;
    }
    int get_near_station_num(){         //获得站点所有邻近站点的数量
        return count;
    }
};

class subway{                    //地铁类型
    private:
    string id;                  //地铁线路的id
    string full_people;         //地铁线路的满员人数
    string total_long;          //地铁线路总长度（km）
    string total_station_num;       //地铁线路经过的站点总数
    int count;                      
    station **line;             //地铁线路
    float crowd;                    //拥挤度
    public:
    subway(){                       //初始化变量
        count=0;
        id= "";
        full_people="";
        total_long="";
        total_station_num="";
    }
    void set_id(string strs){       //设置id
        id=strs;
    }
    string get_id(){                //获取id
        return id;
    }
    void set_full_people(string strs){      //设置满员人数
        full_people=strs;
    }
    string get_full_people(){               //获取满员人数
        return full_people;
    }
    void set_total_long(string strs){       //设置地铁线总长度（km）
        total_long= strs;
    }
    string get_total_long(){            //获得地铁线总长度
        return total_long;
    }
    void set_total_station_num(string strs){        // 设置总站点数量
        total_station_num=strs;
    }
    string get_total_station_num(){             //获取总站点数量
        return total_station_num;
    }
    void init_station_line(){                   //初始化线路
        int num = atoi(total_station_num.c_str());
        line = (station **)malloc(sizeof(station *)*num);
    }
    void add_station_line(station * a){         //线路添加站点
        line[count++]=a;
    }
    station * get_station(int num)              //获取该线路某个站点的数据
    {
        return line[num];
    }
    void set_crowd(float a)
    {
        crowd = a;
    }
    float get_crowd(void)
    {
        return crowd;
    }
};
class crowd_output{
    public:
    string way;
    float time;
    float crowd;
    float fare;
    crowd_output()
    {
        way = "";
        time = 0;
        crowd = 0;
        fare = 0;
    }
};