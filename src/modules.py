
from tags import ModuleTag
 
simple_plugins = [
   {
      'name': 'adrift',
      'plugin': 'Skylights',
      'slug': 'SkAdrift',
      'friendly_name': 'Adrift (Analogue Drift)',
      'tags': [ModuleTag.SAMPLE_AND_HOLD_TAG],
   },
   {
      'name': 'turing',
      'plugin': "Skylights",
      'slug': "SkTuringV2",
      'friendly_name': "SK Alan (Turing Machine)",
      'tags': [ModuleTag.SEQUENCER_TAG],
   },
   {
      'name': 'turing_pulse',
      'plugin': "Skylights",
      'slug': "SkTuringPulse",
      'friendly_name': "SK Alan (Pulse Expander)",
      'tags': [ModuleTag.UTILITY_TAG],
   },
   {
      'name': 'turing_volts',
      'plugin': "Skylights",
      'slug': "SkTuringVolts",
      'friendly_name': "SK Alan (Volts Expander)",
      'tags': [ModuleTag.UTILITY_TAG],      
   },
   {
      'name': 'turing_vactrol',
      'plugin': 'Skylights',
      'slug': 'SkTuringVactrol',
      'friendly_name': "SK Alan (Vactrol Mix Expander)",
      'tags': [ModuleTag.UTILITY_TAG],
   },
]

