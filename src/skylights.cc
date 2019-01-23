#include "skylights.hh"
#include "recorder-module.hh"

Plugin *plugin;

void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	//p->addModel(recorder_model);
	p->addModel(whatnote_model);
	p->addModel(turing_model);
}
