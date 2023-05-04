#ifndef SUPPORT_H_
#define SUPPORT_H_

#ifdef _WIN32
	#include "windows.h"
	typedef unsigned long timespec;	
#else
	#include "sys/time.h"
#endif

#include "bombmania.h"

#define ARRAYSIZE(arr) ((sizeof(arr))/(sizeof(arr[0])))

float    getTimeDiff(timespec &time);
void     getCurTime(timespec &time);
float    generateRandomFloat();
void     modifyTime(timespec &time, float mod);
void     getHomeDir(char * filePath);

#endif /*SUPPORT_H_*/
