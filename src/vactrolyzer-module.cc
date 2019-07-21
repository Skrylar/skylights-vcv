#include "vactrolyzer-module.hh"

void vactrolyzer_module::process(const ProcessArgs &args) {
  for (size_t i = 0; i < 2; i++) {
    outputs[O_VAC1 + i].value =
        m_vactrol[i].step(std::max((float)0.0, inputs[I_VAC1 + i].getVoltage()));
    lights[L_VAC1 + i].value = fabs(outputs[O_VAC1 + i].getVoltage());
  }
}

vactrolyzer_module::vactrolyzer_module() : Module() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  onSampleRateChange();
}

void vactrolyzer_module::onSampleRateChange() {
  double s = APP->engine->getSampleRate();
  for (size_t i = 0; i < 2; i++) {
    m_vactrol[i].set_samplerate(s);
  }
}

vactrolyzer_module::~vactrolyzer_module() {}
