# Stepper wiring: NEMA 17 → extension cable → TB6600

## What you have

- A NEMA 17 with a **6-pin connector housing**, but only **4 pins populated** (this is common — motor manufacturers reuse the same 6-pin shell across variants, some of which have extra wires for an encoder; a plain 4-wire bipolar motor just leaves 2 positions empty).
- A matching **extension cable** that plugs straight into that connector.
- The other end of the extension cable is unterminated and needs to be cut/stripped and wired into the TB6600.

Because only 4 of 6 pins are used, and the internal pairing (which pin = which coil) isn't standardized across manufacturers, **verify before wiring** rather than trusting color alone.

## Step 1 — Identify the 4 active pins and their coil pairing

1. Plug the extension cable into the motor.
2. At the cut end, you'll have 4 wires carrying signal and 2 dead/unused positions (the extension cable may or may not even populate those 2 extra conductors — that's fine, ignore them either way).
3. With the motor **unpowered**, use a multimeter in continuity/resistance mode on the 4 active wires at the cut end:
   - Two of the wires will show **low resistance (~1–5Ω)** between them — that's **Coil A** (A+ / A−).
   - The other two will show low resistance between them — that's **Coil B** (B+ / B−).
   - Any pair spanning the two coils will show **open circuit (no continuity)**.
4. Label the 4 wires: `A+`, `A−`, `B+`, `B−`. Within a coil, polarity (+/−) doesn't matter for the motor to spin — swapping A+/A− (or B+/B−) just reverses that phase, which you can also fix later by swapping the DIR signal or the motor's direction in firmware. What **does** matter is not mixing a Coil A wire with a Coil B wire.

> Common (but unverified for your exact motor) color convention on 4-wire NEMA 17s: Black/Green = Coil A, Red/Blue = Coil B. Confirm with the continuity test above — don't rely on color alone.

## Step 2 — Prep the cut end

1. Strip ~5mm of insulation from each of the 4 identified wires.
2. Tin the wire ends or fit ferrules for a clean, vibration-resistant connection into the TB6600's screw terminals.
3. Heat-shrink or cap the 2 unused conductors (if present) individually so they can't short against anything.

## Step 3 — Wire into the TB6600

The TB6600 motor-side screw terminals are labeled **A+, A−, B+, B−**. Connect:

| Motor wire | TB6600 terminal |
|---|---|
| Coil A + | A+ |
| Coil A − | A− |
| Coil B + | B+ |
| Coil B − | B− |

**Power off** the TB6600 (no 12V applied) while making/changing these connections — hot-plugging motor leads on a stepper driver can spike and damage the output stage.

## Step 4 — Set the TB6600 current & microstepping DIP switches

- Set the **current DIP switches** to match your NEMA 17's rated per-phase current (check the motor's nameplate/datasheet — commonly ~1.2–1.7A for a standard NEMA 17). Don't exceed the motor's rating.
- Set the **microstepping DIP switches** to whatever resolution you want (e.g. 1/8 or 1/16 is a reasonable default for smoother extrusion). Note the setting — the Arduino firmware's steps-per-revolution assumption needs to match it (see the firmware comments in [firmware/nema17_extrusion_control/nema17_extrusion_control.ino](../firmware/nema17_extrusion_control/nema17_extrusion_control.ino)).

Next: [03-power-supply.md](03-power-supply.md) for powering the TB6600 (12V) and the Arduino (5V).
