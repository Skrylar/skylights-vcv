#include "adrift-module.hh"

adrift_module::adrift_module() : Module() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(adrift_module::P_ATTENUATOR, -1.0, 1.0, 0.0, "");
  for (size_t i = 0; i < adrift_module::channels; i++) {
    // bipolar toggle
    configParam(adrift_module::P_BIP0 + i, 0.0, 1.0, 0.0, "");
  }
}

adrift_module::~adrift_module() {}

void adrift_module::noisify_all() {
  for (size_t i = 0; i < channels; i++) {
    noisify(i);
  }
}

void adrift_module::noisify(int channel) {
  // there is very likely a more efficient way to pull this off
  uint8_t dac;

  dac = (m_noise_source.next() ? 0 : 1) << 0;
  dac += (m_noise_source.next() ? 0 : 1) << 1;
  dac += (m_noise_source.next() ? 0 : 1) << 2;
  dac += (m_noise_source.next() ? 0 : 1) << 3;
  dac += (m_noise_source.next() ? 0 : 1) << 4;
  dac += (m_noise_source.next() ? 0 : 1) << 5;
  dac += (m_noise_source.next() ? 0 : 1) << 6;
  dac += (m_noise_source.next() ? 0 : 1) << 7;

  noise[channel] = ((double)dac) / 255.0;
}

void adrift_module::process(const ProcessArgs &args) {
  if (m_reset_all.process(inputs[I_TRIG_ALL].getVoltage())) {
    noisify_all();
  } else {
    for (size_t i = 0; i < channels; i++) {
      if (m_reset[i].process(inputs[I_TRIG0 + i].getVoltage())) {
        noisify(i);
      }
    }
  }

  for (size_t i = 0; i < channels; i++) {
    outputs[O_OUT0 + i].value =
        inputs[I_CV0 + i].getVoltage() +
        ((noise[i] - (0.5 * params[P_BIP0 + i].getValue())) *
         params[P_ATTENUATOR].getValue());
  }
}

void adrift_module::onSampleRateChange() {}

void adrift_module::onReset() { noisify_all(); }

void adrift_module::onRandomize() { noisify_all(); }

json_t *adrift_module::dataToJson() {
  auto map = json_object();
  auto array = json_array();

  for (size_t i = 0; i < channels; i++) {
    json_array_set_new(array, i, json_integer(noise[i]));
  }

  json_object_set_new(map, "noise", array);
  return map;
}

void adrift_module::dataFromJson(json_t *root) {
  if (!root)
    return;

  auto array_schrodinger = json_object_get(root, "noise");

  if (json_is_array(array_schrodinger)) {
    auto array = array_schrodinger;

    for (size_t i = 0; i < channels; i++) {
      auto schrodingers_float = json_array_get(array, i);
      if (json_is_number(schrodingers_float)) {
        noise[i] = json_integer_value(schrodingers_float);
      } else {
        noisify(i);
      }
    }
  } else {
    //      _                         _ _           _ _
    //   __| | __ _ _ __ ___  _ __   (_) |_    __ _| | |
    //  / _` |/ _` | '_ ` _ \| '_ \  | | __|  / _` | | |
    // | (_| | (_| | | | | | | | | | | | |_  | (_| | | |
    //  \__,_|\__,_|_| |_| |_|_| |_| |_|\__|  \__,_|_|_|
    noisify_all();
  }
}
