#ifndef _HL_HELPER_OGRE_
#define _HL_HELPER_OGRE_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include <boost/pool/detail/singleton.hpp>

namespace hilife
{
	class entity;

	class _HilifeExport helper_ogre
	{
	public:
		helper_ogre(void);
		~helper_ogre(void);
		
		static helper_ogre& instance();

		int update_attribute_listener(const std::string &name,const std::string &value);
	private:
		static log4cpp::Category* logger ;
	};
}

#endif //_HL_HELPER_OGRE_
