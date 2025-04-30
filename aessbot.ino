// Sensor IR
#include <IRremote.h>
const int RECV_PIN = !!!!!!!!!!!!!!!!!!!!!!!!!!!!!;
IRrecv irrecv(RECV_PIN);
decode_results results;
bool activado = false;

// === DEFINICIÓN DE PINES ===
// Sensor ultrasónico
const int pinTrigger = 3;
const int pinEcho = 2;

// Sensor de linea
const int SR = !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;
const int SL = !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!;

// Motor A
const int pinENA = 6;  // PWM
const int pinIN1 = 7;
const int pinIN2 = 8;

// Motor B
const int pinIN3 = 9;
const int pinIN4 = 10;
const int pinENB = 11;  // PWM

const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };

// === VARIABLES DE ESTADO ===
bool detected = false;    // objetivo detectado por ultrasonido
unsigned long begin = 0;  // tiempo de inicio del estado actual

// Estados de la máquina
const int STATE_SEARCH = 1;
const int STATE_ATTACK = 2;
const int STATE_AVOID = 3;
int state = STATE_SEARCH;

// === FUNCIONES ===

// Lectura de sensor ultrasónico
void readSensor() {
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  long rcvTime = pulseIn(pinEcho, HIGH);  // tiempo del eco
  float distanciaCm = rcvTime * 0.0343 / 2;

  detected = (distanciaCm > 0 && distanciaCm < 50);  // evitar falsos positivos
}

// Control de motores
void moveForward(const int pinMotor[3], int speed) {
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0], speed);
}

void moveBackward(const int pinMotor[3], int speed) {
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);
  analogWrite(pinMotor[0], speed);
}

void stopMove(const int pinMotor[3]) {
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0], 0);
}

// Cambio de estado
void enter(int newState) {
  state = newState;
  begin = millis();
}

// Estado: Giro aleatorio
void turnRandom_enter(int newState) {
  bool clockwise = random(0, 2);  // sentido aleatorio

  if (clockwise) {
    moveForward(pinMotorA, 120);
    moveBackward(pinMotorB, 120);
  } else {
    moveBackward(pinMotorA, 120);
    moveForward(pinMotorB, 120);
  }
  enter(newState);
}

// Estado: Avanzar hacia el objetivo
void forward_enter(int newState) {
  moveForward(pinMotorA, 200);
  moveForward(pinMotorB, 200);
  enter(newState);
}

// Estado: Retroceder (por ejemplo, para evitar bordes o esquivar)
void backward_enter(int newState) {
  moveBackward(pinMotorA, 150);
  moveBackward(pinMotorB, 150);
  enter(newState);
}

// Comprobación de timeout de estado
bool state_timeout(unsigned long ms) {
  return millis() - begin > ms;
}

// === SETUP ===
void setup() {
  Serial.begin(9600);
  // Pines de sensor IR
  irrecv.enableIRIn();

  // Pines del sensor ultrasónico
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  // Pines de motores
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  randomSeed(analogRead(0));  // mejor aleatoriedad

  turnRandom_enter(STATE_SEARCH);
}

// === LOOP PRINCIPAL ===
void loop() {
  if (!activado) {
    if (irrecv.decode(&results)) {
      activado = true;
      irrecv.resume();
    }
  } else {
    readSensor();
    switch (state) {
      case STATE_SEARCH:
        if (detected) {
          forward_enter(STATE_ATTACK);
        } else if (state_timeout(2000)) {
          turnRandom_enter(STATE_SEARCH);
        }
        break;

      case STATE_ATTACK:
        if (!detected) {
          turnRandom_enter(STATE_SEARCH);
        }
        break;

      default:  // Cualquier estado desconocido: volver a buscar
        if (state_timeout(500)) {
          turnRandom_enter(STATE_SEARCH);
        }
        break;
    }
  }
}
