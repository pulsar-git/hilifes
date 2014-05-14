#ifndef _HL_NETWORK_SERVER_SIMPLE_H_
#define _HL_NETWORK_SERVER_SIMPLE_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"

namespace hilife
{
	class network_server_simple
	{
	public:
		network_server_simple(void);
		~network_server_simple(void);
		int run();
		static ACE_Reactor *g_reactor;
	};
}

#endif  /* _HL_NETWORK_SERVER_SIMPLE_H_ */ 
