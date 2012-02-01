#include <WProgram.h>


void Linea(const char cLinea)
{
		int8_t z0 = cLinea & 0b00000001;
		int8_t z1 = cLinea & 0b00000010;
		int8_t z2 = cLinea & 0b00000100;
		int8_t z3 = cLinea & 0b00001000;
		int8_t z4 = cLinea & 0b00010000;
		int8_t z5 = cLinea & 0b00100000;
		int8_t z6 = cLinea & 0b01000000;
		int8_t z7 = cLinea & 0b10000000;

		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		digitalWrite(7, LOW);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);

		if(z0) digitalWrite(5, HIGH); else digitalWrite(5, LOW);
		if(z1) digitalWrite(6, HIGH); else digitalWrite(6, LOW);
		if(z2) digitalWrite(7, HIGH); else digitalWrite(7, LOW);
		if(z3) digitalWrite(8, HIGH); else digitalWrite(8, LOW);
		if(z4) digitalWrite(9, HIGH); else digitalWrite(9, LOW);
		if(z5) digitalWrite(10, HIGH); else digitalWrite(10, LOW);
		if(z6) digitalWrite(11, HIGH); else digitalWrite(11, LOW);
		if(z7) digitalWrite(12, HIGH); else digitalWrite(12, LOW);
		delay(1);

		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		digitalWrite(7, LOW);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);
		delay(1);
 }


void Carattere(char c)
{
	if(c == 'A')
	{
		Linea(0b00111111);
		Linea(0b01000100);
		Linea(0b10000100);	
		Linea(0b01000100);	
		Linea(0b00111111);	
	}
	else if(c == 'B')
	{
		Linea(0b11111111);
		Linea(0b10010001);
		Linea(0b10010001);	
		Linea(0b01101110);	
	}
	else if(c == 'C')
	{
		Linea(0b01111110);
		Linea(0b10000001);
		Linea(0b10000001);	
		Linea(0b01000010);	
	}
	else if(c == 'D')
	{
		Linea(0b11111111);
		Linea(0b10000001);
		Linea(0b01000010);	
		Linea(0b00111100);	
	}
	else if(c == 'E')
	{
		Linea(0b11111111);
		Linea(0b10010001);
		Linea(0b10010001);	
		Linea(0b10000001);	
	}
	else if(c == 'L')
	{
		Linea(0b11111111);
		Linea(0b00000001);
		Linea(0b00000001);
		Linea(0b00000001);	
	}
	else if(c == 'M')
	{
		Linea(0b11111111);
		Linea(0b01000000);
		Linea(0b00100000);
		Linea(0b01000000);	
		Linea(0b11111111);	
	}
	else if(c == 'N')
	{
		Linea(0b11111111);
		Linea(0b01000000);
		Linea(0b00100000);
		Linea(0b11111111);	
	}
	else if(c == 'O')
	{
		Linea(0b00111100);
		Linea(0b01000010);
		Linea(0b10000001);
		Linea(0b01000010);	
		Linea(0b00111100);	
	}
	else if(c == 'P')
	{
		Linea(0b11111111);
		Linea(0b10001000);
		Linea(0b10010000);
		Linea(0b01100000);	
	}
	else if(c == 'U')
	{
		Linea(0b11111100);
		Linea(0b00000010);
		Linea(0b00000001);
		Linea(0b00000010);	
		Linea(0b11111100);	
	}
	else if(c == ' ')
	{
		Linea(0b00000000);
		Linea(0b00000000);
		Linea(0b00011000);
		Linea(0b00000000);	
		Linea(0b00000000);	
	}
	else
	{
		Linea(0b10000001);	
		Linea(0b10000010);	
		Linea(0b01000100);	
		Linea(0b00101000);	
		Linea(0b00010000);	
		Linea(0b00101000);	
		Linea(0b01000100);
		Linea(0b10000010);
		Linea(0b10000001);
	}
}

void Start()
{
	Linea(0b00000001);	
	delay(50);
	Linea(0b00000010);	
	delay(50);
	Linea(0b00000100);	
	delay(50);
	Linea(0b00001000);	
	delay(50);
	Linea(0b00010000);	
	delay(50);
	Linea(0b00100000);	
	delay(50);
	Linea(0b01000000);	
	delay(50);
	Linea(0b10000000);	
	delay(50);
	Linea(0b01000000);	
	delay(50);
	Linea(0b00100000);	
	delay(50);
	Linea(0b00010000);	
	delay(50);
	Linea(0b00001000);	
	delay(50);
	Linea(0b00000100);	
	delay(50);
	Linea(0b00000010);	
	delay(50);
	Linea(0b00000001);	
	delay(50);
	Linea(0b00000010);	
	delay(50);
	Linea(0b00000100);	
	delay(50);
	Linea(0b00001000);	
	delay(50);
	Linea(0b00010000);	
	delay(50);
	Linea(0b00100000);	
	delay(50);
	Linea(0b01000000);	
	delay(50);
	Linea(0b10000000);	
	delay(50);
	Linea(0b01000000);	
	delay(50);
	Linea(0b00100000);	
	delay(50);
	Linea(0b00010000);	
	delay(50);
	Linea(0b00001000);	
	delay(50);
	Linea(0b00000100);	
	delay(50);
	Linea(0b00000010);	
	delay(50);
	Linea(0b00000001);	
	delay(50);
}


int main(void)
{
	int nCall = 0;
	init();

	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(0, INPUT);
	pinMode(1, INPUT);
	pinMode(2, INPUT);

	delay(100);
	Start();

	while (true)
	{
		if(digitalRead(0) == 0) 
		{
			Carattere('B');
			Carattere('U');
			Carattere('O');
			Carattere('N');
			Carattere(' ');
			Carattere('C');
			Carattere('O');
			Carattere('M');
			Carattere('P');
			Carattere('L');
			Carattere('E');
			Carattere('N');
			Carattere('N');
			Carattere('O');
			delay(400);
		}

		if(digitalRead(1) == 0)
		{
			Carattere('B');
			Carattere('U');
			Carattere('O');
			Carattere('N');
			delay(400);
		}

		if(digitalRead(2) == 0)
		{
			Carattere('C');
			Carattere('O');
			Carattere('M');
			Carattere('P');
			Carattere('L');
			Carattere('E');
			Carattere('N');
			Carattere('N');
			Carattere('O');
			delay(400);
		}

	}
	return 0;
}






