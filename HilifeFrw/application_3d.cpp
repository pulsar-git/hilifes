#include "stable_headers.h"
#include "application_3d.h"
#include "policy_manager.h"
#include "event_manager.h"
#include "sound_manager.h"


#include "CEGUI/CEGUI.h"
#include "OgreMemoryMacros.h"
#include "OgreCEGUIRenderer.h"
#include "OgreCEGUIResourceProvider.h"
#include "OgreNoMemoryMacros.h"
#include "entity_gui_context_manager.h"

namespace hilife
{
int network_i;

class HilifeListener : public ExampleFrameListener, public MouseMotionListener, public MouseListener
{
protected:
	SceneNode *mCurrentObj;
public:
	bool right_toggle_;
	bool _shutdown;

    HilifeListener(RenderWindow* win, Camera* cam)
        : ExampleFrameListener(win, cam,true),right_toggle_(false),
		_shutdown(false),mCurrentObj(0)
    {
		mEventProcessor->addMouseMotionListener(this);
		mEventProcessor->addMouseListener(this);
		mEventProcessor->addKeyListener(this);
        
    }

    bool frameStarted(const FrameEvent& evt)
    {
        static Real timeLapse = 0.0f;
        static Real factor = 0.0;
        static bool wireframe = 0;


        timeLapse += evt.timeSinceLastFrame;

        // Prgressively grow the patch
        if (timeLapse > 1.0f)
        {

            mWindow->setDebugText("Multiline Doesnt Work here..." + StringConverter::toString(factor));
            timeLapse = 0.0f;
        }

		//Network Stuff
		POLICY_REQUIRED(hilife::HL_PL_NETWORK)
		{
			event *evtt = 0;
			evtt = hilife::event_manager::instance().pull_event();
			if(evtt)
			{

				// Add entity to the scene node
				Ogre::Root::getSingleton()._getCurrentSceneManager()->getRootSceneNode()->createChildSceneNode("network"+Ogre::StringConverter::toString(network_i) ,Ogre::Vector3(100+network_i*10,100+network_i*10,100+network_i*10) )->attachObject(
						Ogre::Root::getSingleton()._getCurrentSceneManager()->createEntity( "network"+Ogre::StringConverter::toString(network_i), "robot.mesh" )
					);
				network_i++;
				delete evtt;
			}
		}

        // Call default
        //return ExampleFrameListener::frameStarted(evt);
		if(!_shutdown)
			return true;
		else
			return false;
    }
	void mouseMoved (MouseEvent *e)
	{
		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::Renderer* mGUIRenderer	= CEGUI::System::getSingleton().getRenderer();
			CEGUI::System::getSingleton().injectMouseMove(
				e->getRelX() * mGUIRenderer->getWidth(), 
				e->getRelY() * mGUIRenderer->getHeight());
			e->consume();
		}
	}

	void mouseDragged (MouseEvent *e) 
	{ 
		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::Renderer* mGUIRenderer	= CEGUI::System::getSingleton().getRenderer();
			if(right_toggle_)
			{
				mRotX = Degree(-e->getRelX() * mGUIRenderer->getWidth()* static_cast <Ogre::Real> (0.2) );
				mRotY = Degree(-e->getRelY() * mGUIRenderer->getHeight()* static_cast <Ogre::Real> (0.2) );
				moveCamera();		
			}
			//Default case, only move cursor
			else
			{
				CEGUI::System::getSingleton().injectMouseMove(
					e->getRelX() * mGUIRenderer->getWidth(), 
					e->getRelY() * mGUIRenderer->getHeight());
			}
			e->consume();
		}
	}
	void mousePressed (MouseEvent *e)
	{
		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(
				convertOgreButtonToCegui(e->getButtonID()));
		    
			if(convertOgreButtonToCegui(e->getButtonID())==CEGUI::RightButton)
			{
				right_toggle_=true;
				CEGUI::MouseCursor::getSingletonPtr()->hide();
			}
			e->consume();
		}
	}

	CEGUI::MouseButton convertOgreButtonToCegui(int buttonID)
	{
		switch (buttonID)
		{
		case MouseEvent::BUTTON0_MASK:
			return CEGUI::LeftButton;
		case MouseEvent::BUTTON1_MASK:
			return CEGUI::RightButton;
		case MouseEvent::BUTTON2_MASK:
			return CEGUI::MiddleButton;
		case MouseEvent::BUTTON3_MASK:
			return CEGUI::X1Button;
		default:
			return CEGUI::LeftButton;
		}
	}
	void mouseReleased (MouseEvent *e)
	{
		POLICY_REQUIRED(hilife::HL_PL_SOUND)
			hilife::sound_manager::instance().test();

		right_toggle_=false;

		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(
							convertOgreButtonToCegui(e->getButtonID())
						);

			
			CEGUI::MouseCursor::getSingletonPtr()->show();

			if(mCurrentObj)
			{
				
				using namespace hilife;
				event_manager::instance().fire_event(event::HL_UNSELECTED,std::string (mCurrentObj->getName().c_str()));
				mCurrentObj=0;
			}

			//Object checks...
			CEGUI::Point tp= CEGUI::MouseCursor::getSingleton().getPosition();
			tp.d_x/=Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
			tp.d_y/=Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

			Ray mouseRay = mCamera->getCameraToViewportRay(tp.d_x,tp.d_y);
			RaySceneQuery *mRaySceneQuery = Root::getSingleton()._getCurrentSceneManager()->createRayQuery(Ray());
			mRaySceneQuery->setRay(mouseRay);
			mRaySceneQuery->setSortByDistance(true);

			//Execute query
			RaySceneQueryResult &result = mRaySceneQuery->execute();
			RaySceneQueryResult::iterator itr;


			//Get results
			for(itr=result.begin();itr!=result.end();++itr)
			{
				
				if( itr!=result.end() && itr->movable && itr->movable->getName().compare("TestLevel"))
				{
					mCurrentObj = itr->movable->getParentSceneNode();
					{
						using namespace hilife;
						event_manager::instance().fire_event(event::HL_SELECTED,std::string (mCurrentObj->getName().c_str()));
						
					}
					//RP_CEGUI_CONTEXT_MANAGER::instance()->show_context(mCurrentObj);
					break;
				}
				else
				{
					//Unbind the contextHandler??
					//RP_CEGUI_CONTEXT_MANAGER::instance()->hide_context();
					//Hide the context Window
				}
			}
		}
	}

	void mouseClicked(MouseEvent* ){}
	void mouseEntered(MouseEvent* ){}
	void mouseExited(MouseEvent* ) {}

	void keyPressed(KeyEvent* e)
	{
		if(e->getKey() == KC_ESCAPE)
		{
			_shutdown=true;
			std::cout << "Exit Required!" << std::endl;
			e->consume();
			return;
		}
		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::System::getSingleton().injectKeyDown(e->getKey());
			CEGUI::System::getSingleton().injectChar(e->getKeyChar());
			e->consume();
		}
	}

	void keyReleased(KeyEvent* e)
	{
		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			CEGUI::System::getSingleton().injectKeyUp(e->getKey());
			e->consume();
		}
	}

	void keyClicked(KeyEvent* e) 
	{
		// Do nothing
		e->consume();
	}
};

	application_3d::application_3d(void)
	{
	}

	application_3d::~application_3d(void)
	{
	}

	int application_3d::setup()
	{
		mRoot = new Root();
		LogManager::getSingleton().setLogDetail(Ogre::LL_BOREME);
		

        setupResources();

        bool carryOn = configure();
        if (!carryOn) return false;

        chooseSceneManager();
        createCamera();
        createViewports();

        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Load resources
		loadResources();

		// Create the scene
        createScene();

		// Create Frame Listener
        mFrameListener= new HilifeListener(mWindow, mCamera);
        mRoot->addFrameListener(mFrameListener);
		

        return true;
	
		return 0;
	}
	int application_3d::createScene()
	{
		// Set ambient light
        mSceneMgr->setAmbientLight(ColourValue(0.2, 0.2, 0.2));

        mCamera->setPosition(300,60, 400);
        mCamera->lookAt(0,200,-300);
		
		Ogre::Root::getSingleton()._setCurrentSceneManager(mSceneMgr);
		

		POLICY_REQUIRED(hilife::HL_PL_GUI)
		{
			//CEGUI Stuffs
			CEGUI::Renderer* mGUIRenderer	=	new CEGUI::OgreCEGUIRenderer(mWindow,Ogre::RENDER_QUEUE_OVERLAY, false, 3000);
			CEGUI::System* mySystem			=	new CEGUI::System(mGUIRenderer);
			CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Errors);

			CEGUI::SchemeManager::getSingleton().loadScheme( (CEGUI::utf8*)"TaharezLook.scheme" );
			//Set the mouseCursor
			CEGUI::MouseCursor::getSingleton().setImage((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
			mySystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

			//Load Hilife.layout
			CEGUI::Window* sheet = 
				CEGUI::WindowManager::getSingleton().loadWindowLayout(
					(CEGUI::utf8*)"Hilife.layout"); 
			mySystem->setGUISheet(sheet);
			
			//Suscribe Events (move to dedicated function later!
			sheet->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::Event::Subscriber(&hilife::entity_gui_context_manager::action_default2,&hilife::entity_gui_context_manager::instance()));

			CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

			//Hide context window, otherwise it will NEVER show :/
			wmgr.getWindow((CEGUI::utf8*)"contextWindow")->hide();
		}

		return 0;
	}
	int application_3d::destroy()
	{

		return 0;
	}
	int application_3d::loop()
	{
		// Infinite loop here !
		Ogre::Root::getSingleton().startRendering();
		return 0;
	}

	bool application_3d::configure()
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true);
            return true;
        }
        else
        {
            return false;
        }
    }

	void application_3d::chooseSceneManager()
    {
        // Get the SceneManager, in this case a generic one
        mSceneMgr = mRoot->getSceneManager(ST_GENERIC);
    }
	void application_3d::createCamera()
    {
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        mCamera->setPosition(Vector3(0,0,500));
        // Look back along -Z
        mCamera->lookAt(Vector3(0,0,-300));
        mCamera->setNearClipDistance(5);

    }

	void application_3d::createViewports(void)
    {
        // Create one viewport, entire window
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    }

    /// Method which will define the source of resources (other than current folder)
	void application_3d::setupResources(void)
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load("resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
            }
        }
    }

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	void application_3d::loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	}
}