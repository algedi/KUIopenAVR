#include <WProgram.h>
#include <Stepper.h>

// Esempio Blink - www.arduino.cc
// void Setup() 
// {                
//   pinMode(13, OUTPUT);    
// }

// void Loop() 
// {
//   digitalWrite(13, HIGH);
//   delay(1000);            
//   digitalWrite(13, LOW); 
//   delay(1000);           
// }

// **********************************
// la funzione main() non si vede su
// l'esempio Blink - www.arduino.cc
// **********************************
Stepper oStep_1(2048, 8, 10, 9, 11);
Stepper oStep_2(2048, 4, 6, 5, 7);
Stepper oStep_3(2048, 0, 2, 1, 3);


int main(void)
{
	init();   					// Arduino
    oStep_1.setSpeed(10);
    oStep_2.setSpeed(4);
    oStep_3.setSpeed(6);

	pinMode(13, OUTPUT);    
	while(true) 
	{
  	  oStep_1.step(2048);
//  	  oStep_2.step(2000);
//  	  oStep_3.step(2000);
	  delay(1000);   
	}
     
	return 0;
}
