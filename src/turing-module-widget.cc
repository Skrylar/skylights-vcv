#include "turing-module-widget.hh"
#include "turing-module.hh"

turing_module_widget::turing_module_widget(Module *module) : ModuleWidget() {
  setModule(module);
  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Alan.svg")));

  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH,
                                         RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(
      createInput<DavidLTPort>(Vec(63, 167), module, turing_module::I_MODE));

  addInput(
      createInput<DavidLTPort>(Vec(4.5, 173), module, turing_module::I_CLOCK));

  addOutput(createOutput<DavidLTPort>(Vec(64, 317), module,
                                      turing_module::O_VOLTAGE));

  addOutput(createOutput<DavidLTPort>(Vec(116, 317), module,
                                      turing_module::O_EXPANSION));

  addOutput(
      createOutput<DavidLTPort>(Vec(90, 274), module, turing_module::O_PULSE));

  addOutput(
      createOutput<DavidLTPort>(Vec(90, 317), module, turing_module::O_GATE));

  addParam(createParam<RoundHugeBlackKnob>(Vec(47, 80), module,
                                           turing_module::P_MODE));
  addParam(createParam<RoundSmallBlackKnob>(Vec(34, 320), module,
                                            turing_module::P_SCALE));
  addParam(createParam<RoundBlackSnapKnob>(Vec(61, 215), module,
                                           turing_module::P_LENGTH));
  addParam(createParam<CKSS>(Vec(10, 320), module, turing_module::P_POLE));
  addParam(createParam<CKSS>(Vec(121, 175), module, turing_module::P_WRITE));

  for (size_t i = 0; i < 8; i++) {
    addChild(createLight<MediumLight<BlueLight>>(Vec(18 + (15 * i), 50), module,
                                                 turing_module::L_LIGHT1 + i));
  }
}
