#include <WProgram.h>
#include <Wire.h>

// ARDUINO I2C(master) <<=>> SERIAL

void setup();
void loop();

int nT, nD, nA, nN;
bool bTx;
void setup() 
{
	Wire.begin(); // join i2c bus (address optional for master)
	Serial.begin(9600);
}

void loop()
{
	Wire.requestFrom(5, 6);    // request 6 bytes from slave device #2

	while(Wire.available())    // slave may send less than requested
	{
		char c = Wire.receive(); // receive a byte as character
		Serial.print(c, DEC);         // print the character
	}
	Serial.println("-");
	delay(100);
}



int main(void)
{
	init();
	setup();
    
	for (;;)
		loop();
        
	return 0;
}

