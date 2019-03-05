#include "skylights.hh"
#include "bit-spigot.hh"
#include <dsp/digital.hpp>

struct adrift_module: public Module {
   static const size_t channels = 1;

   enum ParamIds {
      P_ATTENUATOR,
      P_BIP0,
      NUM_PARAMS
   };
   enum InputIds {
      I_TRIG_ALL,
      I_TRIG0,
      I_CV0,
      NUM_INPUTS
   };
   enum OutputIds {
      O_OUT0,
      NUM_OUTPUTS
   };
   enum LightIds {
      NUM_LIGHTS
   };

   rack::SchmittTrigger m_reset_all;
   rack::SchmittTrigger m_reset[channels];
   double noise[channels];

   bit_spigot m_noise_source;

   adrift_module();
   virtual ~adrift_module();

   void noisify_all();
   void noisify(int channel);

   void step() override;
   void onSampleRateChange() override;
   void onReset() override;
   void onRandomize() override;

   json_t *toJson() override;
   void fromJson(json_t* root) override;
};
