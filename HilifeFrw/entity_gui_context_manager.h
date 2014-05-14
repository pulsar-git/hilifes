#ifndef _HL_ENTITY_GUI_CONTEXT_MANAGER_H_
#define _HL_ENTITY_GUI_CONTEXT_MANAGER_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

namespace hilife
{
	class _HilifeExport entity_gui_context_manager
	{
	public:
		entity_gui_context_manager(void);
		~entity_gui_context_manager(void);
		static entity_gui_context_manager& instance();
		int show_context();
		int hide_context();
		bool action_default(const CEGUI::EventArgs&);
		bool action_default2(const CEGUI::EventArgs&);
	private:
		CEGUI::Window * contextWindow_;
	};
}

#endif  /* _HL_ENTITY_GUI_CONTEXT_MANAGER_H_ */ 
