#ifndef _HL_ENTITY_TABLE_H_
#define _HL_ENTITY_TABLE_H_

#include "pre.h"

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "entity_T.h"
#include "entity.h"
#include "entity_3d.h"
#include "entity_gui.h"

namespace hilife
{
	typedef class _HilifeExport entity_T<entity_3d,entity_gui> entity_table;
}

#endif /*_HL_ENTITY_TABLE_H_ */
