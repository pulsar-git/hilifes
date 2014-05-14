#include "precompiled.h"
using boost::unit_test::test_suite;

#include "test_attribute_manager.h"
#include "test_event_manager.h"
//
//// most frequently you implement test cases as a free functions
//void free_test_function()
//{
//    // reports 'error in "free_test_function": test 2 == 1 failed'
//    BOOST_CHECK(2 == 1); // non-critical test => continue after failure
//
//    int* p = (int*)0;
//    *p = 0;
//}
#include "pre.h"
#include <log4cpp/PropertyConfigurator.hh>

test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
	try
		{
			log4cpp::PropertyConfigurator::configure("D:\\GGA\\Projets\\Personnal\\Hilife\\bin\\Data\\log4cpp.properties");
		} 
		catch(log4cpp::ConfigureFailure& f) 
		{
			std::cout << "Configure Problem " << f.what() << std::endl;
		}

    // create the top test suite
   test_suite* top_test_suite(BOOST_TEST_SUITE("Master test suite"));

   // add test suites to the top test suite
   top_test_suite->add(new test_attribute_manager_suite());
   top_test_suite->add(new test_event_manager_suite());

   return top_test_suite;
}

// EOF