#include <Arduino.h>
#include "stewart_kinematics.h"

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
float medida[Nsensores]; // Medidas objetivo en cm, calculadas más adelante
const float tolerancia = 2.0; // Tolerancia en cm
const int iteracionesParaDetener = 5; // Número de iteraciones necesarias dentro de la tolerancia para detener el motor

// Estructura para los datos de los sensores
struct datosSensor {
  float a;
  float b;
};

datosSensor sensor[Nsensores];

// Contadores para el número de iteraciones dentro de la tolerancia
int contadorDentroTolerancia[Nsensores] = {0, 0, 0, 0, 0, 0};

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

  // Inicializar posiciones objetivo y calcular longitudes objetivo de los actuadores
  float B[3][6], P[3][6];
  define_anchor_points(B, P, 23.0, 23.0, 30.0);

  float x = 0, y = 0, z = 0; // Posición objetivo
  float roll = 0, pitch = 0, yaw = 0; // Orientación objetivo

  stewart_inverse_kinematics(medida, x, y, z, roll, pitch, yaw, B, P);

  // Imprimir longitudes objetivo
  Serial.println("Longitudes objetivo de los actuadores:");
  for (int i = 0; i < Nsensores; i++) {
    Serial.print("Actuador ");
    Serial.print(char('A' + i));
    Serial.print(": ");
    Serial.print(medida[i]);
    Serial.println(" cm");
  }

  // Empezamos desde posición 0:
  for (int i = 0; i < Nsensores; i++) {
    moveBackward(pinMotors[i], speed);
  }

  delay(10000); // Para que de tiempo a llegar abajo

  for (int i = 0; i < Nsensores; i++) {
    moveForward(pinMotors[i], speed);
  }

  delay(1000); // Ajustar el tiempo según sea necesario
}

void loop() {
  // Control de distancia para cada actuador
  for (int i = 0; i < Nsensores; i++) {
    float D_cm = distan(A0 + i, 50, sensor[i]);
    Serial.print("Distancia motor ");
    Serial.print(char('A' + i));
    Serial.print(": ");
    Serial.print(D_cm);
    Serial.println(" cm");

    // Control del motor basado en la distancia medida
    if (abs(D_cm - medida[i]) <= tolerancia) {
      contadorDentroTolerancia[i]++;
    } else {
      contadorDentroTolerancia[i] = 0;
      if (D_cm > medida[i]) {
        moveBackward(pinMotors[i], speed);
      } else if (D_cm < medida[i]) {
        moveForward(pinMotors[i], speed);
      }
    }

    // Si el contador ha alcanzado el número de iteraciones para detener
    if (contadorDentroTolerancia[i] >= iteracionesParaDetener) {
      fullStop(pinMotors[i]);
    }
  }
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
