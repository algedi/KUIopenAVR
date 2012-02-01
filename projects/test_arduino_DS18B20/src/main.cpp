#include <WProgram.h>
#include <OneWire.h>

OneWire  ds(10);  // on pin 10

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
}



void loop(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  int Temp;
  if ( !ds.search(addr)) {
	//Serial.print("No more addresses.\n");
	ds.reset_search();
	return;
  }

  Serial.print("R=");  //R=28 Not sure what this is
  for( i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
	Serial.print("CRC is not valid!\n");
	return;
  }

  if ( addr[0] != 0x28) {
	Serial.print("Device is not a DS18S20 family device.\n");
	return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);	   // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);	   // Read Scratchpad

  Serial.print("P=");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {	     // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print("  ");
  }
  Temp=(data[1]<<8)+data[0];//take the two bytes from the response relating to temperature

  Temp=Temp>>4;//divide by 16 to get pure celcius readout

  //next line is Fahrenheit conversion
  Temp=Temp*1.8+32; // comment this line out to get celcius

  Serial.print("T=");//output the temperature to serial port
  Serial.print(Temp);
    Serial.print("  ");


  Serial.print(" CRC=");
  Serial.print( OneWire::crc8( data, 8), HEX);
  Serial.println();
}

 
















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
