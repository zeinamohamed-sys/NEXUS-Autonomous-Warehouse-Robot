# NEXUS — Autonomous Smart Warehouse Robot
**GDG Robotics | Repository starter — 2WD differential-drive design**

NEXUS is a small-scale Autonomous Guided Vehicle (AGV) prototype designed to demonstrate line-guided movement, front obstacle detection and stop behavior, station-marker detection, and small-payload transport in a controlled warehouse-style course.

> **Status:** Starter code and engineering documentation. The physical robot has not been verified by this repository. Do not describe proposed or untested behavior as completed.

## Selected MVP design
- ESP32 DevKit (main controller)
- TB6612FNG dual motor driver
- 2 DC geared motors + caster wheel (differential drive)
- 5-channel digital IR line sensor
- HC-SR04 ultrasonic sensor (front obstacle detection)
- Protected rechargeable battery pack, with regulated logic supply
- 3D-printed sensor bracket, electronics cover and payload tray

## Structure
```text
NEXUS-Autonomous-Warehouse-Robot/
├── README.md
├── .gitignore
├── firmware/nexus_agv.ino
├── hardware/bill_of_materials.csv
├── hardware/wiring-plan.md
└── docs/
    ├── project-proposal.md
    ├── system-architecture.md
    └── test-plan.md
```

## Build and upload
1. Install Arduino IDE and the ESP32 board support package.
2. Open `firmware/nexus_agv.ino`.
3. Confirm the pin map and logic voltage for your exact modules.
4. Select the correct ESP32 board and port, then compile and upload.
5. Test with the wheels lifted first. Confirm motor direction at low speed.
6. Calibrate the line sensor polarity and tune speed / steering values.
7. Measure actual stopping distance and adjust the obstacle threshold.

## Critical electrical safety
- ESP32 GPIO pins are **not 5 V tolerant**. Protect the HC-SR04 ECHO line with a voltage divider or level shifter.
- Verify TB6612FNG motor voltage/current ratings against the chosen motors.
- Do not power motors from the ESP32 3.3 V output.
- Use a protected battery pack and suitable regulator; add a physical main switch / emergency power cut-off.
- Join grounds between logic and motor driver supplies.
- Confirm all connections before inserting the battery.

## Current limitations
The MVP follows a prepared floor line. It does not currently implement SLAM, free-space navigation, dynamic rerouting, warehouse inventory integration or multi-robot fleet management. These are possible future extensions.

## Team completion checklist
- [ ] Confirm actual motor, battery, sensor and ESP32 module models.
- [ ] Validate wiring and motor direction.
- [ ] Calibrate IR sensor polarity and thresholds.
- [ ] Measure obstacle stopping distance.
- [ ] Run and record all tests in `docs/test-plan.md`.
- [ ] Add actual wiring photos and CAD/STL files when produced.
- [ ] Replace indicative BOM prices with supplier quotes / actual purchase prices.
- [ ] Add team member names and project supervisor if required.
