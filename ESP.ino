#include <ESP8266WiFi.h>
#include <ThingSpeak.h> // Bib Thingspeak

const int lm35Pin = A0; // Pin to sensor TEMP (In case, it's a LM35)
const int ledPin = D5; // Pin to LED
const float temperaturaLimite = 37.0; // Limited temper for turn on LED

const char* WIFI_NAME = "NAME"; // SSID WIFI (Name Wifi)
const char* WIFI_PASSWORD = "PASSword"; // Password WIFI

const int myChannelNumber = 2663848; // Channel ID
const char* myApiKey = "YZPDTO8NO63MF1FL"; // API WRITE KEY
const char* server = "api.thingspeak.com";

WiFiClient client;

void conectarWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Tentando conectar ao WiFi...");
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConectado ao WiFi!");
    Serial.print("IP Local: ");
    Serial.println(WiFi.localIP());
  }
}

float lerTemperatura() {
  int analogValue = analogRead(lm35Pin);
  float voltage = analogValue * (3.3 / 1024.0);
  return voltage * 100.0;
}

void controlarLed(float temperatura) {
  if (temperatura > temperaturaLimite) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Temperatura alta! LED ligado.");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Temperatura normal. LED desligado.");
  }
}

void enviarDadosThingSpeak(float temperatura) {
  ThingSpeak.setField(1, temperatura);
  int response = ThingSpeak.writeFields(myChannelNumber, myApiKey);

  if (response == 200) {
    Serial.println("Dados enviados com sucesso para o ThingSpeak!");
  } else {
    Serial.println("Erro ao enviar os dados. Código de erro: " + String(response));
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  conectarWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  conectarWiFi();
  float temperatura = lerTemperatura();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  controlarLed(temperatura);
  enviarDadosThingSpeak(temperatura);

  delay(15000);
}