// Define o pino do sensor LM35
const int lm35Pin = A0; // Pino analógico do NodeMCU

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  Serial.print("VAI TOMAR NO CU");
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
  
  // Aguarda 1 segundo antes de ler novamente
  delay(1000);
}
