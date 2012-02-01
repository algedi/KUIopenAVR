#include <WProgram.h>


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

int main(void)
{
	init();   					// Arduino

	pinMode(13, OUTPUT);    
	while(true) 
	{
	  digitalWrite(13, HIGH);   // set LED on
	  delay(2000);               // 0,1 Sec == 100mS
	  digitalWrite(13, LOW);    // set LED off
	  delay(1000);              // 1 Sec == 100mS
	}

	// ****************************************
	// Esempio Blink - www.arduino.cc
	// funzione nascoste per utenti Arduino IDE
	// ****************************************
	//	setup();
	//	for (;;)
	//		loop();
     
	return 0;
}
