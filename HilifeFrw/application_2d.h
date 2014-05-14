#ifndef _HL_APPLICATION_2D_H_
#define _HL_APPLICATION_2D_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "application_base.h"

namespace hilife
{
	class application_2d : public application_base
	{
	public:
		application_2d(void);
		~application_2d(void);
		int setup();
		int loop();
		int destroy();
	};
}
#endif  /* _HL_APPLICATION_2D_H_ */ 
