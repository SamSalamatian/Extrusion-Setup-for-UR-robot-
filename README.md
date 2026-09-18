# UR Extrusion Setup

Documentation and firmware for driving a custom NEMA 17 extrusion motor from an Arduino + TB6600 driver, and triggering it (on/off + speed) from a Universal Robots **UR10** or **UR20** arm through its control box I/O — including the pin numbers to use in **Grasshopper**.

This repo exists so the electrical setup, the Arduino firmware, and the robot-side I/O mapping all live in one versioned place instead of scattered notes.

## What this covers

| Doc | Contents |
|---|---|
| [docs/01-bom.md](docs/01-bom.md) | Parts list |
| [docs/02-stepper-wiring.md](docs/02-stepper-wiring.md) | NEMA 17 (4-wire, 6-pin housing) → extension cable → TB6600 |
| [docs/03-power-supply.md](docs/03-power-supply.md) | 12V for the TB6600 (fed from the control box area) and 5V for the Arduino (adapter cable) |
| [docs/04-driver-arduino-wiring.md](docs/04-driver-arduino-wiring.md) | TB6600 control side → Arduino |
| [docs/05-arduino-ur-robot-io.md](docs/05-arduino-ur-robot-io.md) | Arduino ↔ UR10/UR20 control box I/O (on/off + speed) |
| [docs/06-grasshopper-integration.md](docs/06-grasshopper-integration.md) | Pin numbers/values to use inside Grasshopper |
| [docs/07-safety.md](docs/07-safety.md) | Safety notes specific to this setup |
| [firmware/nema17_extrusion_control/](firmware/nema17_extrusion_control/nema17_extrusion_control.ino) | Arduino sketch |

## Signal chain (high level)

```
UR10 / UR20 control box                Arduino Uno/Nano               TB6600 driver              NEMA 17
┌─────────────────────┐   on/off   ┌───────────────────┐   PUL/DIR  ┌───────────────┐   A+A-B+B-  ┌─────────┐
│ Configurable Digital │──24V DO──▶│ D-pin (opto/div.)  │───────────▶│                │────────────▶│         │
│ Output (CO)          │            │                    │            │   TB6600       │             │ NEMA17  │
│ Configurable Analog  │  0-10V AO │ A-pin (volt. div.) │            │   stepper      │             │ stepper │
│ Output (AO)           │──────────▶│                    │   step     │   driver       │             │ motor   │
└─────────────────────┘            │  (speed control)   │───pulses──▶│                │             └─────────┘
                                    └───────────────────┘            └───────┬────────┘
                                                                              │ VCC/GND
                                                                     12V DC PSU (fed near control box)
Arduino 5V ◀── adjustable 5V adapter (set to 5V)
```

See [docs/05-arduino-ur-robot-io.md](docs/05-arduino-ur-robot-io.md) for why the 24V/0–10V robot signals need level-shifting before they reach the Arduino.

## Quick pin summary (Arduino side)

| Function | Arduino pin | Notes |
|---|---|---|
| STEP (PUL-) | D3 | to TB6600 PUL- |
| DIR (DIR-) | D4 | to TB6600 DIR- |
| ENABLE (ENA-) | D5 | to TB6600 ENA- (optional) |
| Run on/off (from UR) | D7 | through opto-isolator, active HIGH |
| Speed (from UR) | A0 | through voltage divider, 0–5V in |

Full rationale and wiring detail in the docs above.

## Status

Initial documentation pass — verify wire colors/pinouts against your actual hardware (see the "verify before wiring" callouts in each doc) before powering anything on.
