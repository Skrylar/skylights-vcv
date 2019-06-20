#include "adrift-module.hh"
#include "adrift-module-widget.hh"

adrift_module_widget::adrift_module_widget(Module* module)
   : ModuleWidget(module)
{
   setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Adrift.svg")));

   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   // all
   addInput(createInput<DavidLTPort>
	    (mm2px(Vec(6, 22)),
	     PortWidget::INPUT,
	     module,
	     adrift_module::I_TRIG_ALL));

   // turbulence
   addParam(createParam<RoundHugeBlackKnob>
	    (mm2px(Vec(23, 22)),
	     module,
	     adrift_module::P_ATTENUATOR,
	     -1.0,
	     1.0,
	     0.0));

   for (size_t i = 0;
	i < adrift_module::channels;
	i++)
   {
      const int shift = 32;

      // input
      addInput(createInput<DavidLTPort>
	       (Vec(7, 155 + (shift * i)),
		PortWidget::INPUT,
		module,
		adrift_module::I_CV0 + i));

      // sail
      addInput(createInput<DavidLTPort>
	       (Vec(41, 155 + (shift * i)),
		PortWidget::INPUT,
		module,
		adrift_module::I_TRIG0 + i));

      // bipolar toggle
      addParam(createParam<CKSS>
	       (Vec(85, 157 + (shift * i)),
		module,
		adrift_module::P_BIP0 + i,
		0.0,
		1.0,
		0.0));

      addOutput(createOutput<DavidLTPort>
		(Vec(117, 155 + (shift * i)),
		 PortWidget::OUTPUT,
		 module,
		 adrift_module::O_OUT0 + i));
   }
}

adrift_module_widget::~adrift_module_widget() {
}
