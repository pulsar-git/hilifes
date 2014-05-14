#ifndef _HL_ENTITY_H
#define _HL_ENTITY_H

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "base_entity.h"
#include "entity_3d.h"
#include "entity_gui.h"
#include "pointer.h"


namespace hilife
{
	class entity :
		public base_entity
	{
	public:
		entity(void);
		virtual ~entity(void);
		virtual int initialize(void);
		virtual int create(void);
		virtual int set_attribute(const std::string &name,const std::string &value);
		virtual const std::string &get_attribute_value(const std::string &name);
		
		//Receive Attributes Updates...
		virtual int update_attribute_listener(const std::string &name,const std::string &value);

		//Sent during game main loop update if registered...
		virtual int loop_update(/*delta time?*/){return 0;}

		virtual int event_listener(event *);

		//...

		void name(std::string &name){_name=name;}
		void name(std::string name){_name=name;}
		std::string &name(void){return _name;}

	protected:
		hilife::entity_3d * _entity_3d;
		hilife::entity_gui * _entity_gui;
		//entity_physik *_entity_physik;
		//entity_sound *_entity_sound;
		std::vector< boost::shared_ptr<base_entity> > _list;

		static log4cpp::Category* logger ;
		std::string _name;
		Ogre::Vector3 _position;
	};
}

#endif //_HL_ENTITY_H


