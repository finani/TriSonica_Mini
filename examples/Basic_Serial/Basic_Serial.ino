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
    char* rawData = (char*)TSMini.readRawData();
    Serial.write(rawData);
    Serial.println("");
  }
}
