#include <Servo.h> // Include Servo library 
// Define pin connections for the ultrasonic sensor 
#define TRIG_PIN 12 
#define ECHO_PIN 11 
// Define pin for the buzzer and optional LED 
#define BUZZER_PIN 13 
#define LED_PIN 10 
// Threshold distance (in cm) for triggering the alarm 
#define THRESHOLD 30 
// Variable to store the distance 
f
 loat distance; 
// Servo motor control 
#define SERVO_PIN 9 // Servo connected to pin 9 
Servo servoMotor; 
// Angle for the servo 
int servoAngle = 50; // Starting angle set to 50 
void setup() { 
// Set pin modes 
pinMode(TRIG_PIN, OUTPUT); 
pinMode(ECHO_PIN, INPUT); 
pinMode(BUZZER_PIN, OUTPUT); 
pinMode(LED_PIN, OUTPUT); 
// Attach servo motor 
servoMotor.attach(SERVO_PIN); 
// Initialize Serial Monitor 
Serial.begin(9600); 
Serial.println("Anti-Theft Alarm System with Servo Scanning Initialized..."); 
// Move servo to the initial position 
servoMotor.write(servoAngle); 
} 
void loop() { 
// Rotate servo and measure distance 
for (servoAngle = 50; servoAngle <= 130; servoAngle += 5) { // Rotate from 50° to 130° 
servoMotor.write(servoAngle);   // Set servo angle 
delay(300);                     
// Give servo time to move 
distance = measureDistance();   // Measure the current distance 
// Print the distance and angle to Serial Monitor 
Serial.print("Angle: "); 
Serial.print(servoAngle); 
Serial.print("°, Distance: "); 
    Serial.print(distance); 
    Serial.println(" cm"); 
 
    // Check if the distance falls below the threshold 
    if (distance < THRESHOLD) { 
      activateAlarm(); // Trigger the alarm 
      Serial.println("Object Detected! Servo Stopped."); 
      delay(2000);      // Wait for 2 seconds 
      deactivateAlarm(); 
    } 
  } 
 
  // Sweep back the servo in the opposite direction 
  for (servoAngle = 130; servoAngle >= 50; servoAngle -= 5) { // Rotate back from 130° to 50° 
    servoMotor.write(servoAngle);   // Set servo angle 
    delay(300);                     // Give servo time to move 
    distance = measureDistance();   // Measure the current distance 
 
    // Print the distance and angle to Serial Monitor 
    Serial.print("Angle: "); 
    Serial.print(servoAngle); 
    Serial.print("°, Distance: "); 
    Serial.print(distance); 
    Serial.println(" cm"); 
 
    // Check if the distance falls below the threshold 
    if (distance < THRESHOLD) { 
      activateAlarm(); // Trigger the alarm 
      Serial.println("Object Detected! Servo Stopped."); 
      delay(2000);      // Wait for 2 seconds 
      deactivateAlarm(); 
    } 
  } 
} 
 
// Function to measure distance using the ultrasonic sensor 
float measureDistance() { 
  long duration; 
  float distanceCm; 
 
  // Send a 10-microsecond pulse to trigger the sensor 
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW); 
 
  // Read the echo pulse duration 
  duration = pulseIn(ECHO_PIN, HIGH); 
 
  // Calculate the distance in cm 
  distanceCm = (duration * 0.034) / 2; 
return distanceCm; 
} 
// Function to activate the alarm 
void activateAlarm() { 
digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer 
digitalWrite(LED_PIN, HIGH);   // Turn on the LED 
} 
// Function to deactivate the alarm 
void deactivateAlarm() { 
digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer 
digitalWrite(LED_PIN, LOW);   // Turn off the LED 
} 