#include "DbHandler.h"

DbHandler::DbHandler()
{
}

Db& DbHandler::GetDb()
{
    return db;
}

DbHandler::~DbHandler()
{
}

void DbHandler::location_info(int sock)
{
    Point p;
    read(sock,&p,sizeof(Point));
    
    string dotX = to_string(p.GetX());
    string dotY = to_string(p.GetY());
    cout<<"받은 dotX: "<<dotX<<" 받은 dotY: "<<dotY<<endl;
    Db d;
    d.Connect();

    MYSQL_RES *result;
	MYSQL_ROW row;
    result=d.location_info(dotX,dotY);
    cout<<"x"<<endl;    
    Location l[10];
    int l_cnt=0;
    string diversiform;
    while(row = mysql_fetch_row(result))
    {
        cout<<"xx"<<endl;
        diversiform=row[0];
        char province[BASIC_SIZE];
        strcpy(province,diversiform.c_str());
        l[l_cnt].SetProvince(province);
        
        diversiform=row[1];
        char city[BASIC_SIZE];
        strcpy(city,diversiform.c_str());
        l[l_cnt].SetCity(city);
        
        diversiform=row[2];
        char medical_institution[BASIC_SIZE];
        strcpy(medical_institution,diversiform.c_str());
        l[l_cnt].SetMedical(medical_institution);

        diversiform=row[3];
        char address[SPECIFIC_SIZE];
        strcpy(address,diversiform.c_str());
        l[l_cnt].SetAddress(address);

        diversiform=row[4];
        char weekday_operating_hours[BASIC_SIZE];
        strcpy(weekday_operating_hours,diversiform.c_str());
        l[l_cnt].SetWeekday(weekday_operating_hours);

        diversiform=row[5];
        char saturday_operating_hours[BASIC_SIZE];
        strcpy(saturday_operating_hours,diversiform.c_str());
        l[l_cnt].SetSaturday(saturday_operating_hours);

        diversiform=row[6];
        char sunday_operating_hours[BASIC_SIZE];
        strcpy(sunday_operating_hours,diversiform.c_str());
        l[l_cnt].SetSunday(sunday_operating_hours);

        diversiform=row[7];
        char representative_phone[BASIC_SIZE];
        strcpy(representative_phone,diversiform.c_str());
        l[l_cnt].SetPhone(representative_phone);

        diversiform=row[8];
        char lat[BASIC_SIZE];
        strcpy(lat,diversiform.c_str());
        l[l_cnt].SetLat(lat);

        diversiform=row[9];
        char lng[BASIC_SIZE];
        strcpy(lng,diversiform.c_str());
        l[l_cnt].SetLng(lng);
        ++l_cnt;
    }
    cout<<"l_cnt: "<<l_cnt<<endl;
    cout<<"장소 클래스 디버깅 중..."<<endl;
    for(int i=0; i<l_cnt; i++)
    {
        l[i].ShowLocation();
    }

    if(l_cnt==0)
        write(sock,&l_cnt,sizeof(int));
    else if(l_cnt!=0)
    {
        write(sock,&l_cnt,sizeof(int));
        write(sock,&l,sizeof(Location)*10);
        cout<<"장소 클래스 크기: "<<sizeof(Location)<<" 배열 크기: "<<sizeof(Location)*10<<endl;
    }

    mysql_free_result(result);
    d.Disconnect();
}