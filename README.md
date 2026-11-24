# CaveCar

**Team:** Serial Byters

**Version:** 1.0.1

**Authors:** Surya K

---

## Overview

CaveCar is a small Arduino-based robotic platform designed to explore and map low-ceiling environments (for example, caves or tunnels). The vehicle uses a pair of DC motors for locomotion, an ultrasonic sensor to measure ceiling distance, an IR sensor for obstacle detection, and a servo-mounted ultrasonic sensor to sweep and profile the cave ceiling.

This repository contains the primary control sketch for the CaveCar platform.

---

## Features

* Forward/backward and turning control for a differential-drive vehicle.
* IR-based immediate obstacle detection and avoidance (turns right when obstacle detected).
* Ultrasonic distance measurement to map the cave ceiling.
* Servo sweep (steps of 18°) to build a simple ASCII-based cave ceiling profile printed over Serial.

---

## Hardware

### Required Components

* Arduino (Uno, Nano or compatible)
* 2 × DC motors with an H-bridge motor driver (e.g. L298N or similar)
* 1 × HC-SR04 ultrasonic distance sensor
* 1 × IR proximity sensor (digital output)
* 1 × Servo motor (for sweeping the ultrasonic sensor)
* Power supply/battery pack appropriate for motors and Arduino
* Wires, chassis, wheels, and other mechanical parts

### Pinout (as used in the sketch)

* Servo: D3
* IR sensor (digital input): D2
* Ultrasonic trig: D6
* Ultrasonic echo: D5
* Left motor forward: D8
* Left motor backward: D9
* Right motor forward: D11
* Right motor backward: D10

> Adjust pins in the sketch if you use different wiring or a different motor driver board.

---

## Wiring Notes

* Connect the servo signal to D3, and power the servo from a stable 5V source (use separate motor power if needed). Common ground between motor supply and Arduino is required.
* Wire the HC-SR04 trig to D6 and echo to D5. If your board runs at 5V the HC-SR04 works directly; for 3.3V logic boards use an appropriate level shifter on the echo pin.
* IR sensor digital output to D2.
* Motor driver inputs to D8, D9, D10, D11. Follow your motor driver wiring guide for enable pins and motor power.

---

## Software / Dependencies

* Arduino IDE (or PlatformIO)
* `Servo.h` (built-in Arduino library)

No external libraries beyond the Arduino core and Servo are required.

---

## Uploading

1. Open the sketch in Arduino IDE.
2. Select your board and correct COM/serial port.
3. Click **Upload**.
4. Open the Serial Monitor at `9600` baud to view debug output and the ASCII ceiling map.

---

## How It Works (high level)

1. The main `loop()` reads the IR sensor to check for nearby obstacles.
2. Before moving, the car calls `stopCar()` then `mapCaveCeiling()` to perform a servo sweep and sample ceiling distances.
3. If the IR sensor reads `LOW` (0) the car considers that an obstacle and executes `turnRight()` for a short period, then stops.
4. If the path is clear the car moves forward for a fixed duration.

### Important functions

* `moveForward()` — sets motor pins to drive both wheels forward.
* `turnRight()` — runs left motor forward and right motor backward to pivot right.
* `stopCar()` — brakes/halts both motors.
* `getDistance()` — triggers the HC-SR04 and returns measured distance in centimeters.
* `mapCaveCeiling()` — uses `getDistance()` and the servo sweep function `t18()` to produce a 10-step ASCII map of the ceiling. Each symbol encodes a height band.
* `t18()` — steps the servo by 18 degrees per call, updating a `pos` variable.

---

## Serial Output / Mapping Legend

When `mapCaveCeiling()` runs it prints one line of output characters representing 10 distance samples:

* `#` — distance < 10 cm (very low ceiling)
* `*` — distance < 20 cm (low ceiling)
* `-` — distance < 30 cm (medium ceiling)
* `.` — distance < 40 cm (high ceiling)
* (space) — distance >= 40 cm (very high ceiling)

Additionally, each measurement prints the numeric distance (in cm) to Serial.

---

## Contact / Authors

* Surya K
* Varghese K James
* Sujith M

For questions or contributions, open an issue or send a pull request.

---

## Changelog

* **1.0.1** — Initial documented release and minor cleanup.

