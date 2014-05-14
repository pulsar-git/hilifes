INCLUDES = $(CEGUI_CFLAGS) $(OGRE_CFLAGS) $(AM_CFLAGS)
lib_LTLIBRARIES=libHLFramework.la

libHLFramework_la_SOURCES =  entity_manager.cpp \
 entity_factory.cpp \
 attribute_manager.cpp \
 entity.cpp \
 entity_light_3d.cpp \
 helper_ogre.cpp \
 base_entity.cpp \
 entity_3d.cpp \
 stable_headers.cpp \
       tinyxml/tinystr.cpp \
       tinyxml/tinyxml.cpp \
       tinyxml/tinyxmlerror.cpp \
       tinyxml/tinyxmlparser.cpp


pkginclude_HEADERS = attribute_manager.h \
 base_entity.h \
 config-win32-mv7.h \
 entity.h \
 entity_3d.h \
 entity_T.h \
 entity_factory.h \
 entity_light.h \
 entity_light_3d.h \
 entity_manager.h \
 entity_table.h \
 helper_ogre.h \
 hl_config.h \
 logger.h \
 pointer.h \
 pre.h \
 stable_headers.h \
 standard_headers.h 

noinst_HEADERS = tinyxml/tinystr.h \
    tinyxml/tinyxml.h


libHLFramework_la_LDFLAGS = -version-info @HLFWK_VERSION_INFO@
libHLFramework_la_LIBADD =
