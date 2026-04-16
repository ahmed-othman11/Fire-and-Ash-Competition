# Fire and Ash Competition Robot

This project contains the firmware and design assets for an autonomous and manually controlled firefighting robot. The robot is designed to navigate a track using line-following sensors and extinguish targets using an onboard water pump system.

## Features
* **Dual Mode Control**: Toggle between Autonomous (Line Follower) and Manual (Bluetooth) modes.
* **Precision Steering**: Uses a servo motor to aim the water nozzle.
* **Automated Navigation**: Three-sensor IR array for robust line detection.
* **BMS Monitoring**: Real-time battery voltage calculation.

## Hardware Configuration
![Schematic](ahmed-othman11/fire-and-ash-competition/Fire-and-Ash-Competition-612d1ebf558e5c1f5e42a9f5edb4f8e1f3d76948/Assets/Schematic.jpg)

### Component Pinout
| Component | Pin | Description |
| :--- | :--- | :--- |
| **L298N IN1/IN2** | 9, 10 | Left Motor Direction |
| **L298N IN3/IN4** | 11, 12 | Right Motor Direction |
| **ENA / ENB** | 5, 6 | Speed Control (PWM) |
| **IR Sensors** | A1, A2, A0 | Left, Center, Right Sensors |
| **Servo** | 3 | Nozzle Steering |
| **Pump** | 13 | Water Pump Relay |

## Control Commands (Manual Mode)
The robot is controlled via Serial/Bluetooth using the following keys:
* **Movement**: `9` (Forward), `2` (Backward), `4` (Left), `6` (Right), `5` (Stop).
* **Nozzle**: `W` (Up/Right), `S` (Down/Left).
* **Firefighting**: `P` (Activate Pump).
* **Modes**: `A` (Autonomous), `M` (Manual).

## Visuals
### 3D Design
![3D Model](ahmed-othman11/fire-and-ash-competition/Fire-and-Ash-Competition-612d1ebf558e5c1f5e42a9f5edb4f8e1f3d76948/Assets/3d model.jpg)

### Final Build
![Final Project](ahmed-othman11/fire-and-ash-competition/Fire-and-Ash-Competition-612d1ebf558e5c1f5e42a9f5edb4f8e1f3d76948/final project.jpeg)

## Setup Instructions
1.  Connect the components according to the `Schematic.jpg`.
2.  Open `Final_Code.ino` in the Arduino IDE.
3.  Ensure the `Servo` library is installed.
4.  Upload the code to your Arduino Uno.