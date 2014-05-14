#include "stable_headers.h"

#include "entity.h"
#include "attribute_manager.h"
#include "event.h"
#include "event_manager.h"
#include <boost/bind.hpp>

namespace hilife
{
	log4cpp::Category* entity::logger ;

	entity::entity(void):
	_entity_3d(0),_entity_gui(0)
	{
		LOGGER("entity");
		_attribute_manager = new AttributeManager();
		_list.clear();
	}

	entity::~entity(void)
	{
		LOGGER_DEBUG << "Destructing entity [" << this->name() << "]";
		delete _attribute_manager;
		_attribute_manager=0;
		
		_list.clear();
	}

	int entity::update_attribute_listener(const std::string &name,const std::string &value)
	{
		LOGGER_DEBUG << "Updating Attribute name=[" << name << "] value=[" << value <<"]";
		
		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::update_attribute_listener,_1,name,value)
					 );
		return 0;
	}

	int entity::set_attribute(const std::string &name,const std::string &value)
	{
		if(_attribute_manager)
		{
			_attribute_manager->setAttributeValueByString(name,value);
			this->update_attribute_listener(name,value);
		}
		return 0;
	}

	const std::string &entity::get_attribute_value(const std::string &name)
	{
		if(_attribute_manager)
		{
			return *(new std::string("won't work"));
		}
		return *(new std::string("default"));
	}

	int entity::create(void)
	{
		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::create,_1)
					 );

		event_manager::instance().connect(this);
		return 0;		
	}

	int entity::initialize(void)
	{
		manager().addAttribute("Position",_position);
		parent(this);		

		LOGGER_DEBUG << "Initializing";
		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::initialize,_1)
					 );

		return 0;
	}

	int entity::event_listener(event *evt)
	{
		LOGGER_DEBUG << "Entity [" <<this->name() <<"] -- Received event [" << evt->type() <<"]";

		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::event_listener,_1,evt)
					 );
		return 1;
	}
}
