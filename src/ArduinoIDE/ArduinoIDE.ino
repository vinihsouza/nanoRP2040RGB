#include <SPI.h>
#include <Arduino.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>

int status = WL_IDLE_STATUS;
int temperature;
float posgX, posgY, posgZ;
float posaX, posaY, posaZ;
char ssid[] = "MinhaRede";
char pass[] = "Fit@2022";

WiFiServer server(80);

void setup() {
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDG, OUTPUT); 
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600); 
  IMU.begin();
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
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
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<style>");
            client.print(".container {margin: 0 auto; text-align: center; margin-top: 100px;}");
            client.print("button {color: white; width: 100px; height: 100px;");
            client.print("border-radius: 50%; margin: 20px; border: none; font-size: 20px; outline: none; transition: all 0.2s;}");
            client.print(".red{background-color: rgb(196, 39, 39);}");
            client.print(".green{background-color: rgb(39, 121, 39);}");
            client.print(".blue {background-color: rgb(5, 87, 180);}");
            client.print(".off{background-color: grey;}");
            client.print("button:hover{cursor: pointer; opacity: 0.7;}");
            client.print("</style>");
            client.print("<div class='container'>");
            client.print("<button class='red' type='submit' onmousedown='location.href=\"/RH\"'>ON</button>");
            client.print("<button class='off' type='submit' onmousedown='location.href=\"/RL\"'>OFF</button><br>");
            client.print("<button class='green' type='submit' onmousedown='location.href=\"/GH\"'>ON</button>");
            client.print("<button class='off' type='submit' onmousedown='location.href=\"/GL\"'>OFF</button><br>");
            client.print("<button class='blue' type='submit' onmousedown='location.href=\"/BH\"'>ON</button>");
            client.print("<button class='off' type='submit' onmousedown='location.href=\"/BL\"'>OFF</button>");
            client.println();
            client.print("</div>");
            client.println();
            client.print("<div class='container'>");
            client.print("Temperatura: ");
            client.print(temperature);
            client.print(" C ");
            client.println();
            client.print("</div>");
            client.println();
            client.print("<div class='container'>");
            client.println("Acelerometro: ");
            client.print("X: "); client.print(posaX); client.print("  ");
            client.print("Y: "); client.print(posaY); client.print("  ");
            client.print("Z: "); client.print(posaZ); client.print("  ");
            client.print("</div>");
            client.println();
            client.print("<div class='container'>");
            client.println("Giroscopio: ");
            client.print("X: "); client.print(posgX); client.print("  ");
            client.print("Y: "); client.print(posgY); client.print("  ");
            client.print("Z: "); client.print(posgZ); client.print("  ");
            client.print("</div>");
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

void printWifiStatus() {
  Serial.print("SSID: "); 
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: "); 
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): "); 
  Serial.print(rssi); 
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://"); 
  Serial.println(ip);
}
