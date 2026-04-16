#include <Wire.h> 
#include <Servo.h>

// Servo setup
Servo myServo;

// Motor pins (PWM Pins: 5, 6)
const int IN1 = 9;   
const int IN2 = 10;   
const int ENA = 5;   // Left motor

const int IN3 = 11;  
const int IN4 = 12;  
const int ENB = 6;   // Right motor

const int pump = 13; 
const int servo_pin = 3;

// Sensors and battery
const int ir1 = A1; // Left sensor
const int ir2 = A2; // Center sensor
const int ir3 = A0; // Right sensor
const int batteryPin = A4;

// Speed settings
const int maxSpeed = 255;
const int baseSpeed = 150;
const int slowSpeed = 75;
const int turnSpeed = 180;

char command;
bool autoMode = false;
int servoAngle = 90;

void setup() {
  Wire.begin();

  // Motor pins setup
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  pinMode(pump, OUTPUT);

  // Servo setup
  myServo.attach(servo_pin);
  myServo.write(servoAngle);
  
  Serial.begin(9600);
}

void loop() {
  // Update battery (still calculated if you want to use it later)
  updateBMS();

  // Read command
  if (Serial.available() > 0) {
    command = Serial.read();
    command = toupper(command);
  }
    
  if (command == 'A') autoMode = true;
  if (command == 'M') { 
    autoMode = false; 
    stopMotors(); 
  }
    
  if (!autoMode) {
    handleManual(command);
  }

  if (autoMode) lineFollowerLogic();
}

void updateBMS() {
  int val = analogRead(batteryPin);
  float voltage = val * (5.0 / 1023.0) * (14.7 / 4.7); 
  // You can print it on Serial if needed
  // Serial.println(voltage);
}

void handleManual(char cmd) {
  switch(cmd) {

    case 'W':
      servoAngle += 5;
      if (servoAngle > 170) servoAngle = 170;
      myServo.write(servoAngle);
      break;

    case 'S':
      servoAngle -= 5;
      if (servoAngle < 10) servoAngle = 10;
      myServo.write(servoAngle);
      break;

    case '9': moveForward(); break;
    case '2': moveBackward(); break;
    case '8': forwardRight(); break;
    case '7': forwardLeft(); break;
    case '1': backwardLeft(); break;
    case '3': backwardRight(); break;
    case '6': turnRight(); break;
    case '4': turnLeft(); break;
    case '5': stopMotors(); break;

    case 'P':
      digitalWrite(pump, HIGH);
      delay(300);
      digitalWrite(pump, LOW);
      break;
  }
}

void lineFollowerLogic() {
  int leftState = digitalRead(ir1);
  int centerState = digitalRead(ir2);
  int rightState = digitalRead(ir3);

  if (leftState == LOW && centerState == HIGH && rightState == LOW) {
    autoForward();
  }
  else if (leftState == HIGH && centerState == HIGH && rightState == LOW) {
    autoToLeft();
  }
  else if (leftState == LOW && centerState == HIGH && rightState == HIGH) {
    autoToRight();
  }  
  else if (leftState == LOW && centerState == LOW && rightState == HIGH) {
    autoTurnRight();
  }
  else if (leftState == HIGH && centerState == LOW && rightState == LOW) {
    autoTurnLeft();
  } 
  else {
    stopMotors();
  }
}

// Motor control
void moveForward() { 
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, maxSpeed); 
  analogWrite(ENB, maxSpeed); 
}

void moveBackward() { 
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
  analogWrite(ENA, maxSpeed); 
  analogWrite(ENB, maxSpeed); 
}

void forwardRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, baseSpeed); 
  analogWrite(ENB, slowSpeed); 
}

void backwardRight() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
  analogWrite(ENA, baseSpeed); 
  analogWrite(ENB, slowSpeed); 
}

void forwardLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, slowSpeed); 
  analogWrite(ENB, baseSpeed); 
}

void backwardLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
  analogWrite(ENA, slowSpeed); 
  analogWrite(ENB, baseSpeed); 
}

void turnRight() { 
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, turnSpeed); 
  analogWrite(ENB, turnSpeed); 
}

void turnLeft() { 
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, turnSpeed); 
  analogWrite(ENB, turnSpeed); 
}

void stopMotors() {  
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0); 
}

// Auto mode
void autoForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

void autoToLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, slowSpeed);
}

void autoToRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, slowSpeed);
  analogWrite(ENB, baseSpeed);
}

void autoTurnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
}

void autoTurnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
}