#ifndef _HL_SOUND_MANAGER_H_
#define _HL_SOUND_MANAGER_H_

#include "pre.h" 

#ifdef HL_HAS_PRAGMA_ONCE
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

#include <al.h>
#include <alc.h>
#include <alut.h>

namespace hilife
{
	class _HilifeExport sound_manager
	{
	public:
		sound_manager();
		~sound_manager();
		static sound_manager& sound_manager::instance();
		int init();
		int shutdown();
		
		void test();
	protected:
		ALboolean LoadWave(char *szWaveFile, ALuint BufferID);
		ALvoid DisplayALError(ALbyte *szText, ALint errorcode);
	private:
		ALuint	source[2];
		static log4cpp::Category* logger ;
		
		#define NUM_BUFFERS 7	// Number of buffers to be Generated
		ALboolean	g_bEAX;			// Boolean variable to indicate presence of EAX 2.0 Extension
		ALuint		g_Buffers[NUM_BUFFERS];		// Array of Buffer IDs
	};
}

#endif  /* _HL_SOUND_MANAGER_H_ */ 
