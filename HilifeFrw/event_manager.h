#ifndef _HL_EVENT_MANAGER_H_
#define _HL_EVENT_MANAGER_H_

#include "pre.h" 
#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include <boost/signal.hpp>
#include "event.h"
#include "entity.h"

namespace hilife
{
	class _HilifeExport event_manager
	{
	public:
		event_manager(void);
		~event_manager(void);

		bool connect( /*int(entity::*f)(event*,entity*),*/ entity *);

		void fire_event(event *);
		void fire_event(event::event_type , std::string &name);

		static event_manager& instance();

		void push_event(event *);
		event* pull_event();

	private:
		ACE_Message_Queue_Ex <class event,ACE_MT_SYNCH> _queue;
		boost::signal<void (event*)> _sig;
		static log4cpp::Category* logger ;

	};

}
#endif  /* _HL_EVENT_MANAGER_H_ */ 
