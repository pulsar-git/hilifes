#ifndef _HL_ENTITY_MANAGER_H
#define _HL_ENTITY_MANAGER_H

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "entity.h"

namespace hilife
{
	class _HilifeExport entity_manager
	{
	public:
		entity_manager(void);
		~entity_manager(void);

		int add(hilife::entity *entity);
		hilife::entity * find(std::string &name);
		int remove(std::string &name);

		int register_listener(/*kind of update*/){return 0;};
		int notify_listener(/*Event*/){return 0;};
		void report(void);

		static entity_manager& instance();

	protected:
		hashmap<std::string,hilife::entity*> _map;
	private:
		static log4cpp::Category* logger ;

	};

}
#endif //_HL_ENTITY_MANAGER_H
