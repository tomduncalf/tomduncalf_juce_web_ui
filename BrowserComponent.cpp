/*
  ==============================================================================

    WebBrowserComponent.cpp
    Created: 10 May 2021 9:03:23am
    Author:  Tom Duncalf

  ==============================================================================
*/

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserComponent::BrowserComponent()
    {
#if JUCE_DEBUG
        goToURL ("http://127.0.0.1:3000");
#else
        goToURL ("file://" + juce::File::getSpecialLocation (juce::File::SpecialLocationType::currentApplicationFile)
#if JUCE_MAC
                                 .getChildFile ("Contents")
#endif
                                 .getChildFile ("Resources")
                                 .getChildFile ("build")
                                 .getChildFile ("index.html")
                                 .getFullPathName());
#endif
    }

    BrowserComponent::BrowserComponent (juce::String initialUrl)
    {
        goToURL (initialUrl);
    }

    void BrowserComponent::sendMessage (const juce::var message)
    {
        const auto jsonMessage = juce::JSON::toString (message, true);
        const auto url = "javascript:" + jsCallbackName + "(" + jsonMessage + ")";

        DBG ("sendMessage: " << jsonMessage);
        goToURL (url);
    }

    bool BrowserComponent::pageAboutToLoad (const juce::String& newURL)
    {
        if (newURL.startsWith (urlSchema))
        {
            if (onMessageCallback)
            {
                auto messageString = juce::URL::removeEscapeChars (newURL.substring (urlSchema.length()));
                auto message = juce::JSON::parse (messageString);

                DBG ("message: " << messageString);

                onMessageCallback (message);
            }
            else
            {
                DBG ("No onMessageCallback defined in BrowserComponent");
                jassertfalse;
            }

            return false;
        }
        else
            return true;
    }

    void BrowserComponent::setOnMessageCallback (std::function<void (juce::var)> cb)
    {
        onMessageCallback = cb;
    }
}// namespace BrowserIntegration
}// namespace tomduncalf
