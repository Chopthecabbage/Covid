#pragma once

#include "Point.h"
#include "Location.h"
#include "DbHandler.h"

class Server
{
    private:
        int serv_sock; // 서버소켓
        struct sockaddr_in serv_adr; // IPv4 기반의 주소표현을 위한 구조체 (서버용)
    public:
        Server(); // 서버설정
        ~Server(); // 서버종료
        void Error_Handling(string msg);
        void Server_Execute(); // 서버실행 
        void Working_Thread(int clnt_sock);
};