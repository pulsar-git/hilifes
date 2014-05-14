#ifndef _HL_STANDARD_HEADERS_H
#define _HL_STANDARD_HEADERS_H

#ifdef HL_HAS_PRAGMA_ONCE 
#pragma once
#endif /* HL_HAS_PRAGMA_ONCE*/

// STL headers
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef EXT_HASH
#   include <ext/hash_map>
#   include <ext/hash_set>
#else
#   include <hash_set>
#   include <hash_map>
#endif

#include "logger.h"

# pragma warning (disable:4244 4311 4312 4267)
#include "ace/ace.h"
#include "ace/Message_Queue.h"
#include "ace/Thread_Manager.h"
# pragma warning (default:4244 4311 4312 4267)

#include <CEGUI/CEGUI.h>
#include "ExampleApplication.h"

//TinyXML
#include "tinyxml/tinyxml.h"

//Ogre Stuffs
#include <Ogre.h>

#endif //_HL_STANDARD_HEADERS_H

