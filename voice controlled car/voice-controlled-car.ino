int motA_pin1 = 7;
int motA_pin2 = 6;
int motB_pin1 = 5;
int motB_pin2 = 4;
String command;  // Change to String to read full words

void setup() {
  pinMode(motA_pin1, OUTPUT);
  pinMode(motA_pin2, OUTPUT); 
  pinMode(motB_pin1, OUTPUT);
  pinMode(motB_pin2, OUTPUT);

  Serial.begin(9600);
  Serial.println("Waiting for command...");
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readString();  // Read the full string input
    command.trim();  // Remove any leading/trailing whitespace
    Serial.println(command);

    if (command.equalsIgnoreCase("forward")) {
      forward();
    } else if (command.equalsIgnoreCase("stop")) {
      s();
    } else if (command.equalsIgnoreCase("left")) {
      left();
    } else if (command.equalsIgnoreCase("right")) {
      right();
    } else if (command.equalsIgnoreCase("backward")) {
      reverse();
    } else {
      s();  // Stop if any other command is received
    }
  }
}

void forward() {
  digitalWrite(motA_pin1, HIGH);
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, HIGH);
  digitalWrite(motB_pin2, LOW);
  delay(100);  // Adjust the delay for movement duration
}

void reverse() {
  digitalWrite(motA_pin1, LOW);
  digitalWrite(motA_pin2, HIGH);
  digitalWrite(motB_pin1, LOW);
  digitalWrite(motB_pin2, HIGH);
  delay(100);  // Adjust the delay
}

void left() {
  digitalWrite(motA_pin1, LOW);  // Left motor stop
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, HIGH); // Right motor forward
  digitalWrite(motB_pin2, LOW);
  delay(100);  // Adjust the delay
}

void right() {
  digitalWrite(motA_pin1, HIGH); // Left motor forward
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, LOW);  // Right motor stop
  digitalWrite(motB_pin2, LOW);
  delay(100);  // Adjust the delay
}

void s() {
  // Stop both motors
  digitalWrite(motA_pin1, LOW);
  digitalWrite(motA_pin2, LOW);
  digitalWrite(motB_pin1, LOW);
  digitalWrite(motB_pin2, LOW);
}