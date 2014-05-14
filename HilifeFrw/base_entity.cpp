#include "stable_headers.h"

#include "base_entity.h"
#include "attribute_manager.h"

namespace hilife
{
	base_entity::base_entity(void):_initialized(false),_attribute_manager(0),_parent(0)
	{
	}

	base_entity::~base_entity(void)
	{
	}
}
