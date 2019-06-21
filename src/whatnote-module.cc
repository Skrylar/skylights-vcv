#include "whatnote-module.hh"

#include <cmath>

const double SEMITONE = 1.0 / 12.0;

void whatnote_module::process(const ProcessArgs &args) {
  voltage = inputs[0].getVoltage();
  
  // its not valid, so don't analyze it
  if (voltage < -10.0 || voltage > 10.0) {
    octave = -11.0;
    return;
  }

  double y;
  double x = modf(voltage, &y);	// semitones/cents are fractional part
  octave = (int)y + 4;		// octage is integer part

  // and find semitones in there
  if (x < 0.0) {
    octave -= 1.0;
    x = 1.0 + x;
  }

  double z;
  double w = modf(x / SEMITONE, &z);
  
  semitone = z;
  cents = (int)round(w * 100.0);
  if (cents == 100) {
    semitone = (semitone + 1) % 12;
    cents = 0;
  }

  assert(semitone >= 0);
  assert(semitone < 12);
}

whatnote_module::whatnote_module() : octave(0), semitone(0), cents(0), voltage(0) {
	this->Module::config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

whatnote_module::~whatnote_module() {
}
