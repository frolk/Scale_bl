#include <SoftwareSerial\SoftwareSerial.h>

SoftwareSerial comValue(8, 9); // определение портов
SoftwareSerial bluetooth(6, 7);// 

String inputString = "";  // 
boolean stringComplete = false; //
float weightValue;
int ledPin10 = 10;
int ledPin13 = 13;
int ledPWM; // 
String HC05_Response = "";
int bluetInByte;
bool initZero;//

void setup()
{


	Serial.begin(57600); //
	bluetooth.begin(9600); //
	comValue.begin(9600); // 
	inputString.reserve(200); //

	pinMode(ledPin10, OUTPUT);
	pinMode(ledPin13, OUTPUT);
}
void comValueEvent()
{

	while (comValue.available())
		//
	{
		char inChar = comValue.read();
		//
		inputString += inChar;

		if (inChar == '\n')
		{
			stringComplete = true;
		}
	}

}

void initiateZero()

{
	if (weightValue < 2)  //

	{
		initZero = true;
	}

	else
	{
		initZero = false;
	}

	if (!initZero) //

	{

		digitalWrite(ledPin13, HIGH);

	}

	else
	{
		digitalWrite(ledPin13, LOW);
	}


}

void pwmLed()
{


	ledPWM = map(weightValue, 0, 150, 0, 255);

	analogWrite(ledPin10, ledPWM);

}

void blueChange()
{
	char weightChar[6];
	dtostrf(weightValue, 2, 2, weightChar);
	bluetooth.println(weightChar);
	delay(500);

}



void loop()
{
	comValueEvent();
	if (stringComplete)  
	{

		inputString.remove(0, 8); 
		weightValue = inputString.toFloat();

		//Serial.println(weightValue);

		//initiateZero();

		blueChange();

		inputString = "";
		stringComplete = false;
		//delay(2000);

	}
}








