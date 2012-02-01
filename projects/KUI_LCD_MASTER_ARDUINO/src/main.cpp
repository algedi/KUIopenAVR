/*
  main.cpp - TWI/I2C library for iiKUIno project
  Copyright (c) 2011 Andrea Calvia (algedi_kui@ilnaufrago.it).  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <WProgram.h>
#include <KuiMaster.h>

// **********************
// * LCD LUI CONNECTION *
// * Command list       *
// **********************

#define LCD_CLEAR	1
#define LCD_PRINT	2
#define LCD_VERS	3
#define LCD_POSY	4
#define LCD_POSX    5

#define KEY_LEN		1
#define KEY_DATA	2
#define KEY_CLEAR	3
#define KEY_TEST	4
#define KEY_GET	5

// ****************
// * Set KUI card *
// * Command list *
// ****************

#define LCD_BUS  		5
#define LCD_PORT 		1

#define KEY_BUS			6
#define KEY_PORT		1

KuiMaster oBus = KuiMaster();

void EventRx(uint8_t uAddress, uint8_t uPort, uint8_t uCmd, uint8_t* uuData, uint8_t uLength)
{
	switch(uAddress)
	{
		case KEY_BUS:
			switch(uPort)
			{
				case KEY_PORT:
					switch(uCmd)
					{
						case KEY_LEN:
							oBus.Send(LCD_BUS, LCD_PORT, LCD_PRINT, "LEN");
							break;
						case KEY_DATA:
							oBus.Send(LCD_BUS, LCD_PORT, LCD_PRINT, "DATA");
							break;
					}	
					break;
			}
			break;
	}
}



int main(void)
{
	init();
	Serial.begin(9600);

//	oBus.SetEventReceive(EventRx);

//	oBus.Send(LCD_BUS, LCD_PORT, LCD_CLEAR);
//	delay(500);
//	oBus.Send(LCD_BUS, LCD_PORT, LCD_VERS);
//	delay(500);
//	oBus.Send(LCD_BUS, LCD_PORT, LCD_PRINT, "ciao");
//	delay(500);
    
	while (true)
	{

		uint8_t uuA[30];
		uint8_t nA = oBus.Get(KEY_BUS, KEY_PORT, KEY_LEN);
		Serial.print("LEN: ");
		Serial.println((int) nA);

//		nA = oBus.Get(KEY_BUS, KEY_PORT, KEY_DATA, uuA);
//		for (int n = 0; n < nA; n++)
//		{
//			Serial.println((char) uuA[n]);
//		}

		char cA = (char) oBus.Get(KEY_BUS, KEY_PORT, KEY_GET);
		if(cA != 0)
			Serial.println(cA);


		nA = oBus.Get(KEY_BUS, KEY_PORT, KEY_TEST, uuA);
		for (int n = 0; n < nA; n++)
		{
			Serial.print((char) uuA[n]);
		}
		Serial.println(".");

		delay(2000);
    }
   
	return 0;
}

