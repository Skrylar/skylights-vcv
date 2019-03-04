#include "recorder-module-widget.hh"
#include "recorder-module.hh"
#include <cassert>

recorder_button::recorder_button():
   m_up_svg(NULL),
   m_down_svg(NULL),
   m_mom(NULL),
   m_id(0),
   m_toggle(false)
{
}

void recorder_button::configure
(recorder_module_widget* parent,
 size_t id,
 std::shared_ptr<SVG> up_svg,
 std::shared_ptr<SVG> down_svg)
{
   assert(parent != NULL);
   assert(up_svg != NULL);
   assert(down_svg != NULL);

   m_up_svg = up_svg;
   m_down_svg = down_svg;
   m_mom = parent;
   m_id = id;
   m_toggle = false;

   sw = new SVGWidget();
   addChild(sw);
}

recorder_button::~recorder_button() {}

void recorder_button::onAction(EventAction&) {
   assert(m_mom != NULL);
   m_mom->on_button(m_id, m_toggle);
}

void recorder_button::onDragStart(EventDragStart&) {
   m_toggle = !m_toggle;
   EventAction eAction;
   onAction(eAction);
   sw->setSVG(m_toggle ? m_down_svg : m_up_svg);
   dirty = true;
}

void recorder_button::onDragEnd(EventDragEnd&) {}

recorder_module_widget::recorder_module_widget(Module* module)
   : ModuleWidget(module)
{
   setPanel(SVG::load(assetPlugin(plugin, "res/Recorder.svg")));

   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

   auto rec_button =
      Widget::create<recorder_button>(mm2px(Vec(10, 10)));
   rec_button->configure
      (this,
       id_rec_btn,
       SVG::load(assetPlugin(plugin, "res/rec_btn_up.svg")),
       SVG::load(assetPlugin(plugin, "res/rec_btn_down.svg")));
   addChild(rec_button);

   auto pause_button =
      Widget::create<recorder_button>(mm2px(Vec(10.0, 30.0)));
   pause_button->configure
      (this,
       id_pause_btn,
       SVG::load(assetPlugin(plugin, "res/pause_btn_up.svg")),
       SVG::load(assetPlugin(plugin, "res/pause_btn_down.svg")));
   addChild(pause_button);

   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 15.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 0));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 28.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 1));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 41.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 2));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 54.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 3));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 67.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 4));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 80.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 5));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 93.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 6));
   addInput(Port::create<PJ301MPort>
	    (mm2px(Vec(3.7069211, 106.53)),
	     Port::INPUT, module,
	     recorder_module::AUDIO_INPUT + 7));
}

recorder_module_widget::~recorder_module_widget() {
}

void recorder_module_widget::on_button(size_t id, bool down) {
}

json_t* recorder_module_widget::toJson() {
   return ModuleWidget::toJson();
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
   ModuleWidget::draw(vg);
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *recorder_model = Model::create<recorder_module, recorder_module_widget>("Skylights", "SkRecorder", "SK Recorder", RECORDING_TAG);
