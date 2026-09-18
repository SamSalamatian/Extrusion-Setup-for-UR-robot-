# Power supply

Two independent power rails in this setup — **don't** try to derive one from the other.

## 1. TB6600 driver — 12V DC

- Use a dedicated 12V DC power supply (well within the TB6600's 9–42V input range).
- Physically, feed/mount this supply **from the area near the UR control box** — i.e. plug its AC brick into an outlet on/near the control box or the cell's power strip that's already switched with the robot, rather than routing a long separate mains run to the driver. That way the driver only has power when the cell/control box does.
- Wire the 12V supply's **+V** and **GND** output to the TB6600's **VCC** and **GND** power-input screw terminals (not the motor terminals — see [02-stepper-wiring.md](02-stepper-wiring.md) for those).
- Do **not** connect the TB6600's 12V rail to Arduino power or signal pins — the two share only a common **GND** reference (see [04-driver-arduino-wiring.md](04-driver-arduino-wiring.md)).

> If you'd rather power the TB6600 from the UR control box's own 24V accessory/configurable-I/O power rail instead of a separate 12V brick: the TB6600 accepts up to 42V so 24V works electrically, but the control box's 24V I/O supply typically has a modest shared current budget (on the order of 2A across everything using it) — check your specific control box's I/O power rating against the TB6600 current-limit DIP setting before doing this. A separate 12V brick sized for the motor is the safer default and is what the rest of this doc assumes.

## 2. Arduino — 5V

- You have an adjustable power adapter/cable set to output 5V.
- **Feed this into the Arduino's 5V pin (or VIN, if your specific board's onboard regulator is rated for exactly 5V in — check your board), not the barrel jack.** Most Arduino barrel jacks feed an onboard 5V regulator and expect 7–12V in; feeding 5V into the barrel jack will undervolt the board or not work at all. Feeding the 5V pin directly bypasses that regulator, which is correct here since the adapter is already regulated to 5V.
- Common ground: this 5V supply's GND must be tied to the same ground as the Arduino (normal if you're using the Arduino's own 5V/GND pins) — and that ground also needs to be common with the TB6600 control-side GND (see next doc).

## Summary

| Rail | Voltage | Powers | Fed from |
|---|---|---|---|
| Driver power | 12V DC | TB6600 VCC | Supply mounted/plugged near UR control box |
| Logic power | 5V DC | Arduino 5V pin | Adjustable adapter, set to 5V |

Next: [04-driver-arduino-wiring.md](04-driver-arduino-wiring.md).
