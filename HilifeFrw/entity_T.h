#ifndef _HL_ENTITY_T_H_
#define _HL_ENTITY_T_H_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "entity.h"

namespace hilife
{
	template <class ENT_3D,class ENT_GUI>
	class entity_T :
		public entity
	{
	public:
		entity_T(void);
		virtual ~entity_T(void);

		virtual int initialize(void);
		//virtual int create(void);
		//virtual int set_attribute(const std::string &name,const std::string &value);
		//virtual const std::string &get_attribute_value(const std::string &name);
		
		//Receive Attributes Updates...
		//virtual int update_attribute_listener(const std::string &name,const std::string &value);

		//Sent during game main loop update if registered...
		//virtual int loop_update(/*delta time?*/){return 0;}

		//virtual int event_listener(event *evt);
	};
}

#if defined (HL_TEMPLATES_REQUIRE_SOURCE)
#include "entity_T.cpp"
#endif /* HL_TEMPLATES_REQUIRE_SOURCE */

#endif //_HL_ENTITY_T_H_

