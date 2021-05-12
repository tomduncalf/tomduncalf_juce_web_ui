/*
  ==============================================================================

    BrowserIntegration.h
    Created: 10 May 2021 4:14:34pm
    Author:  Tom Duncalf

  ==============================================================================
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
        void sendEventToBrowser (juce::String evenType, juce::var data);

    protected:
        void handleMessage (juce::var message);

        std::unordered_map<juce::String, std::vector<BrowserCallback>> callbacksByEventName;

        BrowserComponent& browser;
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
