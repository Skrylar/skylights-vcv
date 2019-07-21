#pragma once

#include "skylights.hh"
#include "vtl5c3.hh"

struct vactrolyzer_module : Module {
  enum ParamIds { NUM_PARAMS };
  enum InputIds { I_VAC1, I_VAC2, NUM_INPUTS };
  enum OutputIds { O_VAC1, O_VAC2, NUM_OUTPUTS };
  enum LightIds { L_VAC1, L_VAC2, NUM_LIGHTS };

  vactrolyzer_module();
  virtual ~vactrolyzer_module();

  vtl5c3 m_vactrol[2];

  void onSampleRateChange() override;
  void process(const ProcessArgs &args) override;
};
