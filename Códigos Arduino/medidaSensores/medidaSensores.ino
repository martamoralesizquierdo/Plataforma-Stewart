void setup() {
  // Comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Definir los pines de los sensores
  int sensores[] = {A0, A1, A2, A3, A4, A5};
  int num_sensores = sizeof(sensores) / sizeof(sensores[0]);

  for (int i = 0; i < num_sensores; i++) {
    float distancia_cm = distancia(sensores[i], 20);
    Serial.print("Distancia en A");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(distancia_cm);
    Serial.println(" cm");
    delay(500); // Agregar un pequeño retraso para la estabilidad de la lectura
  }
}

float distancia(int pin, int n) {
  long suma = 0;
  for (int i = 0; i < n; i++) {
    suma += analogRead(pin);
  }
  float adc = suma / n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return distancia_cm;
}
