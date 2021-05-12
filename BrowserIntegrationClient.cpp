/*
  ==============================================================================

    BrowserIntegrationClient.cpp
    Created: 10 May 2021 3:56:20pm
    Author:  Tom Duncalf

  ==============================================================================
*/

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserIntegrationClient::BrowserIntegrationClient (juce::String n, BrowserIntegration& b)
        : clientName (n), browserIntegration (b) {}

    void BrowserIntegrationClient::registerBrowserCallback (juce::String name, BrowserCallback callback)
    {
        browserIntegration.registerBrowserCallback (clientName + "::" + name, callback);
    }

    void BrowserIntegrationClient::sendEventToBrowser (juce::String eventName, juce::var data)
    {
        // TOOD
    }
} // namespace BrowserIntegration
} // namespace tomduncalf