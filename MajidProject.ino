#include <Servo.h>
const int bluetoothTx = 10;
const int bluetoothRx = 11;
int Speed = 250;
const int motor1A = 4;
const int motor1B = 5;
const int motor2A = 6;
const int motor2B = 7;
const int enable1 = 3;
const int enable2 = 9;
const int trigPin = 13;
const int echoPin = 14;
const int servoPin = 12;
long duration;
int distance;
Servo myservo;
int servoAngle = 90;
void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  Serial.begin(9600);
  myservo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();
    switch (command) {
      case '1':
        moveForward();
        break;
      case '2':
        stopMoving();
        break;
      case '3':
        moveBackward();
        break;
      case '4':
        turnRight();
        break;
      case '5':
        turnLeft();
        break;
      case '0':
        obstacleAvoidance();
        break;
    }
  }
}
void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
}
void stopMoving() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  analogWrite(enable1, 0);
  analogWrite(enable2, 0);
}
void moveBackward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
}
void turnRight() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
}
void turnLeft() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  analogWrite(enable1, Speed);
  analogWrite(enable2, Speed);
}
void obstacleAvoidance() {
  myservo.write(180);
  delay(500);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance > 10) {
    stopMoving();
    delay(500);
    myservo.write(0);
    delay(500);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    if (distance > 10) {
      turnLeft();
      delay(1000);
      myservo.write(180);
      delay(500);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      if (distance > 10) {
        turnRight();
        myservo.write(180);
        delay(500);
        moveForward();
        while (distance < 10) {
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          duration = pulseIn(echoPin, HIGH);
          distance = duration * 0.034 / 2;
        }
        stopMoving();
        turnRight();
        delay(500);
        myservo.write(180);
        moveForward();
        delay(5000);
        stopMoving();
        turnLeft();
        delay(500);
      }
    }
  }
}
