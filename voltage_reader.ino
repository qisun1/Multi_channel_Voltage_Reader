#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
float calibation = 0.979228;
float factor = (5.0 / 1023.0) * calibation;
const uint8_t pinCount = 8;
const uint8_t apins[pinCount]= {A0, A1, A2, A3, A4, A5, A6, A7};
const String apinNames[pinCount] = { "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7"};
const uint8_t maxCol = 2;
const uint8_t maxRow = 4;
const uint8_t colSpace = 12;
const uint8_t sampleTimes = 4;

//interrupt pin to trigger sending data to serial port
uint8_t interruptPin = 2;
unsigned long lastTrigger;

void setup() {

  Serial.begin(9600);
  
// print header line
  for (uint8_t i = 0; i < pinCount; i++)
  {
	  Serial.print(apinNames[i]);
	  Serial.print("\t");
  }
  Serial.println("");

  lcd.setBacklight((uint8_t)1);
  lcd.init();

  //pull down the interrupt pin to send data to serial
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISR0, FALLING);

}

void loop() {
	uint8_t col = 0;
	uint8_t row = 0;
	for (uint8_t i = 0; i < pinCount; i++)
	{
		print_voltage(apinNames[i], apins[i], row, col*colSpace);
		row++;
		if (row >= maxRow)
		{
			row = 0;
			col++;
			if (col >= maxCol)
			{
				col = 0;
			}
		}
	}
  delay(1000);
}

void print_voltage (String name, int analogpin, int row, int col)
{
  int sensorValue = analogRead(analogpin);     // read the input pin
  float voltage = sensorValue * factor;
  lcd.setCursor(col, row);
  lcd.print(name);
  lcd.print(": ");
  lcd.print(voltage);
}


void ISR0 () 
{
	if ((millis() - lastTrigger) > 1000)
	{
		uint16_t recordings[pinCount];
		for (uint8_t i = 0; i < pinCount; i++)
		{
			recordings[i] =0;
		}

		for (uint8_t iter =0; iter < sampleTimes; iter++)
		{
			for (uint8_t i = 0; i < pinCount; i++)
			{
				recordings[i] += analogRead(apins[i]);
			}
			delay(10);
		}

		for (uint8_t i = 0; i < pinCount; i++)
		{
			float voltage = float(recordings[i])/ sampleTimes * factor;
			Serial.print(voltage);
			Serial.print("\t");
		}


		Serial.println();
		lastTrigger = millis();
	}


}
