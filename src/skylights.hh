#pragma once

// we don't control these, so don't complain to me about them
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include <vector>
#include <condition_variable>
#include <mutex>

#include "rack.hpp"

// re-entering our zone of concern
#pragma GCC diagnostic pop
#pragma clang diagnostic pop

using namespace rack;

// Forward-declare the Plugin, defined in skcorder.cc
extern Plugin *plugin;

#include "components.hh"

// Forward-declare each Model, defined in each module source file
extern Model *recorder_model;
extern Model *whatnote_model;
extern Model *turing_model;
extern Model *turing_volts_model;
extern Model *turing_pulse_model;
