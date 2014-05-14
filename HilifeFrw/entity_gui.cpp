#include "stable_headers.h"
#include "entity_gui.h"
#include "event.h"
#include "entity_gui_context_manager.h"

namespace hilife
{
	entity_gui::entity_gui(AttributeManager* att)
	{
		_attribute_manager=att;
	}

	entity_gui::~entity_gui()
	{
	}

	int entity_gui::initialize(void)
	{
		
		return 0;
	}
	int entity_gui::create(void)
	{

		return 0;
	}
	int entity_gui::event_listener(event *evt)
	{
		//On peut faire ca par rapport au parent juste je pense!
		if(evt->entity()==this->parent())
			if(evt->type() == event::HL_SELECTED)
				entity_gui_context_manager::instance().show_context();
			if(evt->type() == event::HL_UNSELECTED)
				entity_gui_context_manager::instance().hide_context();
				
		return 1;
	}
	int entity_gui::update_attribute_listener(const std::string &name,const std::string &value)
	{
		return 0;
	}
}