#include "skylights.hh"

struct adrift_module_widget : ModuleWidget {
  adrift_module_widget(Module* module);
  ~adrift_module_widget();
  
  json_t *toJson() override;
  void fromJson(json_t* rootJ) override;
  
  void create() override;
  void _delete() override;
  void disconnect() override;
  void reset() override;
  void randomize() override;
  void appendContextMenu(Menu* menu) override;

  void draw(NVGcontext* vg) override;
  void onMouseDown(EventMouseDown& e) override;
  void onMouseMove(EventMouseMove& e) override;
  void onHoverKey(EventHoverKey& e) override;
  void onDragStart(EventDragStart& e) override;
  void onDragEnd(EventDragEnd& e) override;
  void onDragMove(EventDragMove& e) override;
};
