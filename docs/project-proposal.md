# NEXUS — Project Proposal

## Project overview
NEXUS is a small-scale Autonomous Guided Vehicle (AGV) prototype for moving small items along a prepared warehouse-style route. The selected MVP uses a 2WD differential-drive base, line tracking, front obstacle sensing and a station marker.

## Problem
In small warehouses and training environments, people may spend time repeatedly moving small items between storage, picking and dispatch points. This repetitive movement can create avoidable walking and handling effort and may slow simple workflows.

## Proposed solution
NEXUS follows a marked route using a five-channel IR sensor array. An ESP32 reads the sensors and controls two geared DC motors through a TB6612FNG driver. An HC-SR04 sensor provides front obstacle detection; when an obstacle is within the configured threshold, the robot stops. A wide line marker identifies the destination station.

## Objectives
- Demonstrate autonomous line-guided movement.
- Stop when a front obstacle is detected within a configured threshold.
- Detect a designated station marker and stop.
- Carry a small demonstration payload on a removable tray.
- Use modular, accessible components and 3D-printed mounts.

## MVP scope
The prototype operates on a prepared, marked test route. It is not a production-ready warehouse vehicle and does not currently provide SLAM, free-space navigation, dynamic rerouting, inventory integration or fleet management.

## Expected impact
The project demonstrates a low-cost approach to automating a simple, repetitive transport route. Evaluation will measure route completion, obstacle-stop behavior, station detection and payload stability.

## Future work
Potential extensions include RFID / QR task selection, wheel encoders, mapping and localization, dynamic rerouting, monitoring dashboard and multi-robot coordination.
