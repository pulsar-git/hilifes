#ifndef _HL_CONFIG_LINUX_H_
#define _HL_CONFIG_LINUX_H_

//Templates require sources!
#define HL_TEMPLATES_REQUIRE_SOURCE

#define hashmap ::__gnu_cxx::hash_map

#define _HilifeExport
#define _HilifePrivate

#ifndef EXT_HASH
		#define EXT_HASH
#endif

#if HILIFE_DEBUG_MODE
    #define HILIFE_PLATFORM_LIB "OgrePlatform_d.dll"
#else
    #define HILIFE_PLATFORM_LIB "OgrePlatform.dll"
#endif

#endif /* _HL_CONFIG_LINUX_H */

