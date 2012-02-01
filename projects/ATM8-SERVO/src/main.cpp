#include <WProgram.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created
 
int pos = 0;    // variable to store the servo position
 
void setup()
{
//  myservo.attach(0);  // attaches the servo on pin 9 to the servo object
}
 
 
void loop()
{
	myservo.attach(0);  // attaches the servo on pin 9 to the servo object
	for(pos = 2; pos < 178; pos += 2)  // goes from 0 degrees to 180 degrees
	{                                  // in steps of 1 degree
		myservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(20);                       // waits 15ms for the servo to reach the position
	}
	myservo.detach();  // attaches the servo on pin 9 to the servo object

	delay(20000);

	myservo.attach(0);  // attaches the servo on pin 9 to the servo object
	for(pos = 178; pos>2; pos-=2)     // goes from 180 degrees to 0 degrees
	{                                
		myservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(300);                       // waits 15ms for the servo to reach the position
	}
	myservo.detach();  // attaches the servo on pin 9 to the servo object

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

