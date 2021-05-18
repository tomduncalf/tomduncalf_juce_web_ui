namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserIntegrationClient::BrowserIntegrationClient (juce::String n, BrowserIntegration& b)
        : clientName (n),
          browserIntegration (b) {}

    void BrowserIntegrationClient::registerBrowserCallback (juce::String name, BrowserCallback callback)
    {
        browserIntegration.registerBrowserCallback (clientName + "::" + name, callback);
    }

    void BrowserIntegrationClient::sendEventToBrowser (juce::String eventType, juce::var data, bool suppressLog)
    {
        browserIntegration.sendEventToBrowser (clientName + "::" + eventType, data, suppressLog);
    }
}// namespace BrowserIntegration
}// namespace tomduncalf
