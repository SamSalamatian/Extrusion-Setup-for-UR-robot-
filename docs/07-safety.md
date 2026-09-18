# Safety notes

- **Power off before wiring/re-wiring.** Disconnect the 12V and 5V supplies before touching any motor, driver, or control terminal. Hot-plugging stepper motor leads on the TB6600 can spike-damage its output stage.
- **Double-check polarity** on the 12V supply into the TB6600 (VCC/GND) before first power-up — reversed polarity on most TB6600 modules is not protected and will damage the board.
- **Never feed the UR's 24V or 0–10V signals directly into an Arduino pin.** Always go through the opto-isolator (digital) or voltage divider (analog) described in [05-arduino-ur-robot-io.md](05-arduino-ur-robot-io.md). Arduino digital/analog pins are not 24V-tolerant.
- **Common ground is mandatory, not optional.** UR I/O GND, Arduino GND, TB6600 GND, and the 5V supply GND all need to be tied together for the signals to be valid. Confirm continuity between them before trusting any reading.
- **Set the TB6600 current-limit DIP switches to match the NEMA 17's rated current** (from its nameplate/datasheet) before running it — overcurrent will overheat the motor.
- **Mechanical safety:** an extrusion head mounted on a UR arm is a pinch/entanglement hazard in addition to the arm's own hazards. Treat the extrusion mechanism (nozzle, feed gears, heater if present) as part of the robot's safety-rated workspace/risk assessment, not as an afterthought bolted on the side.
- **This is a custom, non-UR-certified end effector.** Running it from the UR's configurable I/O does not make it safety-rated. If the extrusion process introduces new hazards (heat, moving feed mechanism, material under pressure), update the cell's risk assessment accordingly before production use.
