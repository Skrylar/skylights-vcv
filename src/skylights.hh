#pragma once

// we don't control these, so don't complain to me about them
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#elif __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#endif

#include <condition_variable>
#include <mutex>
#include <vector>

#include "rack.hpp"

// re-entering our zone of concern
#ifdef __clang__
#pragma clang diagnostic pop
#elif __GNUC__
#pragma GCC diagnostic pop
#endif

using namespace rack;

// Forward-declare the Plugin, defined in skcorder.cc
extern Plugin *pluginInstance;

#include "components.hh"

// Forward-declare each Model, defined in each module source file
extern Model *recorder_model;
extern Model *whatnote_model;

/*[[[cog
  from modules import simple_plugins
  for p in simple_plugins:
    cog.outl('extern Model* {}_model;'.format(p['name']))
  ]]]*/
extern Model* adrift_model;
extern Model* turing_model;
extern Model* turing_pulse_model;
extern Model* turing_volts_model;
extern Model* turing_digital_model;
extern Model* turing_vactrol_model;
extern Model* vactrolyzer_model;
/*[[[end]]]*/
