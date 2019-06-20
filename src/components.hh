
#pragma once

struct DavidLTPort : public SVGPort {
   DavidLTPort() {	
      setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cntr_LT.svg")));
   }
};
