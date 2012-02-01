#include <WProgram.h>
#include <OneWire.h>


void setup();
void loop();

DS18B20 ds(10);  // on pin 10

void setup(void) 
{
  Serial.begin(9600);
}

void loop(void) 
{
	int nCelsius;
	int nDecimal;

	if (ds.Read())
	{
		Serial.print("....");
		if(ds.IsPositive()) Serial.print("+");
		else Serial.print("-");
		nCelsius = ds.GetCelsius();
		Serial.print(nCelsius, DEC);
		Serial.print(".");
		Serial.println(ds.GetDecimal(1), DEC);

		Serial.print("    ");
		if(ds.IsPositive()) Serial.print("+");
		else Serial.print("-");
		nCelsius = ds.GetCelsius();
		Serial.print(nCelsius, DEC);
		Serial.print(".");
		nDecimal = ds.GetDecimal(2);
		if(nDecimal < 10) Serial.print("0");
		Serial.println(nDecimal, DEC);

		Serial.print("    ");
		if(ds.IsPositive()) Serial.print("+");
		else Serial.print("-");
		nCelsius = ds.GetCelsius();
		Serial.print(nCelsius, DEC);
		Serial.print(".");
		nDecimal = ds.GetDecimal(3);
		if(nDecimal < 10) Serial.print("0");
		if(nDecimal < 100) Serial.print("0");
		Serial.println(nDecimal, DEC);

		Serial.print("    ");
		if(ds.IsPositive()) Serial.print("+");
		else Serial.print("-");
		nCelsius = ds.GetCelsius();
		Serial.print(nCelsius, DEC);
		Serial.print(".");
		nDecimal = ds.GetDecimal(4);
		if(nDecimal < 10) Serial.print("0");
		if(nDecimal < 100) Serial.print("0");
		if(nDecimal < 1000) Serial.print("0");
		Serial.println(nDecimal, DEC);

	}
	delay(2000);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

