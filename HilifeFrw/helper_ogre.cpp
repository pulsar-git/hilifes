#include "stable_headers.h"

#include "helper_ogre.h"
#include "entity.h"
#include "attribute_manager.h"

namespace hilife
{
	log4cpp::Category* helper_ogre::logger ;

	helper_ogre::helper_ogre(void)
	{
		LOGGER("helper_ogre");
	}
	helper_ogre::~helper_ogre(void)
	{
	}

	int helper_ogre::update_attribute_listener(const std::string &name,const std::string &value)
	{
		if(!name.compare("SoundFile"))
			std::cout << "SoundFile Changing..." << std::endl;
		return 0;
	}

	helper_ogre& helper_ogre::instance()
	{
		return boost::details::pool::singleton_default<helper_ogre>::instance();
	}
}
