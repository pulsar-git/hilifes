#ifndef _HL_BASE_ENTITY_H
#define _HL_BASE_ENTITY_H

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

namespace hilife
{
class entity;

class _HilifeExport base_entity
	{
	public:
		base_entity(void);
		virtual ~base_entity(void);
		virtual int create(void)=0;
		virtual int initialize(void){return 0;};
		virtual int update_attribute_listener(const std::string &name,const std::string &value)=0;
		virtual int loop_update()=0;
		entity * parent(void){return _parent;};
		void parent(entity *ent){_parent=ent;};
		virtual int event_listener(event *evt)=0;
		
		AttributeManager &manager(void){return *_attribute_manager;};
        

	protected:
		bool _initialized;
		AttributeManager *_attribute_manager;

	private:
		hilife::entity *_parent;


	};
}

#endif //_HL_BASE_ENTITY_H
