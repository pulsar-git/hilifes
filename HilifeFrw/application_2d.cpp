#include "stable_headers.h"
#include "application_2d.h"

namespace hilife
{

	application_2d::application_2d(void)
	{
	}

	application_2d::~application_2d(void)
	{
	}

	application_2d::setup()
	{
		return 0;
	}

	application_2d::loop()
	{
		std::string tmpstring;

		for(;;)
		{
			std::cin >> tmpstring;
			
			if(tmpstring.compare("exit")==0)
				break;
		}
		return 0;
	}

	application_2d::destroy()
	{
		return 0;
	}
}