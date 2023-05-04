#include "support.h"
#include <time.h>
#include <signal.h>
#include "stdlib.h"

/*
void timerBoom_(int , siginfo_t *info, void *){
	//mvprintw(23,22,"%d",info->si_ptr);
	timerStruct* neco = (timerStruct*)info->si_ptr;
	timer_delete(neco);
	((timerFunction)((timerStruct*)info->si_ptr)->function)(((timerStruct*)info->si_ptr)->parameter);
	delete ((timerStruct*)info->si_ptr);
//	refresh();
	//printf("test:\ntest:\ntest:\n");
}

void test(sigval_t info){
	timer_delete((timerStruct*)info.sival_ptr);
	((timerFunction)((timerStruct*)info.sival_ptr)->function)(((timerStruct*)info.sival_ptr)->parameter);
//	refresh();
}

void setTimer(int seconds, void * function, void * parameter){
	timer_t boomTimer;
	struct itimerspec boomSpec;
	struct sigevent boomEvent;
	struct sigaction boomAction;
	
	struct timerStruct*  timerStructure= new timerStruct;
	
	
	boomAction.sa_sigaction=timerBoom_;
	sigemptyset(&boomAction.sa_mask);
        boomAction.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &boomAction, NULL);
	
	boomSpec.it_interval.tv_sec=0;
	boomSpec.it_interval.tv_nsec=0;
	boomSpec.it_value.tv_sec=seconds;
	boomSpec.it_value.tv_nsec=0;
	
	
	boomEvent._sigev_un._sigev_thread._attribute= (void *)timerStructure;
	boomEvent._sigev_un._sigev_thread._function=test;
	boomEvent.sigev_value.sival_ptr=(void *)timerStructure;
	boomEvent.sigev_signo=SIGUSR1;
	boomEvent.sigev_notify=SIGEV_SIGNAL;
	//boomEvent.sigev_notify=SIGEV_THREAD;
	
	timer_create(CLOCK_REALTIME, &boomEvent,&boomTimer);	
	timer_settime (boomTimer, 0, &boomSpec, NULL);
	
	timerStructure->function = function;
	timerStructure->parameter = parameter;
	timerStructure->timer=boomTimer;
}
*/

#include "stdio.h"
#include <string.h>
#include <limits.h>

#ifdef _WIN32
	float getTimeDiff(timespec &timeInput){
	  DWORD timeValue;
	  float ret;
	  getCurTime(timeValue);
	  ret = (((float)timeValue-timeInput))/1000;
	  return ret;
	}
#else
	float getTimeDiff(timespec &timeInput){
	  timespec timeValue;
	  clock_gettime(CLOCK_REALTIME, &timeValue);
	  float ret = ((float)(timeValue.tv_sec-timeInput.tv_sec))+(float)(((float)(timeValue.tv_nsec-timeInput.tv_nsec))/1000000000);
	  return ret;
	}
#endif
        

#ifdef _WIN32
        void getCurTime(timespec &time){
	  time = GetTickCount();
	}
#else
	void getCurTime(timespec &time){
	  clock_gettime(CLOCK_REALTIME, &time);
	}
#endif
        
        
#ifdef _WIN32
        void modifyTime(timespec &time, float mod){
          time += (mod*1000);
        }
#else
        void modifyTime(timespec &time, float mod){
          time.tv_nsec+=(long int)(mod-(int)mod);
          time.tv_sec+=(int)mod+(((mod-(int)mod)>0)?1:0);
          
        }
#endif

#ifdef _WIN32
void getHomeDir(char * filePath)
{
   #error Unimlemented getHomeDir function
}
#else
void getHomeDir(char * filePath)
{
   strncpy(filePath, getenv("HOME"), PATH_MAX);
}
#endif
 
float generateRandomFloat(){
  return rand()/100;
}
