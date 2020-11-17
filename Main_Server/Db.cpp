#include "Db.h"

Db::Db()
{
    conn = mysql_init(NULL);
    cout << "Db()" << endl;
}

bool Db::Connect()
{
    handle = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

    if(handle == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(handle));
        return false;
    }

	mysql_query(handle,"set session character_set_connection=utf8;");
	mysql_query(handle,"set session character_set_results=utf8;");
	mysql_query(handle,"set session character_set_client=utf8;");

    cout << "DB connect()" << endl;

    return true;
}

bool Db::Disconnect()
{
    mysql_close(handle);
    cout << "DB disconnect()" << endl;
    return true;
}

Db::~Db()
{
    cout << "~Db()" << endl;
}
//
MYSQL_RES* Db::location_info(string dotX,string dotY)
{
    int query_stat;
	string query = "SELECT province, city, medical_institution, address, weekday_operating_hours, saturday_operating_hours, sunday_operating_hours, representative_phone, lat, lng, ";
    query += "(6371 * acos( cos( radians( "+dotX+" ) ) * cos( radians( lat ) ) ";
    query += "* cos( radians( lng ) - radians( "+dotY+" ) ) ";
    query += "+ sin( radians( "+dotX+" ) ) ";
    query += "* sin( radians( lat ) ) ) ) AS distance ";
    query += "FROM clinic HAVING distance <= 3 ";
    query += "ORDER BY distance";
    
    cout << query << endl; // 디버깅 중...

	query_stat = mysql_query(conn, query.c_str());
	if (query_stat != 0)
	{
		cout << "주소 정보 가져오기 실패" << endl;
		fprintf(stderr, "Mysql query error : %s", mysql_error(conn));
	}
	sql_result = mysql_store_result(conn);
    cout<<"디버깅... => MYSQL_RES* Db::location_info(string dotX,string dotY)"<<endl;
    return sql_result;
}