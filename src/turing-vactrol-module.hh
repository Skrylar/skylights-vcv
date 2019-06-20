#pragma once

#include "skylights.hh"
#include "vtl5c3.hh"

struct turing_vactrol_module : Module {
   enum ParamIds {
      P_VOL1,
      P_VOL2,
      P_VOL3,
      P_VOL4,
      NUM_PARAMS
   };
   enum InputIds {
      I_EXPANDER,
      I_INPUT1,
      I_INPUT2,
      I_INPUT3,
      I_INPUT4,
      NUM_INPUTS
   };
   enum OutputIds {
      O_LEFT,
      O_RIGHT,
      NUM_OUTPUTS
   };
   enum LightIds {
      L_GATE1,
      L_GATE2,
      L_GATE3,
      L_GATE4,
      L_GATE5,
      L_GATE6,
      L_GATE7,
      L_GATE8,
      NUM_LIGHTS
   };

   vtl5c3 m_vactrol[8];

   void onSampleRateChange() override;

   turing_vactrol_module();
   virtual ~turing_vactrol_module();

   void process(const ProcessArgs &args) override;
};
