#include <WProgram.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "EEPROM.h"
#include <avr/eeprom.h>

//	return eeprom_read_byte((unsigned char *) address);
//	eeprom_write_byte((unsigned char *) address, value);


// I2C(slave) <<=>> LCD

void setup();
void loop();
void EventReceive(int); 
void EventSetup(int); 

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
//TwoWire oI2C_Setup = TwoWire();
//TwoWire oI2C_Lcd = TwoWire();

void EventReceive(int nDati) 
{
	int nnDati[nDati];
	for (int n = 0; n < nDati; n++)
		nnDati[n] = Wire.receive();

	if( nnDati[0] == 0)
		lcd.clear();

	if(nnDati[0] == 1)
	{
		lcd.setCursor(nnDati[1], nnDati[2]);
//		lcd.print( (char) nnDati[3] );
		for (int n = 3; n < nDati; n++)
			lcd.print( (char) nnDati[n] );
	}

	if(nnDati[0] == 10)
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("KUI-team (c)");
//		delay(1000);
		lcd.setCursor(0, 1);
		lcd.print("I2C <=> LCD");
//		delay(3000);
	}
		
}

//void EventSetup(int nMany) 
//{
//	lcd.clear();
//	lcd.setCursor(0, 0);
//	lcd.print("EventSetup      ");
//	delay(4000);
//	lcd.clear();

////	delay(1000);
////	lcd.setCursor(0, 1);
////	lcd.print("ATTENDERE       ");
////	delay(2000);
////	
////	lcd.clear();

////	lcd.setCursor(0, 0);
////	lcd.print("START     ");
////	lcd.setCursor(0, 1);
////	lcd.print("          ");
////	delay(2000);

////	lcd.clear();


////	int nX;
////	if (nMany == 2)
////	{	
////		lcd.setCursor(0, 1);
////		lcd.print("Setup I2C");
////		delay(1000);

////		int nAddress = oI2C_Setup.receive();
////		int nDato = oI2C_Setup.receive();

////		lcd.setCursor(0, 0);
////		lcd.print("A:");
////		lcd.print(nAddress);
////		lcd.setCursor(0, 1);
////		lcd.print("D: ");
////		lcd.print(nDato);

////		delay(2000);
////		//eeprom_write_byte((uint8_t*) nAddress,(uint8_t) nDato);
////	}
////	else
////	{
////		lcd.setCursor(0, 1);
////		lcd.print("Error comunication");
////		lcd.setCursor(1, 1);
////		lcd.print("Setup I2C");
////		delay(2000);
////	}		
//////	lcd.setCursor(1, 1);
//////	lcd.print(nX);
//	
//}


void setup() 
{
	lcd.begin(2, 16);

	lcd.setCursor(0, 0);
	lcd.print("KUI-team (c)");
	delay(1000);
	lcd.setCursor(0, 1);
	lcd.print("I2C <=> LCD");

	Wire.begin(4);
	Wire.onReceive(EventReceive);
}

void loop() 
{
//  lcd.setCursor(10, 1);
//  lcd.print(millis()/1000);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}
