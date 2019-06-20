
#pragma once

struct DavidLTPort : public SVGPort {
   DavidLTPort() {	
      setSVG(APP->window->loadSvg(assetPlugin(pluginInstance, "res/cntr_LT.svg")));
   }
};
