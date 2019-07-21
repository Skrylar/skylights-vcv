#include "turing-vactrol-module.hh"

void turing_vactrol_module::process(const ProcessArgs &args) {
  uint16_t seq =
      (uint16_t)ceil((inputs[I_EXPANDER].getVoltage() / 10.0) * 65535.0);

  lights[L_GATE1].value = (seq & 1) > 0 ? 1.0 : 0.0;
  lights[L_GATE2].value = (seq & 2) > 0 ? 1.0 : 0.0;
  lights[L_GATE3].value = (seq & 4) > 0 ? 1.0 : 0.0;
  lights[L_GATE4].value = (seq & 8) > 0 ? 1.0 : 0.0;
  lights[L_GATE5].value = (seq & 16) > 0 ? 1.0 : 0.0;
  lights[L_GATE6].value = (seq & 32) > 0 ? 1.0 : 0.0;
  lights[L_GATE7].value = (seq & 64) > 0 ? 1.0 : 0.0;
  lights[L_GATE8].value = (seq & 128) > 0 ? 1.0 : 0.0;

  outputs[O_LEFT].setVoltage(0.0);
  outputs[O_RIGHT].setVoltage(0.0);

  size_t o = 0; // stores which of the eight steps we're working with
  for (size_t i = 0; i < 4; i++) {
    double gate;
    gate = (seq & (1 << o)) ? 1.0 : 0.0;
    outputs[O_LEFT].value +=
        m_vactrol[o].step(gate) *
        (params[P_VOL1 + i].getValue() * inputs[I_INPUT1 + i].getVoltage());

    o++;

    gate = (seq & (1 << o)) ? 1.0 : 0.0;
    outputs[O_RIGHT].value +=
        m_vactrol[o].step(gate) *
        (params[P_VOL1 + i].getValue() * inputs[I_INPUT1 + i].getVoltage());

    o++;
  }
}

turing_vactrol_module::turing_vactrol_module() : Module() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

  for (size_t i = 0; i < 8; i++) {
    m_vactrol[i] = vtl5c3();
  }

  onSampleRateChange();
  for (size_t i = 0; i < 4; i++) {
    configParam(turing_vactrol_module::P_VOL1 + i, -1.0, 1.0, 0.0, "");
  }
}

void turing_vactrol_module::onSampleRateChange() {
  double s = APP->engine->getSampleRate();
  for (size_t i = 0; i < 8; i++) {
    m_vactrol[i].set_samplerate(s);
  }
}

turing_vactrol_module::~turing_vactrol_module() {}
