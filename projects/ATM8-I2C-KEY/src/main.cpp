#include <WProgram.h>
#include <Wire.h>
#include "EEPROM.h"
#include <avr/eeprom.h>
#include <Keypad.h>

void setup();
void loop();
void EventRequest();
void EventReceive(int); 

//int nnDatiIn[10];
char ccDataIn[10];
char ccDataKey[10]; // = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
char ccDataAdc[6];
char ccDataDgt[5];

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

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void loop()
{
	nKey = ccDataKey[0];
	if(nKey < 9)
	{
		char key = keypad.getKey();
		if (key != NO_KEY)
		{
			nKey++;
			ccDataKey[nKey] = key;
			ccDataKey[0] = nKey;
		}
	}
	
	int n = 0;
	n = analogRead(0);
	ccDataAdc[0] = (char) n;
	n = n >> 8;
	ccDataAdc[1] = (char) n;
	n = analogRead(1);
	ccDataAdc[2] = (char) n;
	n = n >> 8;
	ccDataAdc[3] = (char) n;
	n = analogRead(6);
	ccDataAdc[4] = (char) n;
	n = n >> 8;
	ccDataAdc[5] = (char) n;




	delay(200);
}

void EventRequest()
{
	if(ccDataIn[0] == 0)
	{
		Wire.send((uint8_t*)ccDataKey, 8);
		for(int n = 0; n < 9; n++)
			ccDataKey[n] = 0;
	}
	else if(ccDataIn[0] == 1)
		Wire.send((uint8_t*)ccDataAdc, 6);
	else if(ccDataIn[0] == 2)
		Wire.send((uint8_t*)ccDataDgt, 5);			
}

void EventReceive(int nDati) 
{
	for (int n = 0; n < 10; n++)
		if(n < nDati)
			ccDataIn[n] = Wire.receive();
		else
			ccDataIn[n] = 0;			
}


void setup()
{
	Wire.begin(5);
	Wire.onRequest(EventRequest);
	Wire.onReceive(EventReceive);
	for(int n = 0; n < 10; n++)
		ccDataIn[n] = 0;
}

int main(void)
{
	init();
	setup();
	for (;;)
		loop();
	return 0;
}

