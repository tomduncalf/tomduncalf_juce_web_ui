/*
  ==============================================================================

    BrowserIntegration.cpp
    Created: 10 May 2021 4:14:34pm
    Author:  Tom Duncalf

  ==============================================================================
*/

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserIntegration::BrowserIntegration (BrowserComponent& b): browser (b)
    {
        browser.setOnMessageCallback ([this] (juce::var message) {
            handleMessage (message);
        });
    }

    void BrowserIntegration::registerBrowserCallback (juce::String name, BrowserCallback callback)
    {
        auto hasExistingCallbacks = callbacksByEventName.find (name) != callbacksByEventName.end();
        if (hasExistingCallbacks)
            callbacksByEventName[name].push_back (callback);
        else
            callbacksByEventName[name] = { callback };
    }

    void BrowserIntegration::sendEventToBrowser (juce::String eventType, juce::var data)
    {
        auto* obj = new juce::DynamicObject();
        obj->setProperty ("eventType", eventType);
        obj->setProperty ("data", data);

        browser.sendMessage (juce::var (obj));
    }

    void BrowserIntegration::handleMessage (juce::var message)
    {
        if (! message.hasProperty ("eventType"))
        {
            jassertfalse;// malformed message
            return;
        }

        auto eventType = message.getProperty ("eventType", "");
        auto callbacks = callbacksByEventName.find (eventType);

        if (callbacks == callbacksByEventName.end())
        {
            DBG ("No callbacks defined for " << eventType.toString());
            jassertfalse;
            return;
        }

        for (auto& callback: callbacks->second)
            callback (message.getProperty ("data", juce::var()));
    }
}// namespace BrowserIntegration
}// namespace tomduncalf
