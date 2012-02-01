#include <WProgram.h>
#include <KuiSlave.h>
#include <Keypad.h>

//#include "EEPROM.h"
//#include <avr/eeprom.h>

//	return eeprom_read_byte((unsigned char *) address);
//	eeprom_write_byte((unsigned char *) address, value);

#define KEY_BUS			6
#define KEY_PORT		1
#define KEY_LEN			1
#define KEY_DATA		2
#define KEY_CLEAR   	3
#define KEY_VER			4
#define KEY_GET			5

void EventReceive(int); 
void EventSetup(int); 

char ccKey[20];
int nKey = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 10, 11, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7, 8}; //connect to the column pinouts of the keypad

KuiSlave oBus = KuiSlave(KEY_BUS);  // I2C address 5

Keypad oKey = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void EventBusRx(uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength) 
{
	switch (uPort)
	{
		case KEY_PORT:
			switch (uCmd)
			{
				case KEY_CLEAR:
					nKey = 0;
					break;
			}
	}
}


uint8_t EventBusTx(uint8_t uPort, uint8_t uCmd, uint8_t* uuData) 
{
	uint8_t uLength = 0;
//	uuData[0] = 11;
//	uuData[1] = 12;
//	uuData[2] = 13;
//	uuData[3] = 14;
//	uuData[4] = 15;
//	uuData[5] = 16;


	switch (uPort)
	{
		case KEY_PORT:
			switch (uCmd)
			{
				case KEY_LEN:
					uuData[0] = nKey;
					uLength = 1;
					break;
				case KEY_DATA:
					uLength = nKey;
					for(int n = 0; n < nKey; n++)
						uuData[n] = ccKey[n];
					nKey = 0;
					break;
				case KEY_GET:
					uLength = 1;
					if(nKey > 0)
					{
						uuData[0] = ccKey[0];
						nKey--;
						for(int n = 0; n < nKey; n++)
						{
							ccKey[n] = ccKey[n+1];
						}
					}
					else uuData[0];
					break;
				case KEY_VER:
					uLength = 8;
					uuData[0] = 'V';
					uuData[1] = 'e';
					uuData[2] = 'r';
					uuData[3] = '.';
					uuData[4] = ' ';
					uuData[5] = '1';
					uuData[6] = '.';
					uuData[7] = '0';
					break;
			}
	}
	return uLength;
}



int main(void)
{
	init();

	oBus.SetEventReceive(EventBusRx);
	oBus.SetEventRequest(EventBusTx);
    
	for (;;)
	{
		if(nKey < 20)
		{
			char key = oKey.getKey();
			if (key != NO_KEY)
			{
				ccKey[nKey] = key;
				nKey++;
			}
		}	
	}
        
	return 0;
}
