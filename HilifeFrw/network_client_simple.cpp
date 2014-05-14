#include "stable_headers.h"
#include "network_client_simple.h"


namespace hilife
{
	log4cpp::Category* network_client_simple::logger;

	network_client_simple::network_client_simple()
	{
		LOGGER("network_client_simple");
		LOGGER_INFO << "Starting up";
	}

	network_client_simple::~network_client_simple()
	{
		LOGGER_INFO << "Shutting down";
	}

	int network_client_simple::run()
	{
		ACE_SOCK_Connector connector;
/*		ACE_INET_Addr addr (port, server);

		if (connector.connect (*this, addr) == -1)
			ACE_ERROR_RETURN ((LM_ERROR,
							"%p\n",
							"open"),
							-1);*/
		return 0;
	}
}