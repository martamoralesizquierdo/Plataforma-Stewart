const int Nsensores = 6; // Número de sensores

// Definiciones de pines para los motores
const int pinMotorA[3] = {4, 2, 3}; // ENA, IN1, IN2
const int pinMotorB[3] = {7, 5, 6}; // ENB, IN3, IN4
const int pinMotorC[3] = {10, 8, 9}; // ENC, IN5, IN6
const int pinMotorD[3] = {13, 11, 12}; // END, IN7, IN8
const int pinMotorE[3] = {47, 45, 44}; // ENE, IN9, IN10
const int pinMotorF[3] = {46, 43, 42}; // ENF, IN11, IN12

const int* pinMotors[Nsensores] = {pinMotorA, pinMotorB, pinMotorC, pinMotorD, pinMotorE, pinMotorF};

const int speed = 255; // Velocidad de los motores
const float medida[Nsensores] = {22, 22, 22, 22, 22, 22}; // Medidas objetivo en cm

// Estructura para los datos de los sensores
struct datosSensor {
  float a;
  float b;
};

datosSensor sensor[Nsensores];

// Función para calcular la distancia
float distan(int pin, int muestras, struct datosSensor s) {
  long suma = 0;
  for (int i = 0; i < muestras; i++) {
    suma += analogRead(pin);
  }
  float adc = suma / muestras;
  float distancia_cm = s.a * pow(adc, s.b);
  return distancia_cm;
}

void setup() {
  Serial.begin(9600);

  // Configuración de pines de salida para los motores
  for (int i = 0; i < Nsensores; i++) {
    pinMode(pinMotors[i][0], OUTPUT); // ENx
    pinMode(pinMotors[i][1], OUTPUT); // IN1
    pinMode(pinMotors[i][2], OUTPUT); // IN2
  }

  // Inicialización de datos de sensores
  for (int i = 0; i < Nsensores; i++) {
    sensor[i].a = 17569.7;
    sensor[i].b = -1.2062;
  }

  // Empezamos desde posición 0:
  for (int i = 0; i < Nsensores; i++) {
    moveBackward(pinMotors[i], speed);
  }

  delay(1000); // Para que de tiempo a llegar abajo

  for (int i = 0; i < Nsensores; i++) {
    moveForward(pinMotors[i], speed);
  }

  delay(11000);} // 


void loop() {
   for (int i = 0; i < Nsensores; i++) {
   moveBackward(pinMotors[i],speed); }

  }


// FUNCIONES PARA CONTROLAR LOS MOTORES
void moveForward(const int* pinMotor, int speed) {
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0], speed);
}

void moveBackward(const int* pinMotor, int speed) {
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);
  analogWrite(pinMotor[0], speed);
}

void fullStop(const int* pinMotor) {
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0], 0);
}
