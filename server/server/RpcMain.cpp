// RpcServer.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include "echo.pb.h"
#include "TcpConnect.h"
#include <boost/thread/thread.hpp>   
#include "RPCServerService.h"

using namespace boost::asio;

int main()    
{
	io_service ios;
	std::cout<<"start server..."<<std::endl;
	TcpServer *server = new TcpServer(ios);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &ios));
	//ios.run();
	while (true)
	{
		string in;
		std::cin >> in;
		server->echo(in);
	}
  }
