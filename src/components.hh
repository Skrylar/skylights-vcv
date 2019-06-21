
#pragma once

struct DavidLTPort : public SvgPort {
   DavidLTPort() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance,"res/cntr_LT.svg")));

   }
};
