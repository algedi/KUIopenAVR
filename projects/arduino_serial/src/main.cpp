#include <WProgram.h>

// ARDUINO <<=>> Serial

int n;

void PrimaPagina()
{
	Serial.println("****************");
	Serial.println("* PRIMA PAGINA *");
	Serial.println("****************");
	Serial.println("---------------------------------");    
	Serial.println("1 - Inizia");    
	Serial.println("2 - Saluta");

	while (true)
	{    
		if (Serial.available() > 0)
		{	
			n = Serial.read();
			if (n == 49) {Serial.println("dinuovo 1"); }
			if (n == 50) return; 
		}  
		delay(500);
	}
}


int main(void)
{
	init();

	delay(10000);
	Serial.begin(9600);
	Serial.println("***********");
	Serial.println("* WELCOME *");
	Serial.println("***********");

	Serial.println("START");    
	Serial.println("1 - Inizia");    
	Serial.println("2 - Saluta");

	while (true)
	{    
		if (Serial.available() > 0)
		{	
			n = Serial.read();
			if (n == 49) {Serial.println("Bene adesso si fa sul serio"); PrimaPagina();}
			if (n == 50) Serial.println("FINITO");
		}  
		delay(500);
	}

	return 0;
}
