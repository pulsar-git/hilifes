#ifndef _HL_ENTITY_GUI_H_
#define _HL_ENTITY_GUI_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "base_entity.h"

namespace hilife
{
	class _HilifeExport entity_gui 
		: public base_entity
	{
	public:
		entity_gui(AttributeManager* att);
		~entity_gui();
		virtual int loop_update(/*delta time?*/){return 0;}
		virtual int initialize(void);
		virtual int create(void);
		virtual int event_listener(event *evt);
		virtual int update_attribute_listener(const std::string &name,const std::string &value);
	};
}

#endif  /*_HL_ENTITY_GUI_H_*/ 
