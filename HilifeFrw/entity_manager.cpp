#include "stable_headers.h"
#include <boost/pool/detail/singleton.hpp>
#include "entity_manager.h"

namespace hilife
{

	log4cpp::Category* entity_manager::logger ;
	entity_manager::entity_manager(void)
	{
		LOGGER("entity_manager");
		LOGGER_INFO << "Starting up";
		_map.clear();
	}

	entity_manager::~entity_manager(void)
	{
		LOGGER_INFO << "Shutting down";
		hashmap<std::string,hilife::entity*>::iterator iter;
		hilife::entity *ent=0;
		for(iter=_map.begin();iter!=_map.end();iter++)
		{
			ent=(*iter).second;
			//Don't Do it, or it will segfault, hash_map iterator is inconsistent!
			//_map.erase(ent->name());
			delete ent;
			(*iter).second=0;
		}
		_map.clear();
	}

	int entity_manager::add(hilife::entity *entity)
	{
		_map[entity->name()]=entity;
		return 0;
	}
	hilife::entity* entity_manager::find(std::string &name)
	{
		LOGGER_DEBUG << "Looking entity [" << name << "]";
		hilife::entity *ent=0;
		ent=_map[name];
		if(!ent)
		{
			LOGGER_WARN << "Entity is null";
			//report();
		}
		return ent;
	}

	void entity_manager::report(void)
	{
		LOGGER_DEBUG << "Reporting:";
		hashmap<std::string,hilife::entity*>::iterator iter;
		hilife::entity *ent=0;
		LOGGER_DEBUG << "Hashmap [" << &_map << "]";
		for(iter=_map.begin();iter!=_map.end();iter++)
		{
			ent=(*iter).second;
			LOGGER_DEBUG << "Name [" << (*iter).first << "] -> Entity [" << ent << "]";
		}
	}
	int entity_manager::remove(std::string &name)
	{
		hilife::entity *ent=0;
		ent=_map[name];
		_map.erase(name);
		delete ent;

		return 0;
	}

	entity_manager& entity_manager::instance()
	{
		return boost::details::pool::singleton_default<entity_manager>::instance();
	}
}
