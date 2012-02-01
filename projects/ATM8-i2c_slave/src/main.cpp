#include <WProgram.h>
#include <Wire.h>
#include <LiquidCrystal.h>

void setup();
void loop();
void receiveEvent(int);


int nnCmd[] = {0, 0, 0, 0};
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

char ccLcd1[9];
char ccLcd2[9];

void setup() 
{
	int nX;
	lcd.begin(10, 2);
	for(nX = 0; nX < 10; nX++)
	{
		ccLcd1[nX] = '.';
		ccLcd2[nX] = '.';
	}
	Wire.begin(4);                // join i2c bus with address #4
	Wire.onReceive(receiveEvent); // register event
	Write(1);
	Write(2);
	lcd.print("hello, world!");
}

void loop() 
{

}

void receiveEvent(int howMany) 
{
	int nX;
	nX = Wire.receive();
	if(nnCmd[0] == 0)
	{
		if(nX == 0) Clear();
		else if(nX == 1) Write(1);
		else if(nX == 2) Write(2);
		else if(nX == 3) {Write(1); Write(2);}
		else if(nX == 4) nnCmd[0] = 4;
	}
	else if(nnCmd [0] == 4)
	{
		lcd.setCursor(1, 1);
		lcd.print(x);
	}
	else if(nCmd == 2)
	{
		
	}
}

void Clear()
{
	int nX;
	for(nX = 0; nX < 10; nX++)
	{
		ccLcd1[nX] = '.';
		ccLcd2[nX] = '.';
	}
	Write(1);
	Write(2);
	nnCmd[0];
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}
