// PINES PARA SENSOR ULTRASONIDO
const int pinTrigger = 3;
const int pinEcho = 2;

// PINES PARA MOTORES
// motor A
const int pinENA = 6;    //D6 PMW
const int pinIN1 = 7;
const int pinIN2 = 8;
// motor B
const int pinIN3 = 9;
const int pinIN4 = 10;
const int pinENB = 11;   //D11 PMW
const int pinMotorA[3] = { pinENA, pinIN1, pinIN2 };
const int pinMotorB[3] = { pinENB, pinIN3, pinIN4 };

//Variables
bool enemyDet;  // si esta detectando enemigo

const int STATE_SEARCH = 1;
const int STATE_ATTACK = 2;
const int STATE_AVOID = 3;
int state;

void readSensor(){
  // Generar un pulso de 10 microsegundos en el pin Trigger
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Medir la duración del pulso recibido en el pin Echo
  long rcvTime = pulseIn(pinEcho, HIGH);

  // Calcular distancia en cm (sonido va a 343 m/s)
  float distanciaCm = rcvTime * 0.0343 / 2;
  if (distanciaCm < 50) {
    enemyDet = true;
  }else {
    enemyDet = false;
  }
}

void setup() {
  // Setup del sensor ultrasonido
  Serial.begin(9600);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);

  // Configuración de pines como salida
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Despues de activar, entrar en estaddo de searching
  trunRandom_enter(STATE_SEARCHING);
}

void loop() {
  readSensor();
  if(state ==STATE_SEARCHING){

  }
}

void moveForward(const int pinMotor[3], int speed){
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
 
  analogWrite(pinMotor[0], speed);
}

void moveBackward(const int pinMotor[3], int speed){
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);

  analogWrite(pinMotor[0], speed);
}

void stopMove(const int pinMotor[3]){
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);

  analogWrite(pinMotor[0], 0);
}