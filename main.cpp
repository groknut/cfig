
#include <iostream>
#include <string>
#include "cfig.h"

int main()
{

	Cfig config("config.ini", Cfig::EQUAL, Cfig::HASH);

	int port = config.get("server", "port").toInt();
	std::string host = config.get<std::string>("server", "hosta", std::string("127.0.0.1"));
	bool debug = config.get("server", "debug").toBool();
	float timeout = config.get<float>("", "", 10.25f);

	CfigValue test = config.get("server", "char");
	
	std::cout << "Server Configuration:" << std::endl;
	std::cout << "Hostname: " << host << std::endl;
	std::cout << "Port: " << port << std::endl;
	std::cout << "Debug: " << debug << std::endl;
	std::cout << "Timeout: " << timeout << std::endl;
	std::cout << "Mark: " << test.type() << std::endl;
	std::cout << "test:" << config.has("main", "test") << std::endl;
	std::cout << "test:" << config.get<int>("test", 20) << std::endl;
	std::cout << "test:" << config.get<int>("main", "test", 20) << std::endl;
	
	
	return 0;
}
