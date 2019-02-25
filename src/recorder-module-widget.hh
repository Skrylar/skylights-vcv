#pragma once

#include "skylights.hh"

struct recorder_module_widget : ModuleWidget {
  recorder_module_widget(Module* module);
  ~recorder_module_widget();
  
  json_t *toJson() override;
  void fromJson(json_t* rootJ) override;
  
  void reset() override;
  void appendContextMenu(Menu* menu) override;

  void draw(NVGcontext* vg) override;
};
