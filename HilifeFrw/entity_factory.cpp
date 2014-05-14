#include "stable_headers.h"
#include <boost/pool/detail/singleton.hpp>
#include "entity_factory.h"

//File stuffs...
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/exception.hpp>

#include "attribute_manager.h"
#include "entity_manager.h"

#include "entity_table.h"
#include "entity_light.h"

using namespace hilife;

namespace hilife
{
	log4cpp::Category* entity_factory::logger ;

	entity_factory::entity_factory(void)
	{
		LOGGER("entity_factory");
	}

	entity_factory::~entity_factory(void)
	{
		LOGGER_INFO << "Shuting down";
	}

	entity *entity_factory::load(const std::string &filename)
	{
		TiXmlDocument doc;
		bool loadOkay = doc.LoadFile(filename.c_str());
		entity *ent = 0;
		if (loadOkay)
		{
			LOGGER_INFO << "Loading " << filename;
			TiXmlHandle hDoc(&doc);
			TiXmlElement* pElem;
			TiXmlHandle hRoot(0);

			pElem=hDoc.FirstChildElement().Element();
			hRoot=TiXmlHandle(pElem);
			LOGGER_INFO << "Entity [" <<pElem->Attribute("name")<< "] found class [" << pElem->Attribute("class") << "]";
			ent = create_entity(pElem->Attribute("class"));
			ent->name(pElem->Attribute("name"));

			// Initialise entity
			ent->initialize();

			pElem=hRoot.FirstChild( "attribute" ).Element();
			std::string type;
			for( pElem; pElem; pElem=pElem->NextSiblingElement())
			{
				
				LOGGER_DEBUG << "Attribute [" << pElem->Attribute("name") << "]";
				ent->manager().setAttributeValueByString(pElem->Attribute("name"),pElem->Attribute("value"));
			}
		}
		else
		{
			LOGGER_WARN << "Failed to Load " << filename;
			return ent;
		}
		
		LOGGER_INFO << "Adding entity ["<<ent->name()<<"] to entity_manager";
		entity_manager::instance().add(ent);

		//Spawn it...
		ent->create();

		return ent;
	}

	entity *entity_factory::create_entity(const std::string &className)
	{
		/**
		*   Replace thoose Ugly stuff, by smthg like factory.register("Table",entity_table);
		*
		*
		*/
		if(!className.compare("Base"))
		{
			LOGGER_DEBUG << "create_entity -> Table";
			return new entity_table();
		}

		if(!className.compare("Light"))
		{
			LOGGER_DEBUG << "create_entity -> Light";
			return new entity_light();
		}

		LOGGER_WARN << "Didn't Found a registered class type for [" << className << "]";
		return new entity();
	}

	entity_factory& entity_factory::instance()
	{
		return boost::details::pool::singleton_default<entity_factory>::instance();
	}

	void entity_factory::load_all(const std::string &pathname)
	{
		using namespace boost::filesystem;
		try
		{
			directory_iterator end_itr;

			for(directory_iterator itr (pathname );itr!=end_itr;++itr)
			{
				if(is_directory(*itr))
				{
					LOGGER_DEBUG << "Directory found [" << itr->leaf() << "]";
				}
				else
				{
					LOGGER_DEBUG << "File found [" << itr->leaf() << "]";
					if(itr->string().find(".xml")!=std::string::npos)
						load(itr->string());
				}
			}
		}
		catch(filesystem_error &ex)
		{
			LOGGER_DEBUG << ex.what();
		}
	}
}
