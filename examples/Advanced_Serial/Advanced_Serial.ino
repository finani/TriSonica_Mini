#include "TSM.h"

TSM TSMini(Serial6);

void setup() {
  int status;

  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with TSMini
  status = TSMini.begin(115200);
  if (status < 0) {
    Serial.println("TriSonica Mini initialization unsuccessful");
    Serial.println("Check TriSonica Mini wiring");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
}

void loop() {
  if (TSMini.available()) {
    TSMData tsmData;
//    TSMini.readData(tsmData);
    tsmData = TSMini.readData();

    Serial.println("");
    Serial.print("WindSpeed3D: "); Serial.println(tsmData.windSpeed3D);
    Serial.print("WindSpeed2D: "); Serial.println(tsmData.windSpeed2D);
    Serial.print("WindDirHor: "); Serial.println(tsmData.windDirHor);
    Serial.print("WindDirVer: "); Serial.println(tsmData.windDirVer);
    Serial.print("SonicTemp: "); Serial.println(tsmData.sonicTemp);
    Serial.print("Humidity: "); Serial.println(tsmData.humidity);
    Serial.print("Pressure: "); Serial.println(tsmData.pressure);
    Serial.print("AirDensity: "); Serial.println(tsmData.airDensity, 7);
    Serial.print("Pitch: "); Serial.println(tsmData.pitch);
    Serial.print("Roll: "); Serial.println(tsmData.roll);
  }
}
