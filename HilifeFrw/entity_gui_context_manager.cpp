#include "stable_headers.h"
#include <boost/pool/detail/singleton.hpp>
#include "entity_gui_context_manager.h"

namespace hilife
{
	entity_gui_context_manager& entity_gui_context_manager::instance()
	{
		return boost::details::pool::singleton_default<entity_gui_context_manager>::instance();
	}

	entity_gui_context_manager::entity_gui_context_manager(void)
	{
	}

	entity_gui_context_manager::~entity_gui_context_manager(void)
	{
	}

	int entity_gui_context_manager::show_context()
	{
		//Get GUI Sheet
		CEGUI::Window *sheet=CEGUI::System::getSingleton().getGUISheet();
		
		Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->setDebugText("Starting up");

		//Try to locate the window named "contextmenu"
		CEGUI::Window *menu=0;
		
		// If the window is already present, then delete it from both the Sheet & the window manager
		assert( sheet !=0 );
		if(!sheet)
		{
			std::cout << "Sheet is null" << std::endl;
			return 0;
		}


		if(sheet->isChild("contextmenu"))
		{
			sheet->removeChildWindow("contextmenu");
			CEGUI::WindowManager::getSingleton().destroyWindow("contextmenu");
		}


		//Create a new window
		//menu=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","contextmenu");
		menu=CEGUI::WindowManager::getSingleton().loadWindowLayout("context.layout");
		contextWindow_=menu;
		//Set metrics mode to inherited (like parent)
		menu->setMetricsMode(CEGUI::Inherited);
		//Set relative size (0.2 is parent * 0.2)
		menu->setSize(CEGUI::Size(0.2,0.6));

		//Ideally here the object, would give us a reference to a LUA script that we would parse
		//To create the menu...ideally :)

		//Initialise the number...
		CEGUI::WindowManager &wmgr=CEGUI::WindowManager::getSingleton();

		CEGUI::Window *mBtn=0;
		mBtn=wmgr.getWindow("button");
		mBtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&entity_gui_context_manager::action_default,this));
		// Apparently, by registering an event to the GuiLayout, we can know if we clicked anywhere on a present GUI (GuiLayout event not fired)
		// Or elsewhere, GuiLayout event fired...But that doesn't seems to work actually

		mBtn=wmgr.getWindow("button3");
		mBtn->hide();

		//Load context menu based on entity stuffs	

		sheet->addChildWindow(menu);
		
		menu->moveToFront();
		//move contextWindow to right of cursor
		CEGUI::Point tp = CEGUI::MouseCursor::getSingleton().getPosition();
		tp.d_x/=Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		tp.d_y/=Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		menu->setXPosition(tp.d_x);
		menu->setYPosition(tp.d_y);

		return 0;
	}

	int entity_gui_context_manager::hide_context()
	{
		if(contextWindow_)
			contextWindow_->hide();
		//contextWindow_->removeAllEvents();

		return 0;
	}

	bool entity_gui_context_manager::action_default(const CEGUI::EventArgs&)
	{
		Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->setDebugText("Default Action...");
		std::cout << "default action" << std::endl;

		return true;
	}
	bool entity_gui_context_manager::action_default2(const CEGUI::EventArgs&)
	{
		Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->setDebugText("Default Action... 2");
		std::cout << "default action 2" << std::endl;

		return true;
	}
}