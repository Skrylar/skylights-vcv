#include "recorder-module.hh"

void recorder_module::step() {
   if (!m_tape.is_open()) return; // do nothing if no tape open

   if (!m_output_buffer.full()) {
      Frame<AUDIO_INPUTS> input_frame;
      for (size_t i = 0;
	   i < AUDIO_INPUTS;
	   i++)
      {
	 input_frame.samples[i] = inputs[AUDIO_INPUT+i];
      }
      m_output_buffer.push(input_frame);
   } else {
      // TODO lock up rack until we've acquired some breathing room
   }
}

recorder_module::recorder_module()
   : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS),
     m_tape()
{
}

recorder_module::~recorder_module() {
}

void recorder_module::onSampleRateChange() {
   // need to open a new tape since the sample rate is different now
   maybe_reopen_tape();
}

void recorder_module::open_tape() {
   m_tape.open();
}

void recorder_module::close_tape() {
   m_tape.close();
}

void recorder_module::maybe_reopen_tape() {
   if (m_tape.is_open()) {
      close_tape();
      open_tape();
   }
}
