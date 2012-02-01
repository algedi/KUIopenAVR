#include <WProgram.h>

int ledPin =  13;    // LED connected to digital pin 13
void setup();
void loop();

void setup() 
{
  pinMode(ledPin, OUTPUT);     
}

void loop() 
{
	for(int n=1; n<40; n++)
	{
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  delay(20);                  // wait for a second
	  digitalWrite(ledPin, LOW);    // set the LED off
	  delay(60);                  // wait for a second
	}
	delay(10000);
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}
