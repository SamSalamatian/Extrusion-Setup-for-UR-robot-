# Arduino ↔ UR10 / UR20 control box I/O

Both the UR10 and UR20 control boxes expose **Configurable I/O** screw terminals on the controller I/O panel:

- **Configurable Digital Outputs (CO0–CO7)** — 24V, used here for **on/off**.
- **Configurable Analog Outputs (AO0–AO1)** — 0–10V (or 4–20mA, selectable) — used here for **speed**.
- **PWR / GND** terminals for the I/O rail.

The Arduino's I/O is 5V logic. The UR's signals (24V digital, 0–10V analog) will damage an Arduino pin directly, so both need to be stepped down. **Don't skip this** — this is the step most likely to fry a board if rushed.

## On/off: UR configurable digital output → Arduino digital input

Use a 4-channel opto-isolator module (cheap, common, e.g. PC817-based):

1. UR **CO_x** (a configurable digital output, e.g. CO0) → opto module input+ (through the module's onboard current-limiting resistor).
2. UR **GND** (I/O ground) → opto module input−.
3. Opto module output side: Arduino **5V** → module VCC, Arduino **GND** → module GND, module signal-out → Arduino **D7**.
4. In the UR program/Polyscope, set that configurable output HIGH to start extrusion, LOW to stop.

This keeps the UR's 24V domain and the Arduino's 5V domain galvanically isolated — safer than a resistor divider for a digital line, and forgiving of the UR I/O's higher current capability.

If you don't have an opto module on hand, a resistor divider (e.g. 10kΩ from CO_x to the Arduino pin, 4.7kΩ from that pin to GND) will also step 24V down to a safe ~5.7V logic-high level, but isolation is preferable — prefer the opto module if you can.

## Speed: UR configurable analog output → Arduino analog input

The UR analog output, configured for **0–10V** mode, needs to come down to the Arduino's 0–5V ADC input range:

1. Build a simple 2-resistor voltage divider: UR **AO_x** → 10kΩ → (node) → 10kΩ → UR/Arduino common **GND**.
2. Take the signal from the **node** between the two resistors → Arduino **A0**. This divides the 0–10V range down to 0–5V, matching the Arduino's ADC.
3. In firmware, `analogRead(A0)` (0–1023) is mapped to a step interval / pulse rate — see the sketch in [firmware/](../firmware/nema17_extrusion_control/nema17_extrusion_control.ino).

Confirm in Polyscope's I/O setup that the analog output is actually set to **voltage mode (0–10V)** and not current mode (4–20mA) — the two need different scaling on the Arduino side, and this doc assumes voltage mode.

## Common ground across all three systems

Tie together: UR I/O GND, Arduino GND, TB6600 GND, and the 5V supply GND. One shared reference point for everything — this is what makes the divider/opto math above valid.

## Pin summary

| Signal | UR control box | Arduino pin | Via |
|---|---|---|---|
| Run on/off | Configurable Digital Output (e.g. CO0) | D7 | Opto-isolator |
| Speed | Configurable Analog Output (e.g. AO0), 0–10V mode | A0 | Voltage divider (10k/10k) |

Next: [06-grasshopper-integration.md](06-grasshopper-integration.md) for how to drive CO0/AO0 from Grasshopper.
