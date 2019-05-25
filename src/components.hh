
#pragma once

struct DavidLTPort : public SVGPort {
   DavidLTPort() {	
      setSVG(SVG::load(assetPlugin(pluginInstance, "res/cntr_LT.svg")));
   }
};
