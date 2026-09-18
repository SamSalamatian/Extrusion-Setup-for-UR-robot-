# Grasshopper integration

This assumes you're generating the UR program (URScript) from Grasshopper using a UR-capable plugin (e.g. Scorpion, Robots, RobotComponents, Machina, or similar — the exact plugin isn't fixed here since several exist and component names differ between them). What's constant across all of them: somewhere in the toolchain there's a **"Set Digital Output"** / **"Set I/O"** style component and, if you're doing speed control, a **"Set Analog Output"** component. Feed them the pin numbers below.

## On/off (extrusion start/stop)

- **Output type:** Configurable Digital Output
- **Pin:** `0` (i.e. **CO0**) — matches [05-arduino-ur-robot-io.md](05-arduino-ur-robot-io.md)
- **Value:** `True` / `1` = extrude, `False` / `0` = stop

In a "Set Digital Output" component: `pin = 0`, `state = True/False` (boolean toggle or waypoint-driven).

If your plugin emits raw URScript text instead of typed components, the equivalent line is:

```
set_configurable_digital_out(0, True)
```

## Speed control

- **Output type:** Configurable Analog Output
- **Pin:** `0` (i.e. **AO0**)
- **Range:** `0.0`–`10.0` (Volts) — make sure this output is set to **voltage mode** in Polyscope's I/O configuration, not current mode
- **Value:** map your desired extrusion speed to 0.0–10.0 in Grasshopper (e.g. a slider or a value remapped from toolpath feed rate) before feeding it into the "Set Analog Output" component.

Raw URScript equivalent:

```
set_analog_out(0, speed_value)   # speed_value in 0.0–10.0
```

On the Arduino side, `analogRead(A0)` sees this 0–10V signal scaled down to 0–5V by the voltage divider, and the firmware remaps it back to a step rate — see [firmware/nema17_extrusion_control/nema17_extrusion_control.ino](../firmware/nema17_extrusion_control/nema17_extrusion_control.ino).

## Pin summary (for quick reference inside Grasshopper)

| Function | UR pin to set in Grasshopper | Type |
|---|---|---|
| Extrusion on/off | `0` (CO0) | Digital Output, boolean |
| Extrusion speed | `0` (AO0) | Analog Output, 0.0–10.0V |

> These pin numbers (CO0 / AO0) are suggestions, not fixed by hardware — any free configurable digital/analog output works as long as the number here, the physical UR terminal you wired in [05-arduino-ur-robot-io.md](05-arduino-ur-robot-io.md), and the pin set in the Grasshopper component all match. If another pin is already in use elsewhere in your cell (grippers, tool changers, etc.), just pick a free one and update it consistently in both docs.
