#ifndef _HL_EVENT_H_
#define _HL_EVENT_H_

#include "pre.h"
#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/


namespace hilife
{

	class _HilifeExport event
	{
	public:
		enum event_type {HL_UNDEF,HL_CREATE,HL_INIT,HL_SELECTED,HL_UNSELECTED,HL_SHUTDOWN/* */,HL_MAX_EVENT};

		event(void):_type(HL_UNDEF){}
		event(event_type event):_type(event),_ent(0){}
		event(event_type event,entity * ent):_type(event),_ent(ent){}
		~event(void){};

		event_type type(){return _type;}
		entity *entity(){return _ent;}
	private:
		event_type			_type;
		hilife::entity *	_ent;
	};
}

#endif  /*_HL_EVENT_H_*/
