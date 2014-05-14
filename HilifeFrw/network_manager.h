#ifndef _HL_NETWORK_MANAGER_H_
#define _HL_NETWORK_MANAGER_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "event.h"
namespace boost
{
	class thread;
}

namespace hilife
{
	class _HilifeExport network_manager
	{
	public:
		network_manager(void);
		~network_manager(void);
		static network_manager& instance();
		void start();
		void shutdown();
		void loop();

        
	private:
		static log4cpp::Category* logger ;
		boost::thread *_network_thread;
	};
}

#endif  /* _HL_NETWORK_MANAGER_H_ */ 
