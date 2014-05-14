#include "precompiled.h"
#include "test_event_manager.h"
#include "event_manager.h"
using namespace hilife;

void test_event_manager::start()
{
	network_manager::instance().start();
}

void test_event_manager::shutdown()
{
	network_manager::instance().shutdown();
}

void test_event_manager::pull()
{
	event_manager &mgr = event_manager::instance();
	
	event *evt= new event(event::HL_CREATE);
	event *evt2= new event(event::HL_SHUTDOWN);
	mgr.push_event(evt);
	mgr.push_event(evt2);

	evt=0;
	evt2=0;

	evt2=mgr.pull_event();
	evt=mgr.pull_event();
	BOOST_CHECK( evt2->type()==event::HL_CREATE );
	BOOST_CHECK( evt->type()==event::HL_SHUTDOWN );
	BOOST_CHECK( mgr.pull_event()==0 );

}

void test_event_manager::push()
{

}

test_event_manager_suite::test_event_manager_suite(void)
{
	// create an instance of the test cases class
      boost::shared_ptr<test_event_manager> instance(new test_event_manager());

      // create the test cases
	  test_case* test_1 = BOOST_CLASS_TEST_CASE( &test_event_manager::start, instance );
	  test_case* test_2 = BOOST_CLASS_TEST_CASE( &test_event_manager::pull, instance );
	  test_case* test_3 = BOOST_CLASS_TEST_CASE( &test_event_manager::push, instance );

	  //Last one!
	  test_case* test_n = BOOST_CLASS_TEST_CASE( &test_event_manager::shutdown, instance );

      // add the test cases to the test suite
      add(test_1);
      add(test_2);
	  add(test_3);
	  add(test_n);
}

