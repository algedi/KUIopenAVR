#include <WProgram.h>
//#include <MsTimer2.h>
#include <SdFat.h>
#include <SdFile.h>


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
	if (!sd.init(SPI_HALF_SPEED, 10)) 
	{
		sd.initErrorHalt();
		return;
	}

	if (!myFile.open("test-1.txt", O_WRITE | O_CREAT | O_APPEND)) 
	{
		delay(800);
		digitalWrite(7, LOW);
		delay(200);
		digitalWrite(7, HIGH);
		delay(800);
		sd.errorHalt("opening test.txt for write failed");
		return;
	} 
//	Serial.println(nMin);

//	for(n = 0; n < nCount; n++)
//	{
//	myFile.print("TIME: ");
//	myFile.print(nMin);
//	myFile.print(" min. - VALUE    : ");
//	myFile.print(nValue[n]);
	myFile.println(" mTesla");
//	}
//	Serial.println("ScriviSd5");
//	nCount = 0;
//	nMin++;	

	myFile.close();
}



int main(void)
{
	init();

	pinMode(7, OUTPUT);

	while(true)
	{
		digitalWrite(7, LOW);
		delay(200);
		digitalWrite(7, HIGH);
		delay(800);
		digitalWrite(7, LOW);
		delay(200);
		digitalWrite(7, HIGH);
		delay(800);

		ScriviSd();

//		digitalWrite(7, HIGH);
		delay(500);
		digitalWrite(7, LOW);
		delay(500);
	}
	return 0;
}
