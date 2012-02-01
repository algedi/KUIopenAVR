#include <WProgram.h>
#include <KuiSlave.h>

#define CORE_BUS		10
#define CAM_PORT		1
#define WC_PORT			2
#define CAM_1			1
#define CAM_2			2
#define CAM_3			3
#define WC_DIR_OPEN		1
#define WC_DIR_CLOSE	2
#define WC_ON			3
#define WC_OFF			4

void EventReceive(int); 
void EventSetup(int); 

KuiSlave oBus = KuiSlave(CORE_BUS);

void EventBusRx(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength) 
{
	switch (uPort)
	{
		case CAM_PORT:
			switch (uCmd)
			{
				case CAM_1:
					digitalWrite(6, HIGH);
					digitalWrite(7, LOW);
					break;
				case CAM_2:
					digitalWrite(6, LOW);
					digitalWrite(7, HIGH);
					break;
				case CAM_3:
					digitalWrite(7, HIGH);
					digitalWrite(8, HIGH);
					break;
			}
		case WC_PORT:
			switch (uCmd)
			{
				case WC_DIR_OPEN:
					digitalWrite(8, LOW);
					break;
				case WC_DIR_CLOSE:
					digitalWrite(8, HIGH);
					break;
				case WC_ON:
					digitalWrite(5, HIGH);
					break;
				case WC_OFF:
					digitalWrite(5, LOW);
					break;
			}
	}
}


int main(void)
{
	init();

	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);

	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
	delay(1000);
	digitalWrite(6, HIGH);
	delay(1000);
	digitalWrite(7, HIGH);
	delay(1000);
	digitalWrite(8, HIGH);
	delay(1000);


	oBus.SetEventReceive(EventBusRx);
    
	for (;;)
	{
	}
        
	return 0;
}
