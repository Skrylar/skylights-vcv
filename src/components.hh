
#pragma once

struct DavidLTPort : public SVGPort {
   DavidLTPort() {
      setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cntr_LT.svg")));
   }
};
