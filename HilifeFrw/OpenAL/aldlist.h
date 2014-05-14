#ifndef ALDEVICELIST_H
#define ALDEVICELIST_H

#pragma warning(disable: 4786)  //disable warning "identifier was truncated to '255' characters in the browser information"
#include <vector>
#include <string>
#include "LoadOAL.h"

using namespace std;

class ALDeviceList
{
private:
	OPENALFNTABLE	ALFunction;
	vector<string> dList;
	int defaultDeviceIndex;
	vector<int> minorVer;
	vector<int> majorVer;
	vector<bool> selected;
	vector<bool> xram;
	int filterIndex;

public:
	ALDeviceList ();
	~ALDeviceList ();
	int GetNumDevices();
	char *GetDeviceName(int index);
	void GetDeviceVersion(int index, int *major, int *minor);
	int GetDefaultDevice();
	void FilterDevicesMinVer(int major, int minor);
	void FilterDevicesMaxVer(int major, int minor);
	void FilterDevicesXRAMOnly();
	void ResetFilters();
	int GetFirstFilteredDevice();
	int GetNextFilteredDevice();
};

#endif // ALDEVICELIST_H
