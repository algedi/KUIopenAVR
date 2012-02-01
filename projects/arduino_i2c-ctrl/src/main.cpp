#include <WProgram.h>
#include <Wire.h>

// ARDUINO I2C(master) <<=>> SERIAL

void setup();
void loop();

void LCDWriteStr(int, int, char*, int);
void LCDWriteChar(int, int, char);
void LCDWriteInt(int, int , int);
void LCDClear(void);
void LCDAbout(void);
char GetChar(void);
void KEYRead(void);
int ADCRead(int);

int nT, nD, nA, nN;
bool bTx;
char ccKey[10];
uint16_t nCount = 0;
void setup() 
{
	Wire.begin();
	Serial.begin(9600);

	for(int n = 0; n < 10; n++)
		ccKey[n] = 0;

	LCDClear();
	delay(100);
	LCDWriteStr(0, 0, "Premi 1 per ADC ", 16);
	delay(100);
	LCDWriteStr(0, 1, "Premi 2 per ADC ", 16);
	delay(1000);
	LCDClear();
	delay(1000);
}

void loop()
{
//			LCDWriteInt(10, 1, nCount);
//			nCount++;

			int n = ADCRead(0);
			LCDWriteInt(0, 0, n);
			n = ADCRead(1);
			LCDWriteInt(10, 0, n);
			n = ADCRead(2);
			LCDWriteInt(0, 1, n);

//	if(ccKey[0] > 0)
//	{
//		char c = GetChar();
//		if(c == '1')
//		{
//			int n = ADCRead(0);
//			LCDClear();delay(100);
//			LCDWriteStr(0, 0, "ADC 1           ", 16);delay(100);
//			LCDWriteInt(10, 1, n);
//		} 
//		else if(c == '2')
//		{
//			int n = ADCRead(1);
//			LCDClear();delay(100);
//			LCDWriteStr(0, 0, "ADC 2           ", 16);delay(100);
//			LCDWriteStr(10, 1, "funz", 4);delay(100);
//		}
//		else if(c == '3')
//		{
//			int n = ADCRead(2);
//			LCDClear();delay(100);
//			LCDWriteStr(0, 0, "ADC 3           ", 16);delay(100);
//		}
//	}

//	KEYRead();
	delay(1000);
}

void LCDWriteInt(int nX, int nY, int nInt)
{
	uint16_t n = (uint16_t) nInt;
	uint8_t str[] = {"ciao "};
	str[0] = (uint8_t) (n / 10000);
	n = n - (uint16_t)str[0] * 10000;
	str[1] = (uint8_t) (n / 1000);
	n = n - (uint16_t)str[1] * 1000;
	str[2] = (uint8_t) (n / 100);
	n = n - (uint16_t)str[2] * 100;
	str[3] = (uint8_t) (n / 10);
	n = n - (uint16_t)str[3] * 10;
	str[4] = (uint8_t) n;

	Serial.print(str[0], DEC);
	Serial.print(".");
	Serial.print(str[1], DEC);
	Serial.print(".");
	Serial.print(str[2], DEC);
	Serial.print(".");
	Serial.print(str[3], DEC);
	Serial.print(".");
	Serial.print(str[4], DEC);
	Serial.print("   ");


//	str[0] = 0;
//	str[1] = 1;
//	str[2] = 2;
//	str[3] = 3;
//	str[4] = 4;

	for(int n = 0; n < 5; n++)
		str[n] = str[n] + 48;
    LCDWriteStr(nX, nY, (char*) str, 5);
	Serial.print(nInt, DEC);
	Serial.print("-");
	Serial.print(str[0]);
	Serial.print(str[1]);
	Serial.print(str[2]);
	Serial.print(str[3]);
	Serial.println(str[4]);
} 

void LCDWriteStr(int nX, int nY, char* ccStr, int nChar)
{
	Wire.beginTransmission(4);
	Wire.send(1);
	Wire.send(nX);
	Wire.send(nY);
	Wire.send((uint8_t*)ccStr, nChar);
 	Wire.endTransmission();
} 

void LCDWriteChar(int nX, int nY, char c)
{
	Wire.beginTransmission(4);
	Wire.send(1);
	Wire.send(nX);
	Wire.send(nY);
	Wire.send((uint8_t) c);
 	Wire.endTransmission();
} 

void LCDClear()
{
	Wire.beginTransmission(4);
	Wire.send(0);
 	Wire.endTransmission();
} 

void LCDAbout()
{
	Wire.beginTransmission(4);
	Wire.send(10);
 	Wire.endTransmission();
} 

void KEYRead()
{
	int n = 0;
	char ccBuffer[10] = {0,0,0,0,0,0,0,0,0,0};
	Wire.beginTransmission(5);
	Wire.send(0); 
 	Wire.endTransmission();
	delay(200);
	Wire.requestFrom(5, 8);
	while(Wire.available())
	{
		ccBuffer[n] = Wire.receive();
		n++;
	}
	for( n = 1; n < ccBuffer[0]+1; n++)
	{
		ccKey[0]++;
		ccKey[ccKey[0]] = ccBuffer[n];
	}
} 

int ADCRead(int nAdc)
{
	int n = 0;
	char ccBuf[10] = {0,0,0,0,0,0,0,0,0,0};
	Wire.beginTransmission(5);
	Wire.send(1); 
 	Wire.endTransmission();
	delay(200);
	Wire.requestFrom(5, 8);
	while(Wire.available())
	{
		ccBuf[n] = Wire.receive();
		n++;
	}
	n = ccBuf[nAdc*2 + 1]*256 + ccBuf[nAdc*2];
	return n;
}

char GetChar()
{
	if(ccKey[0] > 0)
	{
		char c = ccKey[1];
		for(int n = 1; n < ccKey[0]; n++)
			ccKey[n] = ccKey[n+1]; 
		ccKey[0]--;
		return c;
	}
}


int main(void)
{
	init();
	setup();
    
	for (;;)
		loop();
        
	return 0;
}

	// Lettura tastiera
	//	Wire.beginTransmission(5);
	//	Wire.send(0); 
	// 	Wire.endTransmission();

	//	// Scrittura LCD
	//	Wire.beginTransmission(4);
	//	Wire.send(1);
	//	Wire.send(0);
	//	Wire.send(0);
	//	Wire.send("Trasmesso 0x00");
	// 	Wire.endTransmission();
	//	delay(200);

	//	n = 0;
	//	Wire.requestFrom(5, 8);
	//	while(Wire.available())
	//	{
	//		ccBufferA[n] = Wire.receive();
	//		n++;
	//	}
	//	Serial.println("Trasmesso 0x01");
	//	delay(200);

	//	Wire.requestFrom(5, 6);    // request 6 bytes from slave device #2

	//	int n = 0;
	//	bool bLow = true;
	//	while(Wire.available())    // slave may send less than requested
	//	{
	//		if(bLow)
	//		{
	//			n = Wire.receive();
	//			bLow = false;
	//		}
	//		else
	//		{
	//			int c = Wire.receive();
	//			n = n + (c << 8);
	//			bLow = true;
	//		}
	//		if (bLow) Serial.println(n);
	//	}

