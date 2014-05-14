#ifndef _HL_APPLICATION_BASE_H_
#define _HL_APPLICATION_BASE_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#ifndef _HL_APPLICATION_BASE_H_
#endif /* HL_HAS_PRAGMA_ONCE*/

#define _HL_APPLICATION_BASE_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

namespace hilife
{
	class application_base
	{
	public:
		application_base(void){};
		virtual ~application_base(void){};
		virtual int setup()=0;
		//virtual int create()=0;
		virtual int destroy()=0;
		virtual int loop()=0;
	};

}

class application_base
{
public:
	application_base(void);
	~application_base(void);
};
#endif  /* _HL_APPLICATION_BASE_H_ */ 

#endif  /* _HL_APPLICATION_BASE_H_ */ 
