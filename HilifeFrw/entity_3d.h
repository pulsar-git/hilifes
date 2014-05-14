#ifndef _HL_ENTITY_3D_H_
#define _HL_ENTITY_3D_H_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "base_entity.h"

namespace hilife
{
	class _HilifeExport entity_3d :
		public base_entity
	{
	public:
		//entity_3d(void);
		entity_3d(AttributeManager *att);
		~entity_3d(void);
		//Receive Attributes Updates...
		virtual int update_attribute_listener(const std::string &name,const std::string &value);

		//Sent during game main loop update if registered...
		virtual int loop_update(/*delta time?*/){return 0;}
		virtual int initialize(void);
		virtual int create(void);
		virtual int event_listener(event *evt);
	
	protected:
		std::string _mesh;
		Ogre::Vector3 _scale;
		Ogre::Entity *_ent_3d;
		Ogre::SceneNode *_node_3d;
		int _size;
	};
}

#endif /* _HL_ENTITY_3D_H_ */

