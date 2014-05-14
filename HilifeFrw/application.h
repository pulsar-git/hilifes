#ifndef _HL_APPLICATION_H_
#define _HL_APPLICATION_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "pointer.h"
#include "application_base.h"

namespace hilife
{

	class _HilifeExport application
	{
	public:
		application(void);
		~application(void);
		int setup();
		int destroy();
		int loop();
	protected:
		std::vector< boost::shared_ptr<application_base> > _list;
	};

}
#endif  /* _HL_APPLICATION_H_ */ 
