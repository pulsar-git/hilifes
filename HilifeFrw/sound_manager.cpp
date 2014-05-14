#include "stable_headers.h"
#include "sound_manager.h"
#include <boost/pool/detail/singleton.hpp>

#include <al.h>
#include <alc.h>
#include <alut.h>
#include "OpenAL/aldlist.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


namespace hilife
{
	log4cpp::Category* sound_manager::logger ;

	sound_manager& sound_manager::instance()
	{
		return boost::details::pool::singleton_default<sound_manager>::instance();

	}
	sound_manager::sound_manager():
		g_bEAX(AL_FALSE)
	{
		LOGGER("sound_manager");
		LOGGER_INFO << "Starting up";
	}

	sound_manager::~sound_manager()
	{
		LOGGER_INFO << "Going Down";
	}

	sound_manager::init()
	{
		ALbyte	ch;
		ALint	error;
		ALCcontext *Context;
		ALCdevice *Device;
		ALDeviceList *pDeviceList;
		char deviceName[256];
		ALint majorVersion, minorVersion;
		ALboolean bOffsetExt = AL_FALSE;
		ALboolean bNewDistModels = AL_FALSE;
		ALboolean bCaptureExt = AL_FALSE;

		ALfloat listenerPos[]={0.0,0.0,0.0};
		ALfloat listenerVel[]={0.0,0.0,0.0};
		ALfloat	listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};	// Listener facing into the screen

		LOGGER_INFO << "OpenAL Test application\n\n";

		// Initialize Open AL manually

		// Open device
		pDeviceList = new(ALDeviceList);
		LOGGER_INFO << "\n\nAvailable OpenAL Devices:";
		LOGGER_INFO << "0. Default Device -- " << pDeviceList->GetDeviceName(pDeviceList->GetDefaultDevice());
		for (int i = 0; i < pDeviceList->GetNumDevices(); i++) {
			pDeviceList->GetDeviceVersion(i, &majorVersion, &minorVersion);
			LOGGER_INFO << i+1 << ". " << pDeviceList->GetDeviceName(i) << "Spec Version "<< majorVersion << "."<< minorVersion;
		}

		strcpy(deviceName, pDeviceList->GetDeviceName(pDeviceList->GetDefaultDevice()));
		LOGGER_INFO << "Select device: ";
		do {
			ch = _getch();
			i = atoi(&ch);
		} while ((i < 0) || (i > pDeviceList->GetNumDevices()));
		if ((i != 0) && (strlen(pDeviceList->GetDeviceName(i-1)) < 256)) {
			strcpy(deviceName, pDeviceList->GetDeviceName(i-1));
		}
		Device = alcOpenDevice(deviceName); // have a name from enumeration process above, so use it...
		delete(pDeviceList);
		pDeviceList = NULL;
		if (Device == NULL)
		{
			LOGGER_DEBUG << "Failed to Initialize Open AL";
			exit(-1);
		}

		//Create context(s)
		Context=alcCreateContext(Device,NULL);
		if (Context == NULL)
		{
			LOGGER_DEBUG << "Failed to initialize Open AL";
			exit(-1);
		}

		//Set active context
		alcGetError(Device);
		alcMakeContextCurrent(Context);
		if (alcGetError(Device) != ALC_NO_ERROR)
		{
			LOGGER_DEBUG << "Failed to Make Context Current";
			exit(-1);
		}

		// Clear Error Code
		alGetError();
		alcGetError(Device);

		// Check what device and version we are using
		const char *dName = alcGetString(Device, ALC_DEVICE_SPECIFIER);
		alcGetIntegerv(Device, ALC_MAJOR_VERSION, 1, &majorVersion);
		alcGetIntegerv(Device, ALC_MINOR_VERSION, 1, &minorVersion);
		LOGGER_DEBUG << "\nOpened "<< dName << ", spec version " << majorVersion << "." << minorVersion <<"\n";

		// Check for all the AL 1.1 Extensions (they may be present on AL 1.0 implementations too)
		bOffsetExt = alIsExtensionPresent("al_ext_offset");
		if (bOffsetExt)
			LOGGER_DEBUG << "AL_EXT_OFFSET support found !";

		bNewDistModels = AL_TRUE;
		bNewDistModels &= alIsExtensionPresent("AL_EXT_LINEAR_DISTANCE");
		bNewDistModels &= alIsExtensionPresent("AL_EXT_EXPONENT_DISTANCE");
		if (bNewDistModels)
			LOGGER_DEBUG << "AL_EXT_LINEAR_DISTANCE and AL_EXT_EXPONENT_DISTANCE support found ";
		
		bCaptureExt = alcIsExtensionPresent(Device, "alc_EXT_capTure");
		if (bCaptureExt)
			LOGGER_DEBUG << "ALC_EXT_CAPTURE support found !";

	#ifdef _USEEAX
		// Check for EAX 2.0 support
		g_bEAX = alIsExtensionPresent("EAX2.0");
		if (g_bEAX)
			LOGGER_DEBUG << "EAX 2.0 Extension available";

		eaxSet = (EAXSet)alGetProcAddress("EAXSet");
		if (eaxSet == NULL)
			g_bEAX = false;

		eaxGet = (EAXGet)alGetProcAddress("EAXGet");
		if (eaxGet == NULL)
			g_bEAX = false;
	#endif // _USEEAX

		// Set Listener attributes

		// Position ...
		alListenerfv(AL_POSITION,listenerPos);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alListenerfv POSITION : ", error);
			exit(-1);
		}

		// Velocity ...
		alListenerfv(AL_VELOCITY,listenerVel);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alListenerfv VELOCITY : ", error);
			exit(-1);
		}

		// Orientation ...
		alListenerfv(AL_ORIENTATION,listenerOri);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alListenerfv ORIENTATION : ", error);
			exit(-1);
		}

		// Generate Buffers
		alGenBuffers(NUM_BUFFERS, g_Buffers);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alGenBuffers :", error);
			exit(-1);
		}

		// Load in samples to be used by Test functions
		if ((!LoadWave("..\\Data\\footsteps.wav", g_Buffers[0])) ||
			/*(!LoadWave("..\\Data\\ding.wav", g_Buffers[1])) ||*/
			(!LoadWave("..\\Data\\stereo.wav", g_Buffers[1])) ||
			(!LoadWave("..\\Data\\wave1.wav", g_Buffers[2])) ||
			(!LoadWave("..\\Data\\wave2.wav", g_Buffers[3])) ||
			(!LoadWave("..\\Data\\wave3.wav", g_Buffers[4])) ||
			(!LoadWave("..\\Data\\wave4.wav", g_Buffers[5])) ||
			(!LoadWave("..\\Data\\stereo.wav", g_Buffers[6])))
		{
			alDeleteBuffers(NUM_BUFFERS, g_Buffers);
			exit(-1);
		}

		// Init Source
		LOGGER_DEBUG << "Init Sources";

		ALfloat source0Pos[]={ -2.0, 0.0, 2.0};	// Behind and to the left of the listener
		ALfloat source1Pos[]={ 2.0, 0.0, -2.0};	// Front and to the right of the listener

		alGetError();

		alGenSources(2,source);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alGenSources 2 : ", error);
			return 0;
		}

		alSourcefv(source[0],AL_POSITION,source0Pos);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcefv 0 AL_POSITION : ", error);
		
		alSourcei(source[0],AL_BUFFER, g_Buffers[1]);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcei 0 AL_BUFFER buffer 0 : ", error);

		alSourcei(source[0],AL_LOOPING,AL_TRUE);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcei 0 AL_LOOPING true: ", error);

		alSourcefv(source[1],AL_POSITION,source1Pos);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcefv 1 AL_POSITION : ", error);

		alSourcei(source[1],AL_BUFFER, g_Buffers[1]);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcei 1 AL_BUFFER buffer 1 : ", error);

		alSourcei(source[1],AL_LOOPING,AL_FALSE);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcei 1 AL_LOOPING false: ", error);

		return 0;
	}
	/*
	Displays the AL Error string for the AL error code
	*/
	ALvoid sound_manager::DisplayALError(ALbyte *szText, ALint errorcode)
	{
		printf("%s%s\n", szText, alGetString(errorcode));
	}

	/*
		Loads the wave file into the given Buffer ID
	*/
	ALboolean sound_manager::LoadWave(char *szWaveFile, ALuint BufferID)
	{
		ALint	error;
		ALsizei size,freq;
		ALenum	format;
		ALvoid	*data;
		ALboolean loop;

		if (!szWaveFile)
			return AL_FALSE;

		alutLoadWAVFile(szWaveFile,&format,&data,&size,&freq,&loop);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			printf("Failed to load %s\n", szWaveFile);
			DisplayALError("alutLoadWAVFile : ", error);
			return AL_FALSE;
		}

		// Copy data into ALBuffer
		alBufferData(BufferID,format,data,size,freq);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alBufferData : ", error);
			return AL_FALSE;
		}

		// Unload wave file
		alutUnloadWAV(format,data,size,freq);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alutUnloadWAV : ", error);
			return AL_FALSE;
		}

		return AL_TRUE;
	}

	int sound_manager::shutdown()
	{
		ALCcontext *Context;
		ALCdevice *Device;
		ALint	error;

		// Release resources
		LOGGER_DEBUG << "Release resources";
		alSourceStopv(2, source);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourceStopv 2 : ", error);

		alDeleteSources(2, source);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alDeleteSources 2 : ", error);


		//Release Buffers

		LOGGER_DEBUG << "Deleting Buffers";
		alDeleteBuffers(NUM_BUFFERS, g_Buffers);
		if ((error = alGetError()) != AL_NO_ERROR)
		{
			DisplayALError("alDeleteBuffers : ", error);
			exit(-1);
		}

		
		//Get active context
		LOGGER_DEBUG << "Getting context";
		Context=alcGetCurrentContext();
		
		//Get device for active context
		LOGGER_DEBUG << "Getting Device";
		Device=alcGetContextsDevice(Context);

		//Disable context
		LOGGER_DEBUG << "Disabling Context";
		alcMakeContextCurrent(NULL);

		//Release context(s)
		LOGGER_DEBUG << "Release Context";
		alcDestroyContext(Context);

		//Close device
		LOGGER_DEBUG << "Close Device";
		alcCloseDevice(Device);

		LOGGER_DEBUG << "End";
		return 0;
	}

	
	void sound_manager::test()
	{
		ALint error;
		alSourcePlay(source[1]);
		if ((error = alGetError()) != AL_NO_ERROR)
			DisplayALError("alSourcePlay source 0 : ", error);
	

	}
}