#include "precompiled.h"
#include "test_attribute_manager.h"

/**
*
*	TODO:
*			Use Boost Floating-point comparison algorithms instead of "=="  for
*			Float Values!
*/
test_attribute_manager::test_attribute_manager(void)
{
}

test_attribute_manager::~test_attribute_manager(void)
{
}

void test_attribute_manager::_create()
{
	_manager=new hilife::AttributeManager();
	_manager->addAttribute("int",_int);
	_manager->addAttribute("bool",_bool);
	_manager->addAttribute("float",_float);
	_manager->addAttribute("string",_string);
	_manager->addAttribute("vect3",_vect3);
	int tint;
	float tfloat;
	bool tbool;
	std::string tstring;
	Ogre::Vector3 tvect3;

	BOOST_REQUIRE( _manager->getAttributeValue("int",tint)==true);
	BOOST_REQUIRE( _manager->getAttributeValue("float",tfloat)==true);
	BOOST_REQUIRE( _manager->getAttributeValue("bool",tbool)==true);
	BOOST_REQUIRE( _manager->getAttributeValue("string",tstring)==true);
	BOOST_REQUIRE( _manager->getAttributeValue("vect3",tvect3)==true);
}

void test_attribute_manager::_delete()
{
	int tint;
	float tfloat;
	bool tbool;
	std::string tstring;
	Ogre::Vector3 tvect3;

	_manager->removeAllAttributes();
	BOOST_CHECK( _manager->getAttributeValue("int",tint)==false);
	BOOST_CHECK( _manager->getAttributeValue("float",tfloat)==false);
	BOOST_CHECK( _manager->getAttributeValue("bool",tbool)==false);
	BOOST_CHECK( _manager->getAttributeValue("string",tstring)==false);
	BOOST_CHECK( _manager->getAttributeValue("vect3",tvect3)==false);

	delete _manager;
	
}

void test_attribute_manager::_set()
{
	int tint=23;
	float tfloat=24;
	bool tbool=true;
	std::string tstring("value test");
	Ogre::Vector3 tvect3(3,4,5);
	

	// Good Types...
	_manager->setAttributeValue("int",tint);
	_manager->setAttributeValue("float",tfloat);
	_manager->setAttributeValue("bool",tbool);
	_manager->setAttributeValue("string",tstring);
	_manager->setAttributeValue("vect3",tvect3);

	BOOST_CHECK(_int == 23);
	BOOST_CHECK(_float==24);
	BOOST_CHECK(_bool == true);
	BOOST_CHECK(!_string.compare("value test"));
	BOOST_CHECK(_vect3.positionEquals(tvect3));

	//Wrong Types...
	BOOST_CHECK(_manager->setAttributeValue("int",tbool) == false);
	BOOST_CHECK(_manager->setAttributeValue("float",tint) == false);
	BOOST_CHECK(_manager->setAttributeValue("bool",tfloat) == false);
	BOOST_CHECK(_manager->setAttributeValue("string",tvect3) == false);
	BOOST_CHECK(_manager->setAttributeValue("vect3",tstring) == false);

	//Value
	_manager->setAttributeValueByString("int","4");
	_manager->setAttributeValueByString("float","4.5");
	_manager->setAttributeValueByString("bool","false");
	_manager->setAttributeValueByString("string","test here");
	_manager->setAttributeValueByString("vect3","3.2 4.3 5.4");

	BOOST_CHECK(_int == 4);
	BOOST_CHECK(_float==4.5);
	BOOST_CHECK(_bool == false);
	BOOST_CHECK(!_string.compare("test here"));
	BOOST_CHECK(_vect3.positionEquals(Ogre::Vector3(3.2,4.3,5.4)));

}

void test_attribute_manager::_get()
{
	int tint;
	float tfloat;
	bool tbool;
	std::string tstring;
	Ogre::Vector3 tvect3;

	_int	= 33;
	_float	= 34;
	_bool	= false;
	_string	= std::string("another value test");
	_vect3	= Ogre::Vector3(4,5,6);

	_manager->getAttributeValue("int",tint);
	_manager->getAttributeValue("float",tfloat);
	_manager->getAttributeValue("bool",tbool);
	_manager->getAttributeValue("string",tstring);
	_manager->getAttributeValue("vect3",tvect3);

	BOOST_CHECK(_int == tint);
	BOOST_CHECK(_float == tfloat);
	BOOST_CHECK(_bool == tbool);
	BOOST_CHECK(_string == tstring);
	BOOST_CHECK(_vect3 == tvect3);

	//Wrong Types...
	BOOST_CHECK(_manager->getAttributeValue("int",tbool) == false);
	BOOST_CHECK(_manager->getAttributeValue("float",tint) == false);
	BOOST_CHECK(_manager->getAttributeValue("bool",tfloat) == false);
	BOOST_CHECK(_manager->getAttributeValue("string",tvect3) == false);
	BOOST_CHECK(_manager->getAttributeValue("vect3",tstring) == false);
	

}

test_attribute_manager_suite::test_attribute_manager_suite() : test_suite("test_attribute_manager_suite")
   {
      // create an instance of the test cases class
      boost::shared_ptr<test_attribute_manager> instance(new test_attribute_manager());

      // create the test cases
      test_case* test_1 = BOOST_CLASS_TEST_CASE( &test_attribute_manager::_create, instance );
	  test_case* test_2 = BOOST_CLASS_TEST_CASE( &test_attribute_manager::_set, instance );
	  test_case* test_3 = BOOST_CLASS_TEST_CASE( &test_attribute_manager::_get, instance );

	  //Last one!
	  test_case* test_n = BOOST_CLASS_TEST_CASE( &test_attribute_manager::_delete, instance );

      // add the test cases to the test suite
      add(test_1);
      add(test_2);
	  add(test_3);
	  add(test_n);


      //add(test_n);
   }