#include <SPI.h>
#include <Arduino.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>

int status = WL_IDLE_STATUS;
int temperature;
float posgX, posgY, posgZ;
float posaX, posaY, posaZ;

void printWifiStatus();
void viewHTML(WiFiClient client);

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
