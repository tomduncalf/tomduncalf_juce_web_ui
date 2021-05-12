/*
  ==============================================================================

    BrowserIntegrationClient.h
    Created: 10 May 2021 3:56:20pm
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    class BrowserIntegrationClient
    {
    public:
        BrowserIntegrationClient (juce::String clientName, BrowserIntegration& browserIntegration);

        void registerBrowserCallback (juce::String name, BrowserCallback callback);
        void sendEventToBrowser (juce::String eventName, juce::var data);

    protected:
        juce::String clientName;
        BrowserIntegration& browserIntegration;
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
