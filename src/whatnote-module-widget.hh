#pragma once

#include "skylights.hh"

struct whatnote_module_widget : ModuleWidget {
  std::shared_ptr<Font> font;
  
  whatnote_module_widget(Module* module);

  void draw(NVGcontext *vg) override;

};
