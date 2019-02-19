#include "skylights.hh"

struct adrift_module: public Module {
   static const size_t channels = 1;

   enum ParamIds {
      P_ATTENUATOR,
      NUM_PARAMS
   };
   enum InputIds {
      I_TRIG_ALL,
      I_TRIG0,
      I_CV0,
      I_BIP0,
      NUM_INPUTS
   };
   enum OutputIds {
      O_OUT0,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   SchmittTrigger m_reset_all;

   SchmittTrigger m_reset[channels];
   double noise[channels];

   bit_spigot m_noise_source;

   adrift_module();
   virtual ~adrift_module();

   void noisify_all();
   void noisify(int channel);

   virtual void step();
   virtual void onSampleRateChange();
   virtual void onReset();
   virtual void onRandomize();

   virtual json_t *toJson();
   virtual void fromJson(json_t* root);
};
