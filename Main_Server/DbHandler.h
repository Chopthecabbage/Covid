#pragma once

#include "Db.h"
#include "Point.h"
#include "Location.h"

class DbHandler
{
    private:
        Db db;
    public:
        DbHandler();
        ~DbHandler();
        Db& GetDb();
        void location_info(int sock);

};