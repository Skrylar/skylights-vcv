#include "skylights.hh"
#include "recorder-module.hh"

Plugin *plugin;


/*[[[cog
  from modules import simple_plugins
  for p in simple_plugins:
    pn = p['name'].replace('_', '-')
    cog.outl('#include "{0}-module.hh"'.format(pn))
    cog.outl('#include "{0}-module-widget.hh"'.format(pn))
  ]]]*/
#include "adrift-module.hh"
#include "adrift-module-widget.hh"
#include "turing-module.hh"
#include "turing-module-widget.hh"
#include "turing-pulse-module.hh"
#include "turing-pulse-module-widget.hh"
#include "turing-volts-module.hh"
#include "turing-volts-module-widget.hh"
#include "turing-vactrol-module.hh"
#include "turing-vactrol-module-widget.hh"
/*[[[end]]]*/

/*[[[cog
  for p in simple_plugins:
    cog.out('Model* {0}_model = Model::create<{0}_module, {0}_module_widget>("{1}", "{2}", "{3}", '.format(p['name'], p['plugin'], p['slug'], p['friendly_name']))
    cog.out(', '.join(['rack::' + x.name for x in p['tags']]))
    cog.outl(');')
  ]]]*/
Model* adrift_model = Model::create<adrift_module, adrift_module_widget>("Skylights", "SkAdrift", "Adrift (Analogue Drift)", rack::SAMPLE_AND_HOLD_TAG);
Model* turing_model = Model::create<turing_module, turing_module_widget>("Skylights", "SkTuringV2", "SK Alan (Turing Machine)", rack::SEQUENCER_TAG);
Model* turing_pulse_model = Model::create<turing_pulse_module, turing_pulse_module_widget>("Skylights", "SkTuringPulse", "SK Alan (Pulse Expander)", rack::UTILITY_TAG);
Model* turing_volts_model = Model::create<turing_volts_module, turing_volts_module_widget>("Skylights", "SkTuringVolts", "SK Alan (Volts Expander)", rack::UTILITY_TAG);
Model* turing_vactrol_model = Model::create<turing_vactrol_module, turing_vactrol_module_widget>("Skylights", "SkTuringVactrol", "SK Alan (Vactrol Mix Expander)", rack::UTILITY_TAG);
/*[[[end]]]*/

void init(Plugin *p) {
   plugin = p;
   p->slug = TOSTRING(SLUG);
   p->version = TOSTRING(VERSION);

   // Add all Models defined throughout the plugin
   //p->addModel(recorder_model);
   p->addModel(whatnote_model);

   /*[[[cog
     for p in simple_plugins:
       cog.outl('p->addModel({}_model);'.format(p['name']))
     ]]]*/
   p->addModel(adrift_model);
   p->addModel(turing_model);
   p->addModel(turing_pulse_model);
   p->addModel(turing_volts_model);
   p->addModel(turing_vactrol_model);
   /*[[[end]]]*/
}
