## Smart Dustbin Project Report

### Components Required
- Ultrasonic Sensor (HC-SR04) x 2
- Arduino Uno (Microcontroller)
- Servo Motor (SG90)
- Green LED
- Yellow LED
- Red LED
- Breadboard & Jumper Wires
- Power Supply (9V Battery/Adapter)

### Working Principle
Based on the distance, LEDs indicate:
- **Green LED**: Low level.
- **Yellow LED**: Medium level.
- **Red LED**: High level.

**Servo Motor**:
- Operates the lid when an object is detected.

**LED Indicators**:
- Provide a visual representation of the fill level.

### Connections
| Component                | Arduino Pin | Description                                      |
|--------------------------|-------------|--------------------------------------------------|
| Ultrasonic TRIG (Lid)    | D9          | Sends pulse to measure distance for lid.         |
| Ultrasonic ECHO (Lid)    | D10          | Receives reflected pulse for lid.                |
| Ultrasonic TRIG (Level)  | D11         | Sends pulse to measure fill level.               |
| Ultrasonic ECHO (Level)  | D12         | Receives reflected pulse for fill level.         |
| Green LED (Low Level)    | D3          | Indicates low capacity.                          |
| Yellow LED (Medium Level)| D4          | Indicates medium capacity.                       |
| Red LED (High Level)     | D5          | Indicates high capacity.                         |
| Servo Motor              | D6          | Opens and closes the lid.                        |