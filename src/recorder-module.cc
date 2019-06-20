#include "recorder-module.hh"

void recorder_module::process(const ProcessArgs &args) {

}

recorder_module::recorder_module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

recorder_module::~recorder_module() {
}
