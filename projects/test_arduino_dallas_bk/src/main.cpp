#include <WProgram.h>
#include <OneWire.h>

void setup();
void loop();

OneWire ds(10);  // on pin 10

void setup(void) 
{
  Serial.begin(9600);
}

void loop(void) 
{
		int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

		byte i;
		byte present = 0;
		byte data[12];
		uint8_t addr[8];

		if ( !ds.search(addr)) 
		{
			Serial.println("No more addresses.\n");
			ds.reset_search();
delay(500);
			return;
		}

//	  Serial.print("R=");
		for( i = 0; i < 8; i++) 
		{
		}
		if ( OneWire::crc8( addr, 7) != addr[7]) 
		{
			// Serial.print("CRC is not valid!\n");
			return;
		}

		if ( addr[0] != 0x28) 
		{
			// Serial.println("Device is not a DS18S20 family device.\n");
			delay(1000);
			return;
		}

		ds.reset();
		ds.select(addr);
		ds.write(0x44,1);         // start conversion, with parasite power on at the end

		delay(1000);     // maybe 750ms is enough, maybe not
		// we might do a ds.depower() here, but the reset will take care of it.

		present = ds.reset();
		ds.select(addr);    
		ds.write(0xBE);         // Read Scratchpad

//	  Serial.print("P=");
//	  Serial.print(present,HEX);
//	  Serial.print(" ");
		for ( i = 0; i < 9; i++) 
		{           // we need 9 bytes
			data[i] = ds.read();
		}
//	  Serial.print(" CRC=");
//	  Serial.print( OneWire::crc8( data, 8), HEX);
		Serial.println();

//		TReading = ds.ReadS18B20();

		LowByte = data[0];
		HighByte = data[1];
		TReading = (HighByte << 8) + LowByte;
		SignBit = TReading & 0x8000;  // test most sig bit
		if (SignBit) // negative
		{
			TReading = (TReading ^ 0xffff) + 1; // 2's comp
		}
		Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

		Whole = Tc_100 / 100;  // separate off the whole and fractional portions
		Fract = Tc_100 % 100;

		if (SignBit) // If its negative
		{
			Serial.print("-");
		}
		Serial.print(Whole);
		Serial.print(".");
		if (Fract < 10)
		{
			Serial.print("0");
		}
		Serial.print(Fract);

		ds.reset_search();
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

