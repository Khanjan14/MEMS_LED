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
		if(osSemaphoreWait(sem_id,osWaitForever)>0){
				int i = 5;
				while (i--){
					LED_On(LED_shared);
					LED_On(LED_child1);
					my_delay(DELAY1);
					LED_Off(LED_shared);
					LED_Off(LED_child1);
					my_delay(DELAY1);
				}
				osSemaphoreRelease(sem_id);
		}
	}
}

void child1(void const *arguments){
	for (;;) {
		if(osSemaphoreWait(sem_id,osWaitForever)>0){
				int i = 5;
				while (i--){
					LED_On(LED_shared);
					LED_On(LED_child2);
					my_delay(DELAY2);
					LED_Off(LED_shared);
					LED_Off(LED_child2);
					my_delay(DELAY2);
				}
				osSemaphoreRelease(sem_id);
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
