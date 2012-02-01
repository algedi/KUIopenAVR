#include <WProgram.h>
#include <Wire.h>

// ARDUINO I2C(master) <<=>> SERIAL

void setup();
void loop();
void menu();

void menu()
{
	Serial.println("********");
	Serial.println("* MENU *");
	Serial.println("********************************");
	Serial.println("M     - Memu");
	Serial.println("I     - Inizio trafmissione dati");    
	Serial.println("O     - Fine trasmissione dati");
	Serial.println("Invio - Fine numero");    
	Serial.println("********************************");
}

// byte x = 0;
int nT, nD, nA, nN;
bool bTx;
void setup() 
{
	Wire.begin(); // join i2c bus (address optional for master)

	Serial.begin(9600);
	menu();

	pinMode(2, OUTPUT);     
	digitalWrite(2, LOW);
	nA = 0;
	nD = 0;
	nN = 0;
	bTx = false;
	Serial.println(nA, DEC);
	Serial.println("\n***********************************************");
	Serial.println("Digita il numero del nuovo dispositivo oppure");
	Serial.println("premi I per iniziare la trasmissine dei dati");
	Serial.print("\nIl dispositivo selezionato è il N:");
	Serial.println(nA, DEC);
	Serial.println("***********************************************");
}

void loop()
{
	if (Serial.available() > 0)
	{	
		nT = Serial.read();
		if(nT == 13)
		{
			if(nN >= 0 && nN <= 255)
			{
				if(bTx)
				{
					Wire.send(nN); 
					Serial.print(" >> Trasmesso al dispositivo ");
					Serial.print(nA, DEC);
					Serial.print(" il dato ");
					Serial.println(nN, DEC);
				}
				else
				{
					nA = nN;
					Serial.print(" >> Selezionato il dispositivo n. ");
					Serial.println(nA, DEC);
				}
			}
			else
			Serial.println(" >> numero non valido - operazione annullata");
			nN = 0;
		}

		if(nT == 109) menu();                              // M

		if(nT == 105)                                      // I
		{
			Wire.beginTransmission(nA);
			Serial.println("INIZIO TRASMISSIONE DATI");
			bTx = true;
		}
		if(nT == 111)                                      // O
		{
			Wire.endTransmission();
			Serial.println("FINE TRASMISSIONE DATI");
			bTx = false;
		}

		if(nT >= 48 && nT <= 57)                           // da 0 a 9
		{
			nN = (nN * 10) + (nT - 48);
			Serial.print(nT - 48);
		} 
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

