# Air-pollution-monitoring-system
Gateways 22 hackathon..
MQ135.ino contains code that is uploaded onto the arduino/wiznet board. This reads the temperature and air pollution levels using the DHT and MQ135 sensors respectively and sends the values to the nodemcu module using software serial. This also alerts using an led and buzzer if the air pollution levels exceeds the safe threshold. The led lights up and the buzzer starts beeping or buzzing if the air pollution levels become hazardous.
nodemcureadfromarduino.ino contains code that is uploaded into the nodemcu module. This sends sends the data collected from the arduino/wiznet board to thingspeak.
