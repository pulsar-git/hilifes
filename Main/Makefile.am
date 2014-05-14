INCLUDES = $(CEGUI_CFLAGS) $(OGRE_CFLAGS) $(AM_CFLAGS) -I$(top_srcdir)/HilifeDll

noinst_PROGRAMS = SkeletalAnimation

SkeletalAnimation_SOURCES = main.cpp
SkeletalAnimation_LDFLAGS = -L$(top_builddir)/HilifeDll
SkeletalAnimation_LDADD = -lHLFramework -llog4cpp -lOgreMain

install-exec-local:
	$(INSTALL_PROGRAM) ./SkeletalAnimation $(top_builddir)/bin/SkeletalAnimation
