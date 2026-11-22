/*
  NEXUS — ESP32 + TB6612FNG + 2WD differential drive
  + 5-channel digital IR line sensor + HC-SR04.

  IMPORTANT:
  Confirm wiring and sensor polarity for your actual modules.
  ESP32 GPIOs are not 5V tolerant. Use level shifting where required.
  Test with wheels lifted before floor testing.
*/

#include <Arduino.h>

// TB6612FNG motor driver
const int AIN1 = 26;
const int AIN2 = 27;
const int PWMA = 25;   // Left motor PWM
const int BIN1 = 14;
const int BIN2 = 12;
const int PWMB = 33;   // Right motor PWM
const int STBY = 13;

// Five digital line sensor outputs, left to right
const int LINE_PINS[5] = {34, 35, 32, 19, 18};

// HC-SR04
const int TRIG_PIN = 5;
const int ECHO_PIN = 4; // Use voltage divider / level shifter on ECHO

// Tune after testing your exact chassis and sensors
const bool LINE_IS_LOW_ON_BLACK = true;
const int BASE_SPEED = 105;          // 0..180 initial safe range
const int MAX_SPEED = 180;
const float KP = 27.0;
const int OBSTACLE_STOP_CM = 20;
const unsigned long STATION_BAR_MS = 300;
const unsigned long LINE_LOST_TIMEOUT_MS = 700;

const int PWM_FREQ = 1000;
const int PWM_RESOLUTION = 8;

bool taskComplete = false;
unsigned long stationStart = 0;
unsigned long lineLostStart = 0;

void setMotor(int in1, int in2, int pwmPin, int speedValue) {
  int speed = constrain(abs(speedValue), 0, MAX_SPEED);
  if (speedValue > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speedValue < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  ledcWrite(pwmPin, speed);
}

void drive(int left, int right) {
  setMotor(AIN1, AIN2, PWMA, left);
  setMotor(BIN1, BIN2, PWMB, right);
}

void stopMotors() {
  drive(0, 0);
}

bool seesLine(int pin) {
  int reading = digitalRead(pin);
  return LINE_IS_LOW_ON_BLACK ? (reading == LOW) : (reading == HIGH);
}

long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (duration == 0) return 999;
  return (long)(duration * 0.0343 / 2.0);
}

float readLinePosition(bool &anyLine, bool &stationBar) {
  const int weights[5] = {-2, -1, 0, 1, 2};
  int count = 0;
  int weightedSum = 0;

  for (int i = 0; i < 5; i++) {
    if (seesLine(LINE_PINS[i])) {
      count++;
      weightedSum += weights[i];
    }
  }

  anyLine = count > 0;
  stationBar = count == 5;
  if (!anyLine) return 999.0;
  return (float)weightedSum / count;
}

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); // Enable TB6612FNG

  ledcAttach(PWMA, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PWMB, PWM_FREQ, PWM_RESOLUTION);

  for (int i = 0; i < 5; i++) pinMode(LINE_PINS[i], INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopMotors();
  Serial.println("NEXUS ready. Verify motor direction and sensor polarity.");
}

void loop() {
  if (taskComplete) {
    stopMotors();
    delay(50);
    return;
  }

  // Obstacle safety has highest priority.
  long distance = readDistanceCm();
  if (distance <= OBSTACLE_STOP_CM) {
    stopMotors();
    stationStart = 0;
    Serial.printf("Obstacle at %ld cm — stopped.\\n", distance);
    delay(80);
    return;
  }

  bool anyLine = false;
  bool stationBar = false;
  float position = readLinePosition(anyLine, stationBar);

  // A wide black bar across all sensors marks the destination.
  if (stationBar) {
    if (stationStart == 0) stationStart = millis();
    if (millis() - stationStart >= STATION_BAR_MS) {
      stopMotors();
      taskComplete = true;
      Serial.println("Station reached — task complete.");
      return;
    }
  } else {
    stationStart = 0;
  }

  // Stop safely if the route line is lost.
  if (!anyLine) {
    if (lineLostStart == 0) lineLostStart = millis();
    stopMotors();
    if (millis() - lineLostStart > LINE_LOST_TIMEOUT_MS) {
      Serial.println("Line lost — robot remains stopped.");
    }
    delay(30);
    return;
  }

  lineLostStart = 0;

  // Proportional steering for differential drive.
  int correction = (int)(KP * position);
  int leftSpeed = constrain(BASE_SPEED + correction, 0, MAX_SPEED);
  int rightSpeed = constrain(BASE_SPEED - correction, 0, MAX_SPEED);
  drive(leftSpeed, rightSpeed);

  Serial.printf("Distance=%ld cm | position=%.2f | L=%d R=%d\\n",
                distance, position, leftSpeed, rightSpeed);
  delay(10);
}
