
#include <iostream>
#include <string>
#include "cfig.h"

int main()
{

	// Cfig config("config.ini");

	Cfig config;
	config.setCommentPrefix(Cfig::HASH);
	config.load("config.ini");

	int port = config.get("server", "port").toInt();
	std::string host = config.get("server", "host");
	bool debug = config.get("server", "debug").toBool();
	float timeout = config.get("server", "timeout").toFloat(10.25f);
	
	std::cout << "Server Configuration:" << std::endl;
	std::cout << "Hostname: " << host << std::endl;
	std::cout << "Port: " << port << std::endl;
	std::cout << "Debug: " << debug << std::endl;
	std::cout << "Timeout: " << timeout << std::endl;
			
	
	return 0;
}
