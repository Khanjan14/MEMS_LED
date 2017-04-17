#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os2.h"
#include "stm32f4xx.h"
#include "Board_LED.h"

#define Parent_LED 0
#define Common_LED 1
#define Child_LED 2

int count=0;
osSemaphoreId_t ID1,ID2,S_ID;
osStatus_t shm;
int f1=0,f2=0;


void myDelay(int i){
	while(i--);
}



void get2(void *argument)
{
	f2=1;
	
	int i=5;
	while (i--){
	LED_On(Common_LED);
		myDelay(500000);
		LED_Off(Common_LED);
		myDelay(500000);
}
	osSemaphoreRelease(S_ID);
	f2=0;
	osThreadExit();
}

void get1(void *argument)
{
	f1=1;
	int i=5;
	while (i--){
	LED_On(Common_LED);
		myDelay(78498);
		LED_Off(Common_LED);
		myDelay(78498);
}
	osSemaphoreRelease(S_ID);
	f1=0;
	osThreadExit();
}
	

void Child1(void *argument)
{
	
	
	while(1){
	if(f1==0){
	shm = osSemaphoreAcquire(S_ID,0);
	if(shm == osOK)
	{
		osThreadNew(get1,NULL,NULL);
	}
	}
	
		
	LED_On(Child_LED);
	myDelay(100000);
	LED_Off(Child_LED);
	myDelay(100000);
	}
}


void Child2(void *argument)
{
	while(1){

	if(f2 == 0){
		
	shm = osSemaphoreAcquire(S_ID,0);
	if(shm == osOK)
	{
		osThreadNew(get2,NULL,NULL);
	}}
	
	LED_On(Parent_LED);
	myDelay(500000);
	LED_Off(Parent_LED);
	myDelay(500000);
	}
}

int main()
{
	
	LED_Initialize();
	SystemCoreClockUpdate();
	osKernelInitialize();
	S_ID = osSemaphoreNew(1,1,NULL);
	ID1 = osThreadNew(Child1,NULL,NULL);
	ID2 = osThreadNew(Child2,NULL,NULL);
	osKernelStart();
	while(1);
	
	
	
}
