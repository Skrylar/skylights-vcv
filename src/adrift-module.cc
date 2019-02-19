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
   // TODO
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
      output[O_OUT0+i] = inputs[I_CV0+i] + (noise[i] * param[P_ATTENUATOR]);
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

