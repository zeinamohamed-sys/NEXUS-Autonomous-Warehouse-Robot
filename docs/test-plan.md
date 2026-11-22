# NEXUS — Prototype Test Plan

Record actual observations. Do not mark a test passed until it has been performed on the physical prototype.

| ID | Test | Procedure | Pass criterion | Status |
|---|---|---|---|---|
| T01 | Power-on safety | Power logic and motor system with wheels lifted | No overheating, smoke or unexpected movement | Not tested |
| T02 | Motor direction | Test each motor at low speed | Both wheels move in intended direction | Not tested |
| T03 | Line sensor calibration | Move sensor array over line and floor | Polarity and readings are documented | Not tested |
| T04 | Line following | Run a short marked route | Robot follows route without manual steering | Not tested |
| T05 | Obstacle stop | Place a safe test object ahead | Robot stops at configured threshold | Not tested |
| T06 | Station marker | Place a wide transverse marker | Robot stops and reports task completion | Not tested |
| T07 | Payload stability | Carry a light payload on the tray | Payload remains stable through route | Not tested |
| T08 | Repeatability | Repeat the same route 10 times | Record successes and failures | Not tested |

## Record
Route length, floor surface, payload mass, base speed, steering gain, configured obstacle threshold, measured stopping distance, successful runs, battery voltage and sensor calibration.

## Safety
Start with wheels lifted. Use a physical power cut-off. Keep people, fragile items and loose cables away from the test area.
