#include "html.h"

WiFiServer server(80);

void setup() {
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDG, OUTPUT); 
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600); 
  IMU.begin();
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(WIFISSID);
    status = WiFi.begin(WIFISSID, PASSWORD);
    delay(10000);
  }
  server.begin();
  printWifiStatus();
}

void loop() {
  WiFiClient client = server.available();
  IMU.readTemperature(temperature);
  IMU.readAcceleration(posaX, posaY, posaZ);
  IMU.readGyroscope(posgX, posgY, posgZ);
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            viewHTML(client);
            break;
          } else currentLine = "";
        } else if (c != '\r') currentLine += c;
        if (currentLine.endsWith("GET /RH")) digitalWrite(LEDR, HIGH);
        if (currentLine.endsWith("GET /RL")) digitalWrite(LEDR, LOW );              
        if (currentLine.endsWith("GET /GH")) digitalWrite(LEDG, HIGH);              
        if (currentLine.endsWith("GET /GL")) digitalWrite(LEDG, LOW );           
        if (currentLine.endsWith("GET /BH")) digitalWrite(LEDB, HIGH);              
        if (currentLine.endsWith("GET /BL")) digitalWrite(LEDB, LOW );
      }
    }
    client.stop();
    Serial.println("client disconnected");
  }
}
