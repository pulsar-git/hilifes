#include "stable_headers.h"
#include "application.h"
#include "policy_manager.h"
#include "application_3d.h"
#include "application_2d.h"
#include "entity_factory.h"
#include <boost/bind.hpp>

namespace hilife
{
	application::application(void)
	{
		_list.clear();
	}

	application::~application(void)
	{
		_list.clear();
	}

	int application::setup()
	{
		//Other application creations
		POLICY_REQUIRED(HL_PL_3D)
		{
			_list.push_back( boost::shared_ptr<application_base> ( new application_3d()));
		}
		else
			_list.push_back( boost::shared_ptr<application_base> ( new application_2d()));


		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&application_base::setup,_1)
					 );

		//Level Loading
		hilife::entity_factory::instance().load_all(std::string("../data/lvl0"));

		return 0;
	}

	int application::destroy()
	{
		std::for_each(	_list.begin(),
								_list.end(),
								boost::bind(&application_base::destroy,_1)
							);
		return 0;
	}
	int application::loop()
	{
		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&application_base::loop,_1)
					 );
		return 0;
	}
}