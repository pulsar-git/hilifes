/*
 * Copyright (c) 2005, Creative Labs Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * 	     the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 * 	     and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of Creative Labs Inc. nor the names of its contributors may be used to endorse or
 * 	     promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "aldlist.h"
#include <windows.h>
#include "alc.h"


/* 
 * Init call
 */
ALDeviceList::ALDeviceList()
{
	char *devices;
	int major, minor, index;
	const char *defaultDeviceName;
	const char *actualDeviceName;

	// have a set of vectors storing the device list, selection status, spec version #, and XRAM support status
	// -- empty all the lists and reserve space for 10 devices
	dList.empty();
	dList.reserve(10);
	selected.empty();
	selected.reserve(10);
	majorVer.empty();
	majorVer.reserve(10);
	minorVer.empty();
	minorVer.reserve(10);
	xram.empty();
	xram.reserve(10);
	defaultDeviceIndex = 0;

	// grab function pointers for 1.0-API functions, and if successful proceed to enumerate all devices
	if (LoadOAL10Library(NULL, &ALFunction) == TRUE) {
		if (ALFunction.alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")) {
			devices = (char *)ALFunction.alcGetString(NULL, ALC_DEVICE_SPECIFIER);
			defaultDeviceName = (char *)ALFunction.alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
			index = 0;
			// go through device list (each device terminated with a single NULL, list terminated with double NULL)
			while (*devices != NULL) {
				if (strcmp(defaultDeviceName, devices) == 0) {
					defaultDeviceIndex = index;
				}
				ALCdevice *device = ALFunction.alcOpenDevice(devices);
				if (device) {
					ALCcontext *context = ALFunction.alcCreateContext(device, NULL);
					if (context) {
						ALFunction.alcMakeContextCurrent(context);
						// if new actual device name isn't already in the list, then add it...
						actualDeviceName = ALFunction.alcGetString(device, ALC_DEVICE_SPECIFIER);
						bool bNewName = true;
						for (int i = 0; i < GetNumDevices(); i++) {
							if (strcmp(GetDeviceName(i), actualDeviceName) == 0) {
								bNewName = false;
							}
						}
						if ((bNewName) && (actualDeviceName != NULL) && (strlen(actualDeviceName) > 0)) {
							ALFunction.alcGetIntegerv(device, ALC_MAJOR_VERSION, sizeof(int), &major);
							ALFunction.alcGetIntegerv(device, ALC_MINOR_VERSION, sizeof(int), &minor);
							dList.push_back(actualDeviceName);
							majorVer.push_back(major);
							minorVer.push_back(minor);
							if (ALFunction.alIsExtensionPresent("EAX-RAM") == TRUE) {
								xram[index] = true;
							} else {
								xram[index] = false;
							}
						}
						ALFunction.alcDestroyContext(context);
					}
					ALFunction.alcCloseDevice(device);
				}
				devices += strlen(devices) + 1;
				index += 1;
			}
		}
	}

	ResetFilters();
}

/* 
 * Exit call
 */
ALDeviceList::~ALDeviceList()
{
	UnloadOAL10Library();
}

/*
 * Returns the number of devices in the complete device list
 */
int ALDeviceList::GetNumDevices()
{
	return dList.size();	
}

/* 
 * Returns the device name at an index in the complete device list
 */
char * ALDeviceList::GetDeviceName(int index)
{
	return (char *)dList[index].c_str();
}

/*
 * Returns the major and minor version numbers for a device at a specified index in the complete list
 */
void ALDeviceList::GetDeviceVersion(int index, int *major, int *minor)
{
	*major = majorVer[index];
	*minor = minorVer[index];
	return;
}

/*
 * returns the index of the default device in the complete device list
 */
int ALDeviceList::GetDefaultDevice()
{
	return defaultDeviceIndex;
}

/* 
 * Deselects devices which don't have the specified minimum version
 */
void ALDeviceList::FilterDevicesMinVer(int major, int minor)
{
	int dMajor, dMinor;
	for (unsigned int i = 0; i < dList.size(); i++) {
		GetDeviceVersion(i, &dMajor, &dMinor);
		if ((dMajor < major) || ((dMajor == major) && (dMinor < minor))) {
			selected[i] = false;
		}
	}
}

/* 
 * Deselects devices which don't have the specified maximum version
 */
void ALDeviceList::FilterDevicesMaxVer(int major, int minor)
{
	int dMajor, dMinor;
	for (unsigned int i = 0; i < dList.size(); i++) {
		GetDeviceVersion(i, &dMajor, &dMinor);
		if ((dMajor > major) || ((dMajor == major) && (dMinor > minor))) {
			selected[i] = false;
		}
	}
}

/* 
 * Deselects devices which don't have XRAM support
 */
void ALDeviceList::FilterDevicesXRAMOnly()
{
	for (unsigned int i = 0; i < dList.size(); i++) {		
		if (xram[i] == false) {
			selected[i] = false;
		}
	}
}

/*
 * Resets all filtering, such that all devices are in the list
 */
void ALDeviceList::ResetFilters()
{
	for (int i = 0; i < GetNumDevices(); i++) {
		selected[i] = true;
	}
	filterIndex = 0;
}

/*
 * Gets index of first filtered device
 */
int ALDeviceList::GetFirstFilteredDevice()
{
	for (int i = 0; i < GetNumDevices(); i++) {
		if (selected[i] == true) {
			break;
		}
	}
	filterIndex = i + 1;
	return i;
}

/*
 * Gets index of next filtered device
 */
int ALDeviceList::GetNextFilteredDevice()
{
	for (int i = filterIndex; i < GetNumDevices(); i++) {
		if (selected[i] == true) {
			break;
		}
	}
	filterIndex = i + 1;
	return i;
}