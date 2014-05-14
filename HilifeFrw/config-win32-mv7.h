#ifndef _HL_CONFIG_W32_MV7_H_
#define _HL_CONFIG_W32_MV7_H_

//Templates require sources!
#define HL_TEMPLATES_REQUIRE_SOURCE

//Pragma Once allowed...
#define HL_HAS_PRAGMA_ONCE

//HashMap
#define hashmap stdext::hash_map

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( __MINGW32__ )
		// Linux compilers don't have symbol import/export directives.
#   	define _HilifeExport
#   	define _HilifePrivate
#   else
#   	if defined( HL_NONCLIENT_BUILD )
#       	define _HilifeExport __declspec( dllexport )
#   	else
#       	define _HilifeExport __declspec( dllimport )
#   	endif
#   	define _HilifePrivate
#	endif

// Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define HILIFE_DEBUG_MODE 1
#   else
#       define HILIFE_DEBUG_MODE 0
#   endif

#if defined( __MINGW32__ )
    #define EXT_HASH
#else
    #define snprintf _snprintf
    #define vsnprintf _vsnprintf
#endif

#if HILIFE_DEBUG_MODE
    #define HILIFE_PLATFORM_LIB "OgrePlatform_d.dll"
#else
    #define HILIFE_PLATFORM_LIB "OgrePlatform.dll"
#endif

#endif //_HL_CONFIG_W32_MV7_H_
