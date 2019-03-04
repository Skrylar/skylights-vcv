#pragma once

#include "skylights.hh"

struct recorder_module_widget;

// TODO consider making this class definition fully opaque
struct recorder_button: rack::Component, rack::FramebufferWidget {
   Module *module = NULL;
   std::shared_ptr<SVG> m_up_svg;
   std::shared_ptr<SVG> m_down_svg;
   SVGWidget *sw;
   
   recorder_module_widget* m_mom; // who do we send events to
   size_t m_id;			  // how do we identify ourselves
   bool m_toggle;

   recorder_button();

   void configure
   (recorder_module_widget* parent,
    size_t id,
    std::shared_ptr<SVG> up_svg,
    std::shared_ptr<SVG> down_svg);
   
   virtual ~recorder_button();

   void onAction(EventAction&) override;
   void onDragStart(EventDragStart&) override;
   void onDragEnd(EventDragEnd&) override;
};

struct recorder_module_widget : ModuleWidget {
   enum ids {
      id_rec_btn,
      id_pause_btn,
   };
   
  recorder_module_widget(Module* module);
  ~recorder_module_widget();
  
  json_t *toJson() override;
  void fromJson(json_t* rootJ) override;
  
  void reset() override;
  void appendContextMenu(Menu* menu) override;

  void draw(NVGcontext* vg) override;
   
protected:
   void on_button(size_t id, bool down);
   friend recorder_button;
};
