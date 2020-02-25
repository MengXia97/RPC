#pragma once
#include "echo.pb.h"
#include "TcpConnect.h"
#include "mainwindow.h"

//using namespace google::protobuf;

class RPCServerService: public echo::EchoService
{
public:
	RPCServerService(TcpConnection * con);
	~RPCServerService(void);
protected:
	TcpConnection * m_tcpCon;
};

class EchoImplService :public RPCServerService{
public:
	EchoImplService(TcpConnection * con, MainWindow* ui);
    void Echo(google::protobuf::RpcController* controller,
		const echo::EchoRequest* request,
		echo::EchoResponse* response,
        google::protobuf::Closure* done) ;
private:
	MainWindow* ui;
};

class EchoBackImplService :public RPCServerService{
private:
	echo::EchoService::Stub *m_stubService;
public:
	EchoBackImplService(TcpConnection * con);
    void Echo(google::protobuf::RpcController* controller,
		const echo::EchoRequest* request,
		echo::EchoResponse* response,
        google::protobuf::Closure* done) ;
};
