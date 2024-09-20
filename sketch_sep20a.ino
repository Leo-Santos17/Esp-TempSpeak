#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Defina o pino onde o LED está conectado
const int ledPin = 14;  // GPIO5 (D1 no NodeMCU)
float temp=0;
int analog= 0;
void setup() {
  // Configura o pino do LED como saída
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
}

void loop() {
  // Analog
  analog= analogRead(17);
  temp = analog*0.48828125;
  
  Serial.print("Temp: ");
  Serial.print(temp);
  
  // Aguarda 1 segundo
  delay(1000);
}