#include "stable_headers.h"
#include "network_manager.h"

#include <boost/pool/detail/singleton.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/bind.hpp>

#include "network_server_simple.h"

namespace hilife
{
	log4cpp::Category* network_manager::logger ;
	network_manager::network_manager(void):_network_thread(0)
	{
		LOGGER("network_manager");
		LOGGER_INFO << "Starting up";
	}

	network_manager::~network_manager(void)
	{
		LOGGER_INFO << "Shuting down";
	}

	network_manager& network_manager::instance()
	{
		return boost::details::pool::singleton_default<network_manager>::instance();
	}

	void network_manager::start()
	{
		LOGGER_INFO << "start()";
		_network_thread = new boost::thread ( boost::bind(&network_manager::loop,this) );

	}
	void network_manager::shutdown()
	{
        LOGGER_INFO << "shutdown()";
		boost::xtime mTime;
		mTime.sec=10;
		mTime.nsec=0;
		if(_network_thread)
			_network_thread->sleep(mTime);
	}

	void network_manager::loop()
	{
		//int i;
		//Si on est dans le cas du serveur...
		network_server_simple server;
		server.run();
		//Sinon ... client :^)

	}
}