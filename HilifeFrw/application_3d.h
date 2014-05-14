#ifndef _HL_APPLICATION_3D_H_
#define _HL_APPLICATION_3D_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include "application_base.h"

namespace hilife
{
	class _HilifeExport application_3d : public application_base
	{
	public:
		application_3d(void);
		~application_3d(void);
		virtual int setup();	
		virtual int destroy();
		virtual int loop();
	protected:
		Root *mRoot;
		Camera* mCamera;
		SceneManager* mSceneMgr;
		ExampleFrameListener* mFrameListener;
		RenderWindow* mWindow;

		int createScene();
		bool configure();
		void createCamera();
		void chooseSceneManager();
		void setupResources();
		void createViewports();
		void loadResources();
	};
}
#endif  /* _HL_APPLICATION_3D_H_ */ 