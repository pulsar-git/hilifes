#include "stable_headers.h"

#include "entity_light_3d.h"
#include "entity.h"
#include "attribute_manager.h"


namespace hilife
{
	entity_light_3d::entity_light_3d(AttributeManager *att):
		entity_3d(att)
	{
		
	}

	entity_light_3d::~entity_light_3d(void)
	{
	}

	int entity_light_3d::initialize(void)
	{
		manager().addAttribute("Type",_type);
		manager().addAttribute("Direction",_direction);
		return 0;
	}

	int entity_light_3d::create(void)
	{
		Ogre::Light* l =0;
		l=Ogre::Root::getSingleton()._getCurrentSceneManager()->createLight(parent()->name());
		// Accept default settings: point light, white diffuse, just set position
		// NB I could attach the light to a SceneNode if I wanted it to move automatically with
		//  other objects, but I don't
		l->setType((Ogre::Light::LightTypes)manager().getAttributeValue<int>(std::string("Type")));
		l->setDirection(manager().getAttributeValue<Ogre::Vector3>(std::string("Direction")));
		return 0;
	}
}
