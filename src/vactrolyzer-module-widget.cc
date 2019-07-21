#include "vactrolyzer-module-widget.hh"
#include "vactrolyzer-module.hh"

vactrolyzer_module_widget::vactrolyzer_module_widget(Module *module)
    : ModuleWidget() {
  setModule(module);
  setPanel(APP->window->loadSvg(
      asset::plugin(pluginInstance, "res/Vactrolyzer.svg")));

  double center_x = box.size.x / 4;

  addChild(createWidget<ScrewSilver>(Vec(center_x, 0)));
  addChild(createWidget<ScrewSilver>(
      Vec(center_x, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(createInput<DavidLTPort>(Vec(center_x - 5, 70), module,
                                    vactrolyzer_module::I_VAC1));
  addChild(createLight<MediumLight<BlueLight>>(Vec(center_x + 3, 100), module,
                                               vactrolyzer_module::L_VAC1));
  addOutput(createOutput<DavidLTPort>(Vec(center_x - 5, 130), module,
                                      vactrolyzer_module::O_VAC1));

  addInput(createInput<DavidLTPort>(Vec(center_x - 5, 70 + 113), module,
                                    vactrolyzer_module::I_VAC2));
  addChild(createLight<MediumLight<BlueLight>>(
      Vec(center_x + 3, 100 + 113), module, vactrolyzer_module::L_VAC2));
  addOutput(createOutput<DavidLTPort>(Vec(center_x - 5, 130 + 113), module,
                                      vactrolyzer_module::O_VAC2));
}
