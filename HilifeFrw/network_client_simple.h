#ifndef _HL_NETWORK_CLIENT_SIMPLE_H_
#define _HL_NETWORK_CLIENT_SIMPLE_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "ace/SOCK_Connector.h"

namespace hilife
{
	class network_client_simple : public ACE_SOCK_Stream
	{
	public:
		network_client_simple();
		~network_client_simple();
		int run();
	private:
		static log4cpp::Category* logger ;
	};
}

#endif  /* _HL_NETWORK_CLIENT_SIMPLE_H_ */ 
