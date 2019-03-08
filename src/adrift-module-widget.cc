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
	     -2.0,
	     2.0,
	     0.0));

   for (size_t i = 0;
	i < 6;
	i++)
   {
      const int shift = 32;
      // sail
      addInput(Port::create<DavidLTPort>
	       (Vec(7, 155 + (shift * i)),
		Port::INPUT,
		module,
		adrift_module::I_TRIG0));

      // input
      addInput(Port::create<DavidLTPort>
	       (Vec(41, 155 + (shift * i)),
		Port::INPUT,
		module,
		adrift_module::I_CV0));

      // bipolar toggle
      addParam(ParamWidget::create<CKSS>
	       (Vec(85, 157 + (shift * i)),
		module,
		adrift_module::P_BIP0,
		0.0,
		1.0,
		0.0));

      addOutput(Port::create<DavidLTPort>
		(Vec(117, 155 + (shift * i)),
		 Port::OUTPUT,
		 module,
		 adrift_module::O_OUT0));
   }
}

adrift_module_widget::~adrift_module_widget() {
}

json_t* adrift_module_widget::toJson() {
   return ModuleWidget::toJson();
}

void adrift_module_widget::fromJson(json_t* rootJ) {
   // TODO
}

void adrift_module_widget::create() {
   // TODO
}

void adrift_module_widget::_delete() {
   // TODO
}

void adrift_module_widget::disconnect() {
   // TODO
}

void adrift_module_widget::reset() {
   // TODO
}

void adrift_module_widget::randomize() {
   // TODO
}

void adrift_module_widget::appendContextMenu(Menu* menu) {
   // TODO
}

void adrift_module_widget::draw(NVGcontext* vg) {
   ModuleWidget::draw(vg);
}

void adrift_module_widget::onMouseDown(EventMouseDown& e) {
   // TODO
}

void adrift_module_widget::onMouseMove(EventMouseMove& e) {
   // TODO
}

void adrift_module_widget::onHoverKey(EventHoverKey& e) {
   // TODO
}

void adrift_module_widget::onDragStart(EventDragStart& e) {
   // TODO
}

void adrift_module_widget::onDragEnd(EventDragEnd& e) {
   // TODO
}

void adrift_module_widget::onDragMove(EventDragMove& e) {
   // TODO
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model* adrift_model = Model::create<adrift_module, adrift_module_widget>
   ("Skylights",
    "SkAdrift",
    "Adrift (Analogue Drift)",
    rack::SAMPLE_AND_HOLD_TAG);
