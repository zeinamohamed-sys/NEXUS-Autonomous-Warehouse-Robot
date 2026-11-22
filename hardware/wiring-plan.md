# NEXUS — Preliminary Wiring Plan (2WD + TB6612FNG)

This pin map matches the starter firmware. Verify it against the exact board/module before wiring.

## ESP32 to TB6612FNG

| ESP32 | TB6612FNG | Function |
|---|---|---|
| GPIO 26 | AIN1 | Left motor direction |
| GPIO 27 | AIN2 | Left motor direction |
| GPIO 25 | PWMA | Left motor speed PWM |
| GPIO 14 | BIN1 | Right motor direction |
| GPIO 12 | BIN2 | Right motor direction |
| GPIO 33 | PWMB | Right motor speed PWM |
| GPIO 13 | STBY | Driver standby enable |
| 3V3 | VCC | Logic supply (confirm module spec) |
| Motor supply | VM | Motor power, within motor/driver ratings |
| GND | GND | Common ground |

Connect the left motor to A01/A02 and the right motor to B01/B02. If a wheel turns in the wrong direction, reverse that motor's two output wires or adjust direction logic.

## ESP32 to 5-channel digital IR sensor

| Sensor output | ESP32 |
|---|---|
| Far left OUT1 | GPIO 34 |
| OUT2 | GPIO 35 |
| Center OUT3 | GPIO 32 |
| OUT4 | GPIO 19 |
| Far right OUT5 | GPIO 18 |
| VCC / GND | As specified by the sensor board |

Check whether the module outputs are 3.3 V compatible. ESP32 GPIOs must not receive 5 V.

## ESP32 to HC-SR04

| HC-SR04 | ESP32 |
|---|---|
| TRIG | GPIO 5 |
| ECHO | GPIO 4 through voltage divider / level shifter |
| VCC | Regulated 5 V supply if required |
| GND | Common ground |

HC-SR04 ECHO is commonly 5 V. Protect GPIO 4.

## Power and safety
- Select a protected battery pack based on the motors' rated voltage and stall current.
- Use a suitable regulator for ESP32 logic power.
- Never power motors from the ESP32 3.3 V pin.
- Connect logic and motor grounds together.
- Add an accessible main switch / emergency power cut-off.
- Verify the TB6612FNG current limit against motor stall current.
- Test with wheels lifted before floor tests.

## Calibration
1. Confirm line sensor output polarity and set `LINE_IS_LOW_ON_BLACK`.
2. Test each motor direction at low speed.
3. Begin with low `BASE_SPEED`; tune `KP` gradually.
4. Measure stopping distance and tune `OBSTACLE_STOP_CM`.
5. Use a wide destination bar that activates all five line sensors.
