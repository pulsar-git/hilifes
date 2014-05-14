#ifndef _HL_ENTITY_FACTORY_H
#define _HL_ENTITY_FACTORY_H

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "entity.h"


using namespace hilife;

namespace hilife
{

	class _HilifeExport entity_factory
	{
	public:
		entity_factory(void);
		~entity_factory(void);
		entity *load(const std::string &filename);
		void load_all(const std::string &pathname);
		static entity_factory& instance();

	protected:
		entity *create_entity(const std::string &className);
	private:
		static log4cpp::Category* logger ;
	};
}

#endif //_HL_ENTITY_FACTORY_H
