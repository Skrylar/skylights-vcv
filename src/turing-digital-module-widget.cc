#include "turing-digital-module-widget.hh"
#include "turing-digital-module.hh"

turing_digital_module_widget::turing_digital_module_widget(Module* module) {
	setModule(module);
   setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/AlanDigital.svg")));

   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   addInput(createInput<DavidLTPort>
	    (Vec(10, 40),
	     module,
	     turing_digital_module::I_EXPANDER));
   
   for (size_t i = 0;
	i < 4;
	i++)
   {
      addInput(createInput<DavidLTPort>
	       (Vec(10, 100 + (30 * i)),
		module,
		turing_digital_module::I_INPUT1 + i));
   }

   size_t y = 0;
   for (size_t i = 0;
	i < 4;
	i++)
   {
		if(module)
			module->configParam(turing_digital_module::P_VOL1 + i,
									  -1.0,
									  1.0,
									  0.0);
		addParam(createParam<RoundBlackKnob>
					(Vec(60, 80 + (50 * i)),
					 module,
					 turing_digital_module::P_VOL1 + i));

      addChild(createLight<MediumLight<BlueLight>>
	       (Vec(63, 65 + (50 * i)),
		module,
		turing_digital_module::L_GATE1 + y++));
      addChild(createLight<MediumLight<BlueLight>>
	       (Vec(78, 65 + (50 * i)),
		module,
		turing_digital_module::L_GATE1 + y++));
   }
  
   addOutput(createOutput<DavidLTPort>
	     (Vec(10, 300),
	      module,
	      turing_digital_module::O_LEFT));
   addOutput(createOutput<DavidLTPort>
	     (Vec(40, 300),
	      module,
	      turing_digital_module::O_RIGHT));
}

