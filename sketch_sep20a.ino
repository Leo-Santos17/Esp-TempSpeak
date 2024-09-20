// Defina o pino onde o LED está conectado
const int ledPin = 14;  // GPIO5 (D1 no NodeMCU)

void setup() {
  // Configura o pino do LED como saída
  pinMode(ledPin, OUTPUT);
  
  // Inicializa o LED apagado
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Acende o LED
  digitalWrite(ledPin, HIGH);
  
  // Aguarda 1 segundo (1000 milissegundos)
  delay(1000);
  
  // Apaga o LED
  digitalWrite(ledPin, LOW);
  
  // Aguarda 1 segundo
  delay(1000);
}
