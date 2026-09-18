/*
  NEMA 17 extrusion control via TB6600, triggered from a UR10/UR20
  configurable digital output (on/off) and configurable analog output
  (speed), stepped down per docs/05-arduino-ur-robot-io.md.

  Wiring (see docs/04-driver-arduino-wiring.md and docs/05-arduino-ur-robot-io.md):
    D3  -> TB6600 PUL-   (step pulse)
    D4  -> TB6600 DIR-   (direction, fixed HIGH here)
    D5  -> TB6600 ENA-   (optional; see ENABLE note below)
    D7  <- UR digital output, through opto-isolator (HIGH = run)
    A0  <- UR analog output (0-10V), through 10k/10k divider (0-5V at pin)
    5V  -> TB6600 PUL+/DIR+/ENA+ (common-anode wiring)
    GND shared across Arduino, TB6600 control side, and UR I/O GND

  Speed is set entirely by the analog input; there is no acceleration
  ramp here (extrusion speed changes are typically slow/continuous
  relative to a stepper's ability to just change rate directly). Add
  an AccelStepper-based ramp if your process needs one.
*/

const uint8_t STEP_PIN   = 3;
const uint8_t DIR_PIN    = 4;
const uint8_t ENABLE_PIN = 5;
const uint8_t RUN_PIN    = 7;   // from UR, via opto-isolator
const uint8_t SPEED_PIN  = A0;  // from UR, via voltage divider

// Step pulse interval bounds, in microseconds, between successive STEP
// edges. Smaller interval = faster. Tune these to your TB6600
// microstepping DIP setting and desired extrusion speed range.
const unsigned long MIN_STEP_INTERVAL_US = 300;   // fastest
const unsigned long MAX_STEP_INTERVAL_US = 4000;  // slowest (still moving)

// TB6600 needs a minimum STEP pulse width; a few microseconds is
// plenty of margin (check your specific module's datasheet).
const unsigned long STEP_PULSE_WIDTH_US = 5;

// Set to true if your TB6600 wiring uses ENA- to actively hold the
// motor enabled (i.e. LOW = enabled) while running, and you want it
// released (free-spin) when not running. Many setups simply leave
// ENA unconnected and can ignore this. Verify polarity on your module
// before relying on it — see docs/04-driver-arduino-wiring.md.
const bool USE_ENABLE_PIN = false;

unsigned long lastStepMicros = 0;
unsigned long stepIntervalUs = MAX_STEP_INTERVAL_US;
bool stepPinState = false;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(RUN_PIN, INPUT);

  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH);      // fixed extrusion direction
  digitalWrite(ENABLE_PIN, HIGH);   // inactive until enabled below, if used
}

void loop() {
  bool running = digitalRead(RUN_PIN) == HIGH;

  if (USE_ENABLE_PIN) {
    // Many TB6600 modules enable the driver when ENA- is pulled LOW.
    // Confirm on your module before depending on this.
    digitalWrite(ENABLE_PIN, running ? LOW : HIGH);
  }

  if (!running) {
    digitalWrite(STEP_PIN, LOW);
    stepPinState = false;
    return;
  }

  int speedRaw = analogRead(SPEED_PIN); // 0-1023, representing 0-5V (0-10V at UR before divider)
  stepIntervalUs = map(speedRaw, 0, 1023, MAX_STEP_INTERVAL_US, MIN_STEP_INTERVAL_US);
  stepIntervalUs = constrain(stepIntervalUs, MIN_STEP_INTERVAL_US, MAX_STEP_INTERVAL_US);

  unsigned long now = micros();
  if (now - lastStepMicros >= stepIntervalUs) {
    lastStepMicros = now;
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_PULSE_WIDTH_US);
    digitalWrite(STEP_PIN, LOW);
  }
}
