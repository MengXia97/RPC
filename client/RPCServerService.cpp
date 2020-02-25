#include "RPCServerService.h"
#include <iostream>

RPCServerService::RPCServerService(TcpConnection * con) :m_tcpCon(con){
	con->addService(this);
}
RPCServerService::~RPCServerService(void){}




EchoImplService::EchoImplService(TcpConnection * con, MainWindow* ui) :RPCServerService(con)
{
	this->ui = ui;
}
void EchoImplService::Echo(google::protobuf::RpcController* controller,
	const echo::EchoRequest* request,
	echo::EchoResponse* response,
	google::protobuf::Closure* done) {
	this->ui->updateLog(request->message());
}

EchoBackImplService::EchoBackImplService(TcpConnection * con) :RPCServerService(con){
	m_stubService = new echo::EchoService::Stub(con);
}
void EchoBackImplService::Echo(google::protobuf::RpcController* controller,
	const echo::EchoRequest* request,
	echo::EchoResponse* response,
	google::protobuf::Closure* done) {
	std::cout << "RPC,message:" << request->message() << std::endl;
	//TODO 能否提取
	echo::EchoRequest requestBack;
	requestBack.set_message(request->message());
	m_stubService->Echo(NULL, &requestBack, NULL, NULL);
	//m_proxy->Echo(request->message());
}
