#include <WProgram.h>
#include <LiquidCrystal.h>
#include <KuiSlave.h>
//#include "EEPROM.h"
//#include <avr/eeprom.h>

//	return eeprom_read_byte((unsigned char *) address);
//	eeprom_write_byte((unsigned char *) address, value);

#define LCD_BUS			5
#define LCD_PORT		1
#define LCD_CMD_CLEAR	1
#define LCD_CMD_PRINT	2
#define LCD_CMD_VERS	3


// I2C(slave) <<=>> LCD

void EventReceive(int); 
void EventSetup(int); 

LiquidCrystal oLcd(10, 9, 8, 7, 6, 5);
KuiSlave oBus = KuiSlave(LCD_BUS);  // I2C address 5

void EventBusRx(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength) 
{
	oLcd.clear();
	delay(1000);
	oLcd.setCursor(0, 0);
	oLcd.print("PORT: ");
	oLcd.print((int) uPort);
	delay(500);
	oLcd.setCursor(0, 1);
	oLcd.print("CMD: ");					
	oLcd.print((int) uCmd);
	delay(500);
	


	switch (uPort)
	{
		case LCD_PORT:
			switch (uCmd)
			{
				case LCD_CMD_CLEAR:
					oLcd.clear();
					break;
				case LCD_CMD_VERS:
					oLcd.clear();
					oLcd.setCursor(0, 0);
					oLcd.print("KUI-team (c)");
					delay(1000);
					oLcd.setCursor(0, 1);
					oLcd.print("Ver. 1.0");					
					delay(100);
					break;
				case LCD_CMD_PRINT:
					oLcd.clear();
					oLcd.setCursor(0, 0);
					for(uint8_t n = 0; n < uLength; n++)
						oLcd.print((char) uuData[n]);					
					break;
			}
	}
}


int main(void)
{
	init();

	oLcd.begin(2, 16);

	oLcd.setCursor(0, 0);
	oLcd.print("KUI-team (c)");
	delay(1000);
	oLcd.setCursor(0, 1);
	oLcd.print("II2C <=> LCD");

	oBus.SetEventReceive(EventBusRx);
    
	for (;;)
	{
	}
        
	return 0;
}
