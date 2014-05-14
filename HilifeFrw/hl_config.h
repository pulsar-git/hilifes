#ifndef _HL_CONFIG_H_
#define _HL_CONFIG_H_

#ifdef HAVE_CONFIG_H 
  #include <config.h>
#endif


#ifdef _MSC_VER 
#	include "config-win32-mv7.h"
#endif

#ifdef __GNUC__
#	include "config-linux.h"
#endif

// ms windows stuff
#ifdef WIN32
#  define NOMINMAX
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#endif

//TIXML STL...
#define TIXML_USE_STL



#endif /* _HL_CONFIG_H_ */
