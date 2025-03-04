#define LEFT_MOTOR_FORWARD 5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10

#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

int ir[5];
int speedLeft = 150;
int speedRight = 150;

void setup() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
}

void loop() {
  ir[0] = analogRead(IR1);
  ir[1] = analogRead(IR2);
  ir[2] = analogRead(IR3);
  ir[3] = analogRead(IR4);
  ir[4] = analogRead(IR5);

  if (ir[0] < 500 && ir[1] < 500 && ir[2] > 500 && ir[3] < 500 && ir[4] < 500) {
    moveForward();
  } else if (ir[1] > 500 && ir[2] > 500 && ir[3] < 500) {
    slightLeft();
  } else if (ir[1] < 500 && ir[2] > 500 && ir[3] > 500) {
    slightRight();
  } else if (ir[0] > 500) {
    hardLeft();
  } else if (ir[4] > 500) {
    hardRight();
  } else {
    stopMotors();
  }
}

void moveForward() {
  analogWrite(LEFT_MOTOR_FORWARD, speedLeft);
  analogWrite(RIGHT_MOTOR_FORWARD, speedRight);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}

void slightLeft() {
  analogWrite(LEFT_MOTOR_FORWARD, speedLeft / 2);
  analogWrite(RIGHT_MOTOR_FORWARD, speedRight);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}

void slightRight() {
  analogWrite(LEFT_MOTOR_FORWARD, speedLeft);
  analogWrite(RIGHT_MOTOR_FORWARD, speedRight / 2);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}

void hardLeft() {
  analogWrite(LEFT_MOTOR_FORWARD, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, speedRight);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}

void hardRight() {
  analogWrite(LEFT_MOTOR_FORWARD, speedLeft);
  analogWrite(RIGHT_MOTOR_FORWARD, 0);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_FORWARD, 0);
  analogWrite(RIGHT_MOTOR_FORWARD, 0);
  analogWrite(LEFT_MOTOR_BACKWARD, 0);
  analogWrite(RIGHT_MOTOR_BACKWARD, 0);
}
