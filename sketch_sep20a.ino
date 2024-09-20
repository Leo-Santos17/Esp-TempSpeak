#include "ThingSpeak.h"
#include <WiFi.h>

// Define o pino do sensor LM35
const int lm35Pin = A0; // Pino analógico do NodeMCU
const char* WIFI_PASSWORD = "81936160rr";
const int myChannelNumber = 2663848 ;
const char* myApiKey = "YZPDTO8NO63MF1FL";
const char* server = "api.thingspeak.com";

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial.print("VAI TOMAR NO CU");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Wifi not connected");
  }
  Serial.println("Wifi connected !");
  Serial.println("Local IP: " + String(WiFi.localIP()));
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
}

void loop() {
  // Lê o valor analógico do sensor LM35
  int analogValue = analogRead(lm35Pin);
  
  // Converte o valor analógico para tensão (ESP8266 usa resolução de 10 bits)
  float voltage = analogValue * (3.3 / 1024.0); // 3.3V é a referência
  
  // Converte a tensão para temperatura em graus Celsius
  float temperatureC = voltage * 100.0;
  
  // Exibe a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  // ThingSpeak
  ThingSpeak.setField(1,temperatureC);
  int x = ThingSpeak.writeFields(myChannelNumber,myApiKey);

  // Erro
  if(x == 200){
    Serial.println("Data pushed successfull");
  }else{
    Serial.println("Push error" + String(x));
  }

  // Aguarda 1 segundo antes de ler novamente
  delay(1000);

  
}
