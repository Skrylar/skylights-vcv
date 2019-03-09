#include "skylights.hh"
#include "bit-spigot.hh"
#include <dsp/digital.hpp>

struct adrift_module: public Module {
   static const size_t channels = 6;

   enum ParamIds {
      P_ATTENUATOR,
      P_BIP0, P_BIP1, P_BIP2, P_BIP3, P_BIP4, P_BIP5,
      NUM_PARAMS
   };

   enum InputIds {
      I_TRIG_ALL,
      I_TRIG0, I_TRIG1, I_TRIG2, I_TRIG3, I_TRIG4, I_TRIG5,
      I_CV0, I_CV1, I_CV2, I_CV3, I_CV4, I_CV5,
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
