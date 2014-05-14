#include "stable_headers.h"
#include "policy_manager.h"
#include <boost/pool/detail/singleton.hpp>

namespace hilife
{
	log4cpp::Category* policy_manager::logger ;
	policy_manager& policy_manager::instance()
	{
		return boost::details::pool::singleton_default<policy_manager>::instance();
	}

	policy_manager::policy_manager(void)
	{
		LOGGER("policy_manager");
		LOGGER_INFO << "Starting up";
		for(int i=0;i<HL_PL_MAX;++i)
			_policies[i]=false;
	}

	policy_manager::~policy_manager(void)
	{
		LOGGER_INFO << "Shutting down";
	}
	bool policy_manager::value(hl_policies policy)
	{
		return _policies[policy];
	}
	void policy_manager::value(hl_policies policy,bool value)
	{
		_policies[policy]=value;
	}
}