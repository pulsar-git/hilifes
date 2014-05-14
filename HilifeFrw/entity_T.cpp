#include "stable_headers.h"
#include "entity_T.h"
#include "attribute_manager.h"
#include "pointer.h"
#include <boost/bind.hpp>
#include "policy_manager.h"

namespace hilife
{
	template <class ENT_3D,class ENT_GUI>
	entity_T<ENT_3D,ENT_GUI>::entity_T(void)
	{
	}
	
	template <class ENT_3D,class ENT_GUI>
	entity_T<ENT_3D,ENT_GUI>::~entity_T(void)
	{
	}

	template <class ENT_3D,class ENT_GUI>
	int entity_T<ENT_3D,ENT_GUI>::initialize(void)
	{
		manager().addAttribute("Position",_position);
		parent(this);		

		LOGGER_DEBUG << "Initializing";
		
		POLICY_REQUIRED(hilife::HL_PL_3D)
			_list.push_back( boost::shared_ptr<base_entity> ( new ENT_3D(_attribute_manager)));

		POLICY_REQUIRED(hilife::HL_PL_GUI)
			_list.push_back( boost::shared_ptr<base_entity> ( new ENT_GUI(_attribute_manager)));

		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::parent,_1,this)
					 );
		std::for_each(	_list.begin(),
						_list.end(),
						boost::bind(&base_entity::initialize,_1)
					 );

		return 0;
	}
}
