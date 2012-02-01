#include <WProgram.h>
#include <MsTimer2.h>
#include <SdFat.h>

SdFat sd;
SdFile myFile;
////const int chipSelect = 10;
int nCount;
int nValue[100];
int nMin;



void ScriviSd(void)
{
	int n;
	n = 0;

	Serial.println("ScriviSd1");

	if (!sd.init(SPI_HALF_SPEED, 10)) 
	{
		Serial.println("ScriviSd-error init");
		sd.initErrorHalt();
	}
	Serial.println("ScriviSd2");
	if (!myFile.open("test-1.txt", O_WRITE | O_CREAT | O_APPEND)) 
	{
	Serial.println("ScriviSd3");
		sd.errorHalt("opening test.txt for write failed");
	} 
	Serial.println(nMin);

	for(n = 0; n < nCount; n++)
	{
		myFile.print("TIME: ");
		myFile.print(nMin);
		myFile.print(" min. - VALUE    : ");
		myFile.print(nValue[n]);
		myFile.println(" mTesla");
	}
	Serial.println("ScriviSd5");
	nCount = 0;
	nMin++;	

	myFile.close();
}

void ClockEvent(void)
{
	Serial.println("ClockEvent");
	nValue[nCount] = analogRead(0);
	nCount++;
//	ScriviSd();
}

int main(void)
{
	init();   					// Arduino
	Serial.begin(9600);
	nCount = 0;
	nMin = 0;

	MsTimer2::set(1000, ClockEvent); // 500ms period
	MsTimer2::start();

	while(true)
	{
		if(nCount > 60)
		{
			ScriviSd();
			nCount = 0;
		}
	}
	return 0;
}




//	Serial.println("pausa");

//  	if (!myFile.open("test.txt", O_READ)) 
//	{
//    	sd.errorHalt("opening test.txt for read failed");
//  	} 
//	Serial.println("test.txt:");
//    
//	int data;
//	while ((data = myFile.read()) > 0) 
//		Serial.write(data);
//	myFile.close();

//    Serial.print("Fine ...");

