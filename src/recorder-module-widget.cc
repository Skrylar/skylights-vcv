#include "recorder-module-widget.hh"
#include "recorder-module.hh"

recorder_module_widget::recorder_module_widget(Module* module)
   : Module(module)
{
   setPanel(SVG::load(assetPlugin(plugin, "res/Recorder.svg")));

   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 10.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 0));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 21.06)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 1));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 31.589999999999996)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 2));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 42.12)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 3));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 52.65)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 4));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 63.17999999999999)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 5));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 73.71)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 6));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 84.24)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 7));
}

recorder_module_widget::~recorder_module_widget() {
}

json_t* recorder_module_widget::toJson() {
   // TODO
}

void recorder_module_widget::fromJson(json_t* rootJ) {
   // TODO
}

void recorder_module_widget::reset() {
   // TODO
}

void recorder_module_widget::appendContextMenu(Menu* menu) {
   // TODO
}

void recorder_module_widget::draw(NVGcontext* vg) {
   // TODO
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *recorder_model = Model::create<recorder_module, recorder_module_widget>("Skylights", "SkRecorder", "SK Recorder", RECORDING_TAG);
