#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    class BrowserIntegrationPluginClient : public BrowserIntegrationClient
    {
    public:
        BrowserIntegrationPluginClient (BrowserIntegration& browserIntegration,
                                        juce::AudioProcessorValueTreeState& parameterValueTree,
                                        juce::String clientName = "Plugin");
        
        void setupBrowserPluginIntegration();

    protected:
        juce::AudioProcessorValueTreeState& parameterValueTree;
        BrowserValueTreeSynchroniser valueTreeSynchroniser;
    };
}
}
