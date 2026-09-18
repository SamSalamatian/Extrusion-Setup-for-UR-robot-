# Bill of Materials

| # | Item | Notes |
|---|---|---|
| 1 | NEMA 17 stepper motor (4-wire bipolar, 6-pin connector housing with 4 pins populated) | Already have |
| 2 | Matching extension cable for the motor's connector | Already have — one end plugs into the motor, the other end gets cut and wired to the TB6600 |
| 3 | TB6600 stepper driver | 9–42V DC input, up to ~4A output |
| 4 | Arduino (Uno/Nano or similar 5V logic board) | Generates STEP/DIR pulses, reads UR signals |
| 5 | 12V DC power supply | Powers the TB6600 — fed from near the UR control box (see [03-power-supply.md](03-power-supply.md)) |
| 6 | Adjustable power adapter (set to 5V) | Powers the Arduino |
| 7 | 4-channel opto-isolator module (or equivalent, e.g. PC817-based) | Steps the UR's 24V digital output down to a safe Arduino input |
| 8 | 2x resistors (e.g. 10kΩ + 10kΩ) for a voltage divider | Steps the UR's 0–10V analog output down to 0–5V for the Arduino |
| 9 | Multimeter | For continuity-checking motor coil pairs and connector pinout before wiring |
| 10 | Heat-shrink tubing / wire ferrules / terminal blocks | For the cut end of the extension cable |

Quantities intentionally omitted — fill in once the BOM is finalized for procurement.
