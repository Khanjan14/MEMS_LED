#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os.h"
#include "stm32f4xx.h"
#include "Board_LED.h"

#define Parent_LED 0
#define Common_LED 1
#define Child_LED 2

void Child1(void const *argument);
void Child2(void const *argument);
void get1(void const *argument);
void get2(void const *argument);


int count=0;
osThreadId ID1,ID2;

osThreadDef (Child1, osPriorityNormal, 1, 0);         // thread object
osThreadDef (Child2, osPriorityNormal, 1, 0);         // thread object
osThreadDef (get1, osPriorityNormal, 1, 0);         // thread object
osThreadDef (get2, osPriorityNormal, 1, 0);         // thread object

osSemaphoreId S_ID;
osSemaphoreDef(smp);

//osStatus shm;
int f1=0,f2=0;


void myDelay(int i){
	while(i--);
}

void child2 (void const *argument) { 
	for (;;) {
		if(osSemaphoreWait(S_ID,osWaitForever)>0){
				int i = 5;
				while (i--){
					LED_On(Common_LED);
					LED_On(Parent_LED);
					my_delay(1000000);
					LED_Off(Common_LED);
					LED_Off(Parent_LED);
					my_delay(1000000);
				}
				osSemaphoreRelease(S_ID);
		}
	}
}

void child1(void const *arguments){
	for (;;) {
		if(osSemaphoreWait(S_ID,osWaitForever)>0){
				int i = 5;
				while (i--){
					LED_On(Common_LED);
					LED_On(Child_LED);
					my_delay(2000000);
					LED_Off(Common_LED);
					LED_Off(Child_LED);
					my_delay(2000000);
				}
				osSemaphoreRelease(S_ID);
		}
	}
}

int main()
{
	
	LED_Initialize();
	SystemCoreClockUpdate();
	

	osKernelInitialize();
	S_ID = osSemaphoreCreate (osSemaphore(smp), 1);
	ID1 = osThreadCreate(osThread(Child1),NULL);
	ID2 = osThreadCreate(osThread(Child2),NULL);
	osKernelStart();
	while(1);
	
	
	
}
