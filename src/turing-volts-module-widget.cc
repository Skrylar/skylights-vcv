#include "turing-volts-module-widget.hh"
#include "turing-volts-module.hh"

turing_volts_module_widget::turing_volts_module_widget(Module* module) {
		setModule(module);
  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AlanVolts.svg")));

  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  
  addInput(createInput<DavidLTPort>
	   (Vec(25, 45),
	    module,
	    turing_volts_module::I_EXPANDER));

  addOutput(createOutput<DavidLTPort>
	   (Vec(25, 300),
	    module,
	    turing_volts_module::O_VOLTAGE));
  
  for (size_t i = 0;
       i < 5;
       i++)
    {
		 if(module)
			 module->configParam(turing_volts_module::P_VOL1+i,-1.0,1.0,0.0);
		 addParam(createParam<RoundBlackKnob>
					 (Vec(15, 80 + (40 * i)),
					  module,
					  turing_volts_module::P_VOL1 + i));

      addChild(createLight<MediumLight<BlueLight>>
	       (Vec(50, 90 + (40 * i)),
		module,
		turing_volts_module::L_LIGHT1 + i));
    }
}


