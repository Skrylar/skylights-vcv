#include "adrift-module.hh"

adrift_module::adrift_module()
   : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS)
{
}

adrift_module::~adrift_module() {
}

void adrift_module::noisify_all() {
   for (size_t i = 0;
	i < channels;
	i++)
   {
      noisify(i);
   }
}

void adrift_module::noisify(int channel) {
   // there is very likely a more efficient way to pull this off
   uint8_t dac;

   dac = (m_noise_source.next() ? 0 : 1) << 0;
   dac = (m_noise_source.next() ? 0 : 1) << 1;
   dac = (m_noise_source.next() ? 0 : 1) << 2;
   dac = (m_noise_source.next() ? 0 : 1) << 3;
   dac = (m_noise_source.next() ? 0 : 1) << 4;
   dac = (m_noise_source.next() ? 0 : 1) << 5;
   dac = (m_noise_source.next() ? 0 : 1) << 6;
   dac = (m_noise_source.next() ? 0 : 1) << 7;

   noise[channel] = ((double)dac) / 255.0;
}

void adrift_module::step() {
   if (m_reset_all.process(inputs[I_TRIG_ALL])) {
      noisify_all();
   } else {
      for (size_t i = 0;
	   i < channels;
	   i++)
      {
	 if (m_reset[i].process(inputs[I_TRIG0+i])) {
	    noisify(i);
	 }
      }
   }

   for (size_t i = 0;
	i < channels;
	i++)
   {
      output[O_OUT0+i] =
	 inputs[I_CV0+i] +
	 ((noise[i] - (0.5 * param[I_BIP0+i])) * param[P_ATTENUATOR]);
   }
}

void adrift_module::onSampleRateChange() {
}

void adrift_module::onReset() {
   noisify_all();
}

void adrift_module::onRandomize() {
   noisify_all();
}

json_t* adrift_module::toJson() {
}

void adrift_module::fromJson(json_t* root) {
}
