#ifndef HL_ENTITY_LIGHT_3D_
#define HL_ENTITY_LIGHT_3D_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "entity_3d.h"

namespace hilife
{
	class _HilifeExport entity_light_3d :
		public entity_3d
	{
	public:
		//entity_light_3d(void);
		entity_light_3d(AttributeManager *att);
		~entity_light_3d(void);
		virtual int initialize(void);
		virtual int create(void);
	private:
		Ogre::Vector3 _direction;
		int _type;
	};
}

#endif //HL_ENTITY_LIGHT_3D_
