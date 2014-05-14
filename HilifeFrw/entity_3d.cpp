#include "stable_headers.h"

#include "entity_3d.h"
#include "helper_ogre.h"
#include "attribute_manager.h"
#include "entity.h"
#include "event.h"


namespace hilife
{

	entity_3d::entity_3d(AttributeManager* att):_ent_3d(0),_node_3d(0)
	{
		_attribute_manager=att;
	}

	entity_3d::~entity_3d(void)
	{
	}
	
	int entity_3d::update_attribute_listener(const std::string &name,const std::string &value)
	{
		return hilife::helper_ogre::instance().update_attribute_listener(name,value);
	}

	int entity_3d::create(void)
	{
		//When it ll become too long...move it to a factory!
		
		Ogre::Vector3 attribute;
		manager().getAttributeValue(std::string("Position"),attribute);
		_ent_3d = Ogre::Root::getSingleton()._getCurrentSceneManager()->createEntity( parent()->name(), _mesh.c_str() );

		// Add entity to the scene node
		_node_3d=Ogre::Root::getSingleton()._getCurrentSceneManager()->getRootSceneNode()->createChildSceneNode(parent()->name(),manager().getAttributeValue<Ogre::Vector3>(std::string("Position")) );
		_node_3d->attachObject(_ent_3d);

		//Set the scale if set...
		Ogre::Vector3 scale;
		if(manager().getAttributeValue(std::string("Scale"),scale))
		{
			_node_3d->setScale(scale);
		}
		

		return 0;	
	}

	int entity_3d::initialize(void)
	{
		manager().addAttribute("Mesh",_mesh);
		manager().addAttribute("Size",_size);
		manager().addAttribute("Scale",_scale);
		return 0;		
	}

	int entity_3d::event_listener(event *evt)
	{
		//On peut faire ca par rapport au parent juste je pense!
		if(evt->entity()==this->parent())
				if(_node_3d)
				{
					if(evt->type() == event::HL_SELECTED)
								_node_3d->showBoundingBox(true);
					if(evt->type() == event::HL_UNSELECTED)
								_node_3d->showBoundingBox(false);
				}
		return 1;
	}

}
