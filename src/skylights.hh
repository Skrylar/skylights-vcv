#pragma once

// we don't control these, so don't complain to me about them
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#endif

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include <vector>
#include <condition_variable>
#include <mutex>

#include "rack.hpp"

// re-entering our zone of concern
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
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
/*[[[end]]]*/
