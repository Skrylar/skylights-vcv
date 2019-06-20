
#pragma once

struct DavidLTPort : public SvgPort {
   DavidLTPort() {
      setSvg(APP->window->loadSvg("res/cntr_LT.svg"));
   }
};
