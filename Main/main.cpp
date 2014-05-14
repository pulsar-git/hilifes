#include "stable_headers.h"
#include "pre.h"
#include <log4cpp/propertyconfigurator.hh>

#include "sound_manager.h"
#include "network_manager.h"
#include "policy_manager.h"
#include "application.h"

int main(int argc,char **argv)
{
		
		hilife::policy_manager::instance().value(hilife::HL_PL_NETWORK,true);
		//hilife::policy_manager::instance().value(hilife::HL_PL_SOUND,true);
		//hilife::policy_manager::instance().value(hilife::HL_PL_3D,true);
		hilife::policy_manager::instance().value(hilife::HL_PL_GUI,true);

		//log4cpp initialisation
		try
		{
			log4cpp::PropertyConfigurator::configure("../Data/log4cpp.properties");
			
		} 
		catch(log4cpp::ConfigureFailure& f) 
		{
			std::cout << "Configure Problem " << f.what() << std::endl;
			return -1;
		}

		POLICY_REQUIRED(hilife::HL_PL_SOUND)
			hilife::sound_manager::instance().init();


		POLICY_REQUIRED(hilife::HL_PL_NETWORK)
			hilife::network_manager::instance().start();


		hilife::application app;
		app.setup();
		try 
		{
			app.loop();
		}
		catch( Ogre::Exception& e ) 
		{
			std::cout << e.getFullDescription() << std::endl;
		}
		POLICY_REQUIRED(hilife::HL_PL_SOUND)
			hilife::sound_manager::instance().shutdown();
		

		POLICY_REQUIRED(hilife::HL_PL_NETWORK)
			hilife::network_manager::instance().shutdown();
}
