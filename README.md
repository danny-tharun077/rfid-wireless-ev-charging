
# RFID-Based Wireless EV Charging System

A hardware prototype integrating RFID-based access
authentication with wireless power transfer for EV charging.

## Project Overview

This project demonstrates a wireless charging system in
which RFID identification is used to authorize charging.
A microcontroller processes the RFID data and controls
the charging system according to the implemented logic.

The prototype combines embedded programming, RFID
technology, and wireless power transfer.

## Objectives

- Implement RFID-based user or vehicle identification.
- Enable or disable charging based on authorization.
- Demonstrate contactless power transfer using coupled coils.
- Integrate hardware and embedded control.
- Evaluate the prototype through practical testing.

## Key Features

- RFID tag scanning and identification
- Authorized and unauthorized access handling
- Microcontroller-based charging control
- Wireless power transfer
- Hardware prototype and experimental validation

## System Architecture
<img width="1317" height="968" alt="image" src="https://github.com/user-attachments/assets/d0d9be74-d9bd-494f-bd0b-3549798865a2" />


## Hardware Components

1. ACS712 Current Sensor
2. 2-Channel Relay Module
3. IR Sensor
4. MFRC522 RFID Reader
5. I2C LCD Display
6. Servo Motor
7. Buzzer
8. 12V Power Supply
9. Arduino
10. Breadboard
11. Transmitter/Receiver Coil

## Hardware Connections

| S.No | Component | Pin | Connection |
|---|---|---|---|
| 1 | ACS712 Current Sensor | VCC | Arduino 5V |
|  |  | GND | Arduino GND |
|  |  | OUT | Arduino A0 |
|  |  | Terminal Block 1 | 12V Positive (+) |
|  |  | Terminal Block 2 | Relay COM |
| 2 | 2-Channel Relay Module | VCC | Arduino 5V |
|  |  | GND | Arduino GND |
|  |  | IN1 | Arduino Digital Pin 8 |
|  |  | IN2 | Arduino Digital Pin 7 |
|  |  | Channel 1 NO | Transmitter Coil 1 (Slot 1) |
|  |  | Channel 2 NO | Transmitter Coil 2 (Slot 2) |
| 3 | IR Sensors | Entrance OUT | Arduino Digital Pin 2 |
|  |  | Slot 1 OUT | Arduino Digital Pin 3 |
|  |  | Slot 2 OUT | Arduino Digital Pin 4 |
|  |  | VCC (All Sensors) | Arduino 5V |
|  |  | GND (All Sensors) | Arduino GND |
| 4 | MFRC522 RFID Reader | VCC | Arduino 3.3V |
|  |  | GND | Arduino GND |
|  |  | RST | Arduino Digital Pin 5 |
|  |  | MISO | Arduino Digital Pin 12 |
|  |  | MOSI | Arduino Digital Pin 11 |
|  |  | SCK | Arduino Digital Pin 13 |
|  |  | SDA / SS | Arduino Digital Pin 10 |
| 5 | I2C LCD Display | VCC | Arduino 5V |
|  |  | GND | Arduino GND |
|  |  | SDA | Arduino A4 |
|  |  | SCL | Arduino A5 |
| 6 | Servo Motor | Brown Wire | GND |
|  |  | Orange/Red Wire | 5V |
|  |  | Yellow/White Wire | Arduino Digital Pin 9 |
| 7 | Transmitter Coils | Slot 1 Positive Wire | Relay Channel 1 NO |
|  |  | Slot 1 Negative Wire | GND |
|  |  | Slot 2 Positive Wire | Relay Channel 2 NO |
|  |  | Slot 2 Negative Wire | GND |
| 8 | Buzzer | Positive (+) | Arduino Digital Pin 6 |
|  |  | Negative (-) | Arduino GND |

## Power Supply Connections

| S.No | Connection | Description |
|---|---|---|
| 1 | 12V Power Supply | Positive and negative terminals connected to the power rails |
| 2 | Arduino 5V Supply | Connect Arduino 5V and GND to the logic power rails |
| 3 | Common Ground | Connect the supply ground and Arduino ground |
| 4 | Relay COM Terminals | Connect to the positive supply as required by the circuit |




## Software and Tools

- Embedded C / Arduino C++ (as applicable)
- Arduino IDE

## Working Principle

1. The RFID reader scans the presented tag.
2. The controller processes the tag identification.
3. The system checks whether charging is authorized.
4. The charging control enables or disables power transfer.
5. The receiver obtains power through magnetic coupling.
6. The prototype's output and operating behavior are evaluated.

## Flowchart
<img width="668" height="951" alt="image" src="https://github.com/user-attachments/assets/4e470e69-4d64-4bd6-a5a2-0e7660a9b03e" />


## Challenges and Limitations

1. Ambient light blindness:
As a vehicle approached the infrared proximity sensors, the
mechanical motion caused the sensor signal to rapidly flicker
between HIGH and LOW states for a few milliseconds, confusing
the microcontroller into registering multiple fake vehicle arrivals.
2. Inductive coil misalignment
The power transfer efficiency of the contactless inductive charging
pads dropped off sharply if the vehicle's receiver coil was not
perfectly centered over the station's primary transmitter coil. Even a
2-centimeter misalignment caused an unacceptable drop in current
output.
3. Multi-device ground loop noise injection
Connecting several distinct sub-systems (SPI reader, I2C screen,
PWM servo, and current loops) created small voltage differences
across their ground paths. This introduced ground loop noise that
corrupted weak analog sensor readings.

## Conclusion

This Project results show that the Arduino Uno successfully
coordinates all parts of the wireless EV charging system in the expected sequence.
When a vehicle is detected by the infrared sensors, the RFID reader verifies the
user, and only after successful authentication does the system activate the servo
gate, buzzer, and the selected transmitter coil. The current sensors continuously
monitor the charging current from each coil, while the LCD provides real-time
status updates such as slot availability, RFID approval, and charging operation.



## Future Scope

- Improved RFID authentication security
- Charging efficiency optimization
- Coil alignment improvement
- Enhanced monitoring and fault protection
- Integration with suitable battery-management systems

## Repository Structure

- `docs/` - Project documentation
- `hardware/` - Circuit diagrams and component details
- `srccode/` - Controller source code
- `images/` - Hardware photographs
