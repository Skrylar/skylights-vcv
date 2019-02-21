#pragma once

#include "skylights.hh"
#include "tape-file.hh"

struct recorder_module : Module {
   const static size_t AUDIO_INPUTS = tape_file::TRACKS;

   enum ParamIds {
      NUM_PARAMS
   };
   enum InputIds {
      ENUMS(AUDIO_INPUT, AUDIO_INPUTS),
      NUM_INPUTS
   };
   enum OutputIds {
      NUM_OUTPUTS
   };
   enum LightIds {
      ENUMS(ARM_LIGHT, AUDIO_INPUTS),
      NUM_LIGHTS
   };

   tape_file m_tape;

   recorder_module();
   virtual ~recorder_module();

   // open a new tape file unless we were closed
   void open_tape();
   // close any tape we already had open
   void close_tape();
   // maybe open a new tape, if we already had a tape open
   void maybe_reopen_tape();

   void onSampleRateChange() override;

   void step() override;
};
