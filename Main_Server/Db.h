#pragma once

#include "Common.h"

class Db
{
    private:
        MYSQL *conn;
        MYSQL *handle;
        MYSQL_RES *sql_result;
        MYSQL_ROW sql_row;
    public:
        Db();
        ~Db();
        bool Connect();
        bool Disconnect(); 
        //
        MYSQL_RES* location_info(string dotX,string dotY);
};