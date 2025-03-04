#include <Servo.h>

// Pin Definitions for Ultrasonic Sensors
#define TRIG_PIN_LID 9       // Ultrasonic Sensor 1 (Lid) TRIG
#define ECHO_PIN_LID 10       // Ultrasonic Sensor 1 (Lid) ECHO
#define TRIG_PIN_LEVEL 11    // Ultrasonic Sensor 2 (Level) TRIG
#define ECHO_PIN_LEVEL 12    // Ultrasonic Sensor 2 (Level) ECHO

// Pin Definitions for LEDs
#define GREEN_LED 3          // Low level indicator
#define YELLOW_LED 4         // Medium level indicator
#define RED_LED 5            // High level indicator

// Servo motor pin
#define SERVO_PIN 6

// Capacity thresholds (in cm)
#define CAPACITY_LOW 30      // Distance > 30 cm = Low level
#define CAPACITY_MEDIUM 15   // Distance between 15–30 cm = Medium level
#define CAPACITY_HIGH 10     // Distance < 15 cm = High level

// Lid detection threshold
#define LID_OPEN_DISTANCE 30 // Object detected within 20 cm
#define LID_MAX_DISTANCE 50  // Maximum valid distance for the lid sensor

// Servo motor object
Servo servo;

// Function to measure distance using an ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
  // Send a 10us pulse to TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time it takes for the pulse to return
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout for no object

  if (duration == 0) {
    // Return a high value to indicate "out of range"
    return 999;
  }

  // Convert time to distance (cm)
  int distance = duration * 0.034 / 2; // Speed of sound: 343m/s or 0.034 cm/us
  return distance;
}

// Function to update LED indicators based on the fill level
void updateLEDs(int distance) {
  if (distance > CAPACITY_LOW) {
    // Low level
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    Serial.println("Level: Low");
  } else if (distance > CAPACITY_MEDIUM) {
    // Medium level
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Serial.println("Level: Medium");
  } else if (distance <= CAPACITY_HIGH) {
    // High level
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("Level: High");
  }
}

// Function to control the servo motor for the lid
void controlLid(int distance) {
  if (distance <= LID_OPEN_DISTANCE && distance > 0 && distance <= LID_MAX_DISTANCE) {
    // Object detected near the lid
    Serial.println("Object detected. Opening lid...");
    servo.write(90);  // Open the lid
    delay(3000);      // Keep the lid open for 3 seconds
    servo.write(0);   // Close the lid
    Serial.println("Lid closed.");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Pin Modes for Ultrasonic Sensors
  pinMode(TRIG_PIN_LID, OUTPUT);
  pinMode(ECHO_PIN_LID, INPUT);
  pinMode(TRIG_PIN_LEVEL, OUTPUT);
  pinMode(ECHO_PIN_LEVEL, INPUT);

  // Pin Modes for LEDs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initialize Servo Motor
  servo.attach(SERVO_PIN);
  servo.write(0); // Start with the lid closed

  // Initial State
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("Smart Dustbin Initialized.");
}

void loop() {
  // Measure distance for lid operation
  int distanceLid = measureDistance(TRIG_PIN_LID, ECHO_PIN_LID);

  // Measure distance for level monitoring
  int distanceLevel = measureDistance(TRIG_PIN_LEVEL, ECHO_PIN_LEVEL);

  // Control the servo motor for the lid
  controlLid(distanceLid);

  // Update the LEDs based on the distance
  updateLEDs(distanceLevel);

  // Wait for a short period before the next iteration
  delay(500);
}