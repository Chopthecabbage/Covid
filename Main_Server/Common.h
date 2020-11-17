#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <mutex>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "/usr/include/mariadb/mysql.h"

// DB연동 관련
#define DB_HOST "10.10.20.240"
#define DB_USER "root"
#define DB_PASS "123"
#define DB_NAME "woo"
#define DB_PORT 3306
// TCP/IP 서버포트
#define PORT 9013
#define BASIC_SIZE 50
#define SPECIFIC_SIZE 100

using namespace std;