#include "Server.h"

Server::Server()
{
    int nSockOpt = 1;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4인터넷 프로토콜 체계의 연결지향형 데이터 전송용 소켓생성

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; // 어떤 주소체계를 사용하는지 -> IPv4 인터넷 프로토콜에 적용하는 주소체계
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // ip주소가 어떻게 되는지 -> 32비트 ip주소저장,
    serv_adr.sin_port = htons(PORT); // port 번호는 어떻게 되는지 

    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &nSockOpt, sizeof(nSockOpt)); 
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		Error_Handling("bind error");
    cout << "Server()" << endl;
}

Server::~Server()
{
    cout << "~Server()" << endl;
    close(serv_sock);
}

void Server::Working_Thread(int clnt_sock)
{
    DbHandler db_handler;
    
    int sock = clnt_sock;
    int signal;
    int len;

    db_handler.GetDb().Connect();

    while(1)
    {
        len = read(sock,&signal,sizeof(int)); // 클라이언트 -> 중계서버로부터 전달되는 시그널 데이터를 읽다.
        cout<<"디버깅 중... => signal: "<<signal<<endl;
        if(len == 0)
            break;
        switch(signal)
        {
            case 1:
                cout<<"디버깅 중... => db_handler.location_info(sock)"<<endl;
                db_handler.location_info(sock);
                break;
            default:
                break;
        }
    }
    db_handler.GetDb().Disconnect();
}

void Server::Error_Handling(string msg)
{
    cout << msg << endl;
	exit(1);
}

void Server::Server_Execute()
{
    int clnt_sock; // 클라이언트 소켓
    struct sockaddr_in clnt_adr; // IPv4 기반의 주소표현을 위한 구조체 (클라이언트용)
    int clnt_adr_sz;
    int cnt;

    if(listen(serv_sock, 5)==-1)
        Error_Handling("listen error"); 

    while(1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr,(socklen_t *)&clnt_adr_sz);
        if(clnt_sock < 0)
        {
            Error_Handling("accept() error");
            break;
        }
		cout << "[ Connect IP: " << inet_ntoa(clnt_adr.sin_addr) << " SOCKET: " << clnt_sock << " ]" << endl;
        thread th(&Server::Working_Thread,this,clnt_sock);
        th.detach();
    }
}