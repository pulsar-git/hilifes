#ifndef _HL_TEST_ATTRIBUTE_MANAGER_H_
#define _HL_TEST_ATTRIBUTE_MANAGER_H_

#pragma once
#include ".\precompiled.h"
#include "pre.h"

#include "attribute_manager.h"


struct test_attribute_manager
{
	test_attribute_manager(void);
	~test_attribute_manager(void);
	void _create();
	void _delete();
	void _set();
	void _get();
protected:
	hilife::AttributeManager *_manager;
	int _int;
	bool _bool;
	float _float;
	std::string _string;
	Ogre::Vector3 _vect3;
};

struct test_attribute_manager_suite : public test_suite
{
public:

   test_attribute_manager_suite();
   ~test_attribute_manager_suite(){}

};

#endif  /*_HL_TEST_ATTRIBUTE_MANAGER_H_*/ 
