#include "recorder-module-widget.hh"
#include "recorder-module.hh"

recorder_module_widget::recorder_module_widget(Module* module) : ModuleWidget() {
	setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Recorder.svg")));

	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addInput(createInput<PJ301MPort>(mm2px(Vec(3.7069211, 10.530807)), module, recorder_module::AUDIO_INPUT + 0));
	addInput(createInput<PJ301MPort>(mm2px(Vec(3.7069211, 23.530807)), module, recorder_module::AUDIO_INPUT + 1));
	addInput(createInput<PJ301MPort>(mm2px(Vec(3.7069211, 36.530807)), module, recorder_module::AUDIO_INPUT + 2));
	addInput(createInput<PJ301MPort>(mm2px(Vec(3.7069211, 49.530807)), module, recorder_module::AUDIO_INPUT + 3));

}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
//Model *recorder_model = createModel<recorder_module, recorder_module_widget>("Skylights", "SkRecorder", "SK Recorder", RECORDING_TAG);
