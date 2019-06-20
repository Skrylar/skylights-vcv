#include "turing-module-widget.hh"
#include "turing-module.hh"

turing_module_widget::turing_module_widget(Module* module) : ModuleWidget(module) {
  setPanel(APP->window->loadSvg(assetPlugin(pluginInstance, "res/Alan.svg")));

  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  
  addInput(createPort<DavidLTPort>
	   (Vec(63, 167),
	    PortWidget::INPUT,
	    module,
	    turing_module::I_MODE));
  
  addInput(createPort<DavidLTPort>
	   (Vec(4.5, 173),
	    PortWidget::INPUT,
	    module,
	    turing_module::I_CLOCK));

  addOutput(createPort<DavidLTPort>
	    (Vec(64, 317),
	     PortWidget::OUTPUT,
	     module,
	     turing_module::O_VOLTAGE));

  addOutput(createPort<DavidLTPort>
	    (Vec(116, 317),
	     PortWidget::OUTPUT,
	     module,
	     turing_module::O_EXPANSION));

  addOutput(createPort<DavidLTPort>
	    (Vec(90, 274),
	     PortWidget::OUTPUT,
	     module,
	     turing_module::O_PULSE));
  
  addOutput(createPort<DavidLTPort>
	    (Vec(90, 317),
	     PortWidget::OUTPUT,
	     module,
	     turing_module::O_GATE));

  addParam(createParam<RoundHugeBlackKnob>
	   (Vec(47, 80),
	    module,
	    turing_module::P_MODE,
	    0.0,
	    1.0,
	    1.0));

  addParam(createParam<RoundSmallBlackKnob>
	   (Vec(34, 320),
	    module,
	    turing_module::P_SCALE,
	    0.0,
	    10.0,
	    1.0));

  addParam(createParam<RoundBlackSnapKnob>
	   (Vec(61, 215),
	    module,
	    turing_module::P_LENGTH,
	    2.0,
	    16.0,
	    8.0));

  addParam(createParam<CKSS>
	   (Vec(10, 320),
	    module,
	    turing_module::P_POLE,
	    0.0,
	    1.0,
	    0.0));

  addParam(createParam<CKSS>
	   (Vec(121, 175),
	    module,
	    turing_module::P_WRITE,
	    0.0,
	    1.0,
	    0.0));

  for (size_t i = 0;
       i < 8;
       i++)
  {
     addChild(createLight<MediumLight<BlueLight>>
	      (Vec(18 + (15 * i), 50),
	       module,
	       turing_module::L_LIGHT1 + i));
  }
}
