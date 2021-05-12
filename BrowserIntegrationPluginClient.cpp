#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserIntegrationPluginClient::BrowserIntegrationPluginClient (BrowserIntegration& b,
                                                                    juce::AudioProcessorValueTreeState& p,
                                                                    juce::String c)
        : BrowserIntegrationClient (c, b),
          parameterValueTree (p),
          valueTreeSynchroniser (p.state, "PARAMETERS", b) {}

    // This is a separate method rather than called from the constructor because it needs
    // to be called after all the members of the class implementing it have been setup
    void BrowserIntegrationPluginClient::setupBrowserPluginIntegration()
    {
        registerBrowserCallback ("init", [this] (juce::var) {
            valueTreeSynchroniser.sendFullSyncCallback();
        });

        registerBrowserCallback ("setParameter", [this] (juce::var data) {
            parameterValueTree.getParameterAsValue (data["id"].toString()).setValue (data["value"]);
        });
    }
}
}
