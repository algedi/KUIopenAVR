#include <WProgram.h>
#include <SD.h>

#define MEM_PW 5
#define HELP "H help\nL file info\nD delete\nP append string\nW init file and write\nR dump to serial\nA append text\n"

byte inSerByte = 0;
void WriteMenu(void);

int main(void)
{
	init();   					// Arduino
 	Serial.begin(9600);
    Serial.println("Premi H per il MENU di aiuto\n");

    // on my MicroSD Module the power comes from a digital pin
    // I activate it at all times
    //  pinMode(MEM_PW, OUTPUT);
    //  digitalWrite(MEM_PW, HIGH);
    //  
    // configure the serial port to command the card and read data
    while (true)
    {
       // Arduino expects one of a series of one-byte commands
       // you can get some help by sending an 'H' over the serial port
       if (Serial.available() > 0) 
       {
          int result = 0;

          inSerByte = Serial.read();
          switch (inSerByte) 
	      {
		      case 'H':
		      	WriteMenu();
		      	result = 3; // special output for help message
		  	  	break;
			  case 'L':
		  		result = SD.ls("hola.txt");
		        break;
			  case 'R':
		  		result = SD.cat("hola.txt");
		        break;
			  case 'W':
		        result = SD.write("hola.txt");
		        result = SD.write("hola1.txt");
		        result = SD.write("hola2.txt");
		        result = SD.write("hola3.txt");
		        break;
		      case 'A':
		        result = SD.append("hola.txt");
		        break;
		      case 'P':
		        result = SD.println("hola.txt","\nhola caracola");
		        break;
		      case 'D':
		        result = SD.del("hola.txt");
		        break;
		      default:
		        result = 2; // value for unknown operation
		        break;
       	  }
    
          // print a status message for the last issued command
		  // for help (result == 3) won't print anything
		  if (result == 1) SD.printEvent(ERROR, "hola.txt");
		  else if (result == 2) SD.printEvent(WARNING, "unknown command");
		  else if (result == 0) SD.printEvent(SUCCESS, "hola.txt");
		}
	}
	return 0;
}

void WriteMenu()
{
	Serial.println("HELP\n");
	Serial.println("\tL file info\n");
	Serial.println("\tD delete\n");
	Serial.println("\tP append string\n");
	Serial.println("\tW init file and write\n");
	Serial.println("\tR dump to serial\n");
	Serial.println("\tA append text\n");
}
