#include "whatnote-module-widget.hh"
#include "whatnote-module.hh"

whatnote_module_widget::whatnote_module_widget(Module* module) : ModuleWidget(module) {
  font = APP->window->loadFont(assetPlugin(pluginInstance, "res/LEDCalculator.ttf"));

  setPanel(APP->window->loadSvg(assetPlugin(pluginInstance, "res/WhatNote.svg")));

  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(createPort<PJ301MPort>(Vec(57.5, 273), PortWidget::INPUT, module, whatnote_module::AUDIO_INPUT + 0));
}

void whatnote_module_widget::draw(const DrawArgs &args) {
  whatnote_module* mod = reinterpret_cast<whatnote_module*>(module);

  static const char* semitone_labels[12] =
    { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

  ModuleWidget::draw(args);
  if (!mod) return;

  char buffer[128];

  nvgFillColor(args.vg, nvgRGBA(0x00, 0x00, 0x00, 0xFF));
  nvgFontFaceId(args.vg, font->handle);
  nvgTextLetterSpacing(args.vg, 0);
  nvgTextAlign(args.vg, NVG_ALIGN_CENTER);

  // the big font
  nvgFontSize(args.vg, 20);

  if (mod->octave >= -10) {
    snprintf
      (reinterpret_cast<char*>(&buffer),
       128,
       "%s%d",
       semitone_labels[mod->semitone],
       mod->octave);

    nvgTextBox(args.vg, 25, 164, 85, buffer, 0);

    // the little fonts
    nvgFontSize(args.vg, 14);

    if (mod->cents > 0) {
       snprintf
	  (reinterpret_cast<char*>(&buffer),
	   128,
	   "+%d",
	   mod->cents);
    } else {
       snprintf
	  (reinterpret_cast<char*>(&buffer),
	   128,
	   "%d",
	   mod->cents);
    }

    nvgTextBox(args.vg, 25, 182, 85, buffer, 0);
  } else {
    nvgTextBox(args.vg, 25, 164, 85, "--", 0);

    // the little fonts
    nvgFontSize(args.vg, 14);
  }

  snprintf
    (reinterpret_cast<char*>(&buffer),
     128,
     "%.2f V",
     mod->voltage);

  nvgTextBox(args.vg, 25, 198, 85, buffer, 0);
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *whatnote_model = createModel<whatnote_module, whatnote_module_widget>("SkWhatnoteCV");
