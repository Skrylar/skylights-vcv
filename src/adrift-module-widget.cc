#include "adrift-module.hh"
#include "adrift-module-widget.hh"

adrift_module_widget::adrift_module_widget(Module* module)
   : ModuleWidget(module)
{
   setPanel(SVG::load(assetPlugin(plugin, "res/Adrift.svg")));

   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   // all
   addInput(Port::create<DavidLTPort>
	    (mm2px(Vec(6, 22)),
	     Port::INPUT,
	     module,
	     adrift_module::I_TRIG_ALL));

   // turbulence
   addParam(ParamWidget::create<RoundHugeBlackKnob>
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
      addInput(Port::create<DavidLTPort>
	       (Vec(7, 155 + (shift * i)),
		Port::INPUT,
		module,
		adrift_module::I_CV0 + i));

      // sail
      addInput(Port::create<DavidLTPort>
	       (Vec(41, 155 + (shift * i)),
		Port::INPUT,
		module,
		adrift_module::I_TRIG0 + i));

      // bipolar toggle
      addParam(ParamWidget::create<CKSS>
	       (Vec(85, 157 + (shift * i)),
		module,
		adrift_module::P_BIP0 + i,
		0.0,
		1.0,
		0.0));

      addOutput(Port::create<DavidLTPort>
		(Vec(117, 155 + (shift * i)),
		 Port::OUTPUT,
		 module,
		 adrift_module::O_OUT0 + i));
   }
}

adrift_module_widget::~adrift_module_widget() {
}
