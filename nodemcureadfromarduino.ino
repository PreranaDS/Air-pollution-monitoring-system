#include <Regexp.h>
#include<string.h>
#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

float temperature = 21.0; // Assume current temperature. Recommended to measure with DHT22
float humidity = 25.0; // Assume current humidity. Recommended to measure with DHT22
char ssid[] = "SOMEWIFI";   // your network SSID (name) 
char pass[] = "SOMEPASSWORD";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = CHANNEL_ID;
const char * myWriteAPIKey = "WRITE_API_KEY_THINGSPEAK";

void setup() {
// Open serial communications and wait for port to open:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
void loop() { // run over and over
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  Serial.println("in loop");
  if (Serial.available()) {
    Serial.println("In if");
  String recieved= Serial.readString();
  Serial.println(recieved);
  int split=recieved.indexOf(";");
  Serial.println(split);
  float mq135val = recieved.substring(0,split).toFloat();
  ThingSpeak.setField(1, mq135val);
  Serial.println("Set 1");
  float temp = recieved.substring(split+1).toFloat();
  ThingSpeak.setField(2, temp);
  Serial.println("Set 2");
  Serial.println(mq135val);
  Serial.println(temp);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  Serial.println("Sent to thingspeak");
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}
delay(20000);
}