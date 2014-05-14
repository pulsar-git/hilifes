#ifndef _HL_TEST_EVENT_MANAGER_H_
#define _HL_TEST_EVENT_MANAGER_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "precompiled.h"


struct test_event_manager
{
	void start();
	void shutdown();
	void pull();
	void push();
};

struct test_event_manager_suite : public test_suite
{
public:
	test_event_manager_suite(void);
	~test_event_manager_suite(void){};
};

#endif  /* _HL_TEST_EVENT_MANAGER_H_ */ 
