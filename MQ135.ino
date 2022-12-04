#include <MQ135.h>
#include <SoftwareSerial.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
+
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"
/*  MQ135 gas sensor
    Datasheet can be found here: https://www.olimex.com/Products/Components/Sensors/SNS-MQ135/resources/SNS-MQ135.pdf

    Application
    They are used in air quality control equipments for buildings/offices, are suitable for detecting of NH3, NOx, alcohol, Benzene, smoke, CO2, etc

    Original creator of this library: https://github.com/GeorgK/MQ135
*/

#define PIN_MQ135 A0

//Command format is SoftwareSerial(rxPin, txPin, inverse_logic, buffer size);
SoftwareSerial arduinosend(11,10);
MQ135 mq135_sensor(PIN_MQ135);
Talkie voice;
float temp = 21.0; // Assume current temperature. Recommended to measure with DHT22
float humidity = 25.0; // Assume current humidity. Recommended to measure with DHT22

void setup() {
  Serial.begin(115200);
  arduinosend.begin(115200);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH); 
}

void loop() {
  voice.say(sp2_ALERT);
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temp, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temp, humidity);
  int tempsensorvalue = analogRead(A1);
  Serial.println(correctedPPM);
    if(correctedPPM>400000){
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
  arduinosend.print(correctedPPM);
  arduinosend.print(";");
  arduinosend.print(tempsensorvalue);
  arduinosend.println();
  delay(30000);
}
