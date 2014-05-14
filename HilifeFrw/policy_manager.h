#ifndef _HL_POLICY_MANAGER_H_
#define _HL_POLICY_MANAGER_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

namespace hilife
{
#define POLICY_REQUIRED(a) if(hilife::policy_manager::instance().value(a))


	enum hl_policies {HL_PL_CLIENT,HL_PL_SERVER,HL_PL_3D,HL_PL_GUI,HL_PL_NETWORK,HL_PL_SOUND,HL_PL_MAX};

	class _HilifeExport policy_manager
	{
	public:
		policy_manager(void);
		~policy_manager(void);
		bool value(hl_policies a);
		void value(hl_policies a,bool v);
		static policy_manager& instance();
	private:
		bool _policies[HL_PL_MAX];
		static log4cpp::Category* logger ;
	};
}
#endif  /* _HL_POLICY_MANAGER_H_ */ 
