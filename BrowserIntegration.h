/**
 A BrowserIntegration instance wraps a BrowserComponent, providing methods
 to send JSON messages (wrapped in a juce::var) and register callbacks for
 receiving events from Javascript.

 Usually you will want to construct a single BrowserIntegration instance and
 pass a reference down to any other classes that want to interact with it.
 */
#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    using BrowserCallback = std::function<void (juce::var)>;

    class BrowserIntegration
    {
    public:
        BrowserIntegration (BrowserComponent& browser);

        void registerBrowserCallback (juce::String name, BrowserCallback callback);
        void sendEventToBrowser (juce::String eventType, juce::var data, bool suppressLog = false);

    protected:
        void handleMessage (juce::var message);

        std::unordered_map<juce::String, std::vector<BrowserCallback>> callbacksByEventName;

        BrowserComponent& browser;
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
