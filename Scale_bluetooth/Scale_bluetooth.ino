#include <SoftwareSerial\SoftwareSerial.h>

SoftwareSerial comValue(8, 9); //  pins for scale
SoftwareSerial bluetooth(6, 7);// pins for bluetooth

String inputString = "";  // data from scale
boolean stringComplete = false; // flag of endging of message from scale
float weightValue; 
int ledPin10 = 10;
int ledPin13 = 13;
int ledPWM; 
String HC05_Response = "";
int bluetInByte;
bool initZero;

void setup()
{


	Serial.begin(57600); // assign computer's baudrate
	bluetooth.begin(9600); // bluetooth hc-05's baudrate
	comValue.begin(9600); // arduino's baudrate
	inputString.reserve(200); //reserve space for scale's data

	pinMode(ledPin10, OUTPUT);
	pinMode(ledPin13, OUTPUT);
}
void comValueEvent()
{

	while (comValue.available()) 
		//
	{
		char inChar = comValue.read(); // reading scale's message (18 byte on GS7516). Every byte rewrite inchar variable
		
		inputString += inChar;  //assemble String of inChars

		if (inChar == '\n') //detect byte with symbol of ending
		{
			stringComplete = true;  // activate flag's string ending
		}
	}

}
// getting scale's message

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








