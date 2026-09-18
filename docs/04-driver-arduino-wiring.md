# TB6600 control side → Arduino

The TB6600 control-side terminals are usually labeled **PUL+/PUL−**, **DIR+/DIR−**, **ENA+/ENA−** (sometimes silkscreened CP+/CP−, CW+/CW−).

## Wiring (common-anode style, 5V logic)

This is the standard way to wire a TB6600 to a 5V-logic Arduino:

| TB6600 terminal | Connects to |
|---|---|
| PUL+ | Arduino 5V |
| DIR+ | Arduino 5V |
| ENA+ | Arduino 5V |
| PUL− | Arduino D3 (STEP) |
| DIR− | Arduino D4 (DIR) |
| ENA− | Arduino D5 (ENABLE) |
| GND (control side, if separate from VCC GND) | Arduino GND |

Tying PUL+/DIR+/ENA+ to +5V and pulsing the **minus** side from the Arduino is the manufacturer-recommended wiring for driving a TB6600 from 5V logic (it uses the TB6600's internal opto-isolators as intended, pulling the input LOW to trigger).

- **STEP (D3)**: one pulse = one microstep, at whatever resolution the TB6600's DIP switches are set to.
- **DIR (D4)**: sets rotation direction; HIGH/LOW meaning depends on wiring polarity — just check actual rotation direction once running and flip DIR or swap A+/A− (or B+/B−) at the motor if it's backwards.
- **ENABLE (D5)**: optional. Many people leave ENA unconnected (TB6600 enables by default in that state) — wiring it to an Arduino pin lets firmware fully cut motor current (e.g. so the motor can be freely hand-turned) independent of whether it's stepping.

## Critical: common ground

The Arduino's GND, the TB6600 control-side GND, and (per [03-power-supply.md](03-power-supply.md)) the 5V supply's GND all need to be tied together. Without a shared ground reference, the STEP/DIR/ENA signals from the Arduino have no valid reference at the TB6600 and won't work reliably.

The TB6600's **12V motor-power GND** and the **control-side GND** are usually internally common on the module — check your specific module's silkscreen/datasheet. If they're separate, tie all three grounds (Arduino, TB6600 control, 12V supply) together at one point.

Next: [05-arduino-ur-robot-io.md](05-arduino-ur-robot-io.md) for the UR10/UR20 side.
