#include <WProgram.h>
#include <KuiMaster.h>
#include <KuiSlave.h>

#define LCD_BUS      1
#define LCD_PORT     1
#define LCD_CLEAR    1
#define LCD_PRINT    2

void EventSlaveRx(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength)
{
	switch(uPort)
	{
		case LCD_PORT:
			switch(uCmd)
			{
				case LCD_CLEAR:
					break;
				case LCD_PRINT:
					break;
			}		
			break;
	}	
}


int main(void)
{
	init();
	Serial.begin(9600);
   
	KuiMaster oMaster = KuiMaster();
	KuiSlave oSlave = KuiSlave(1);
	oMaster.Send(LCD_BUS, LCD_PORT, LCD_CLEAR);
	oSlave.SetEventReceive(EventSlaveRx);
//	oBus.Set(LCD_BUS, LCD_PORT, LCD_PRINT, "Hello World!");

	return 0;
}

