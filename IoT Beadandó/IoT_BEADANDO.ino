//************  Kulcsár László Attila  TWT9LN  ******************

#include <OneWire.h>
#include <DallasTemperature.h>


 
const int relayPin = 2;
#define ONE_WIRE_BUS 4                                 // A csőben lévő hőmérséklet szenzora
OneWire oneWire1(ONE_WIRE_BUS);
DallasTemperature tempSensor1(&oneWire1);
#define ONE_WIRE_BUS 5                                 // A műhelyben lévő hőmérséklet szenzora
OneWire oneWire2(ONE_WIRE_BUS);
DallasTemperature tempSensor2(&oneWire2);

void setup() {

  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);  
  tempSensor1.begin();
  tempSensor2.begin();

}

void loop() {
  tempSensor1.requestTemperatures();
  tempSensor2.requestTemperatures();

  float temp1 = tempSensor1.getTempCByIndex(0);
  float temp2 = tempSensor2.getTempCByIndex(0);

  /* 5 másodpercenkét ellenőrzi a műhely és a fűtőcsőben lévő levegő hőmérsékletét
   és ennek megfelelően kapcsolja a relé be vagy ki a ventillátort  */

if (temp1 > temp2 + 2) {
    digitalWrite(relayPin, HIGH);
  }
  if (temp2 > 25) {
    digitalWrite(relayPin, LOW);
  }
  delay(5000);

  //5 másodpercenént kiírja a Serial Monitor-ra a a műhely és a cső hőmérsékletét a kalibrálásához.

  Serial.print("Hőmérséklet szenzor 1: "); 
  Serial.print(temp1-4);                       // kalibrálás: módosítva a mért érték - 4 °C-al
  Serial.println(" Celsius");
  

  Serial.print("Hőmérséklet szenzor 2: "); 
  Serial.print(temp2-3);                      // kalibrálás: módosítva a mért érték - 3 °C-al
  Serial.println(" Celsius");

  Serial.println("************************************");
  
  delay(5000);

 
}
