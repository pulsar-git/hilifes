#include "stable_headers.h"
#include <boost/pool/detail/singleton.hpp>
#include <boost/bind.hpp>
#include "event_manager.h"
#include "entity_manager.h"

namespace hilife
{
	log4cpp::Category* event_manager::logger ;

	event_manager::event_manager(void)
	{
		LOGGER("event_manager");
		LOGGER_INFO << "Starting up";
		_queue.open();
		_queue.activate();
	}

	event_manager::~event_manager(void)
	{
		LOGGER_INFO << "Shuting down";
		_queue.deactivate();
		_queue.flush();
	}

	
	bool event_manager::connect(entity *ent)
	{
		LOGGER_DEBUG << "Connecting :" << ent->name();
		_sig.connect(boost::bind(&entity::event_listener,ent,_1));
		return true;
	}
	
	void event_manager::fire_event(event *evt)
	{
		LOGGER_DEBUG << "Firing event :" << evt->type();
		_sig(evt);
	}

	void event_manager::fire_event(event::event_type event_type, std::string & obj_name)
	{
		entity *ent=entity_manager::instance().find(obj_name);
		event evt(event_type,ent);
		fire_event(&evt);
	}
	event_manager& event_manager::instance()
	{
		return boost::details::pool::singleton_default<event_manager>::instance();
	}
	void event_manager::push_event(event *evt)
	{
		LOGGER_DEBUG << "push_event()";
		_queue.enqueue(evt);
	}
	event* event_manager::pull_event()
	{
		LOGGER_DEBUG << "pull_event()";
		if(!_queue.is_empty())
		{
			event *evt=0;
			_queue.dequeue(evt);
			return evt;
		}
		else
			return 0;
	}


}