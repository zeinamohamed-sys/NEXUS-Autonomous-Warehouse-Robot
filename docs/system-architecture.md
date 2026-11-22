# System Architecture

## Control flow
1. **Sensing:** IR sensor array reads the route; HC-SR04 measures forward clearance.
2. **Decision:** ESP32 prioritizes obstacle stop, station detection, line-lost safety stop, then line following.
3. **Actuation:** TB6612FNG receives direction and PWM signals for left and right motors.
4. **Completion:** A wide marker activating all five line sensors is treated as the destination; the robot stops.

## Modules

| Module | Responsibility |
|---|---|
| ESP32 | Main controller and state logic |
| 5-channel IR sensor | Line tracking and station marker detection |
| HC-SR04 | Forward obstacle distance |
| TB6612FNG | Dual DC motor direction and speed control |
| 2WD differential drive | Movement and turning |
| Battery / regulator | Portable power and logic supply |
| 3D-printed parts | Payload tray, sensor bracket, electronics cover |

## Safety priority
`OBSTACLE_STOP` → `STATION_REACHED` → `LINE_LOST` → `FOLLOW_LINE`

The robot stops when an obstacle is detected or the route line is lost. It does not attempt an unverified obstacle bypass.
