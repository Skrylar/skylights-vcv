#pragma once

#include "bit-spigot.hh"
#include "dsp/digital.hpp"
#include "skylights.hh"

struct turing_module : Module {
  enum ParamIds { P_WRITE, P_LENGTH, P_MODE, P_POLE, P_SCALE, NUM_PARAMS };
  enum InputIds { I_CLOCK, I_MODE, NUM_INPUTS };
  enum OutputIds { O_VOLTAGE, O_EXPANSION, O_GATE, O_PULSE, NUM_OUTPUTS };
  enum LightIds {
    L_LIGHT1,
    L_LIGHT2,
    L_LIGHT3,
    L_LIGHT4,
    L_LIGHT5,
    L_LIGHT6,
    L_LIGHT7,
    L_LIGHT8,
    NUM_LIGHTS
  };

  uint16_t m_sequence;
  bit_spigot m_spigot;
  rack::dsp::SchmittTrigger m_clock_trigger;

  turing_module();
  virtual ~turing_module();

  json_t *dataToJson() override;
  void dataFromJson(json_t *root) override;

  void process(const ProcessArgs &args) override;
  void onReset() override;
  void onRandomize() override;
};
