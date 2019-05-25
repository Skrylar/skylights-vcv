#include "turing-volts-module-widget.hh"
#include "turing-volts-module.hh"

turing_volts_module_widget::turing_volts_module_widget(Module* module) : ModuleWidget(module) {
  setPanel(SVG::load(assetPlugin(pluginInstance, "res/AlanVolts.svg")));

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  
  addInput(createPort<DavidLTPort>
	   (Vec(25, 45),
	    PortWidget::INPUT,
	    module,
	    turing_volts_module::I_EXPANDER));

  addOutput(createPort<DavidLTPort>
	   (Vec(25, 300),
	    PortWidget::OUTPUT,
	    module,
	    turing_volts_module::O_VOLTAGE));
  
  for (size_t i = 0;
       i < 5;
       i++)
    {
      addParam(createParam<RoundBlackKnob>
	       (Vec(15, 80 + (40 * i)),
		module,
		turing_volts_module::P_VOL1 + i,
		-1.0,
		1.0,
		0.0));
      
      addChild(createLight<MediumLight<BlueLight>>
	       (Vec(50, 90 + (40 * i)),
		module,
		turing_volts_module::L_LIGHT1 + i));
    }
}


