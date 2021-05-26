/** BEGIN_JUCE_MODULE_DECLARATION

ID:             tomduncalf_juce_web_ui
vendor:         tom@tomduncalf.com
version:        0.0.1
name:           JUCE Browser Integration
description:    Provides helpers to integrate web-based UIs into a JUCE application
website:        https://github.com/tomduncalf/tomduncalf_juce_web_ui
license:        MIT

dependencies:   juce_core, juce_gui_extra, juce_audio_processors

END_JUCE_MODULE_DECLARATION
*/

#include <unordered_map>

#include <juce_core/juce_core.h>
#include <juce_gui_extra/juce_gui_extra.h>
// TODO add #if for this one to allow non-plugin use case?
#include <juce_audio_processors/juce_audio_processors.h>

#include "BrowserComponent.h"
#include "BrowserIntegration.h"
#include "BrowserIntegrationClient.h"
#include "BrowserValueTreeSynchroniser.h"
#include "BrowserIntegrationPluginClient.h"
