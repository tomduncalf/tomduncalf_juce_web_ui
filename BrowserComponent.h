/*
  ==============================================================================

    WebBrowserComponent.h
    Created: 10 May 2021 9:03:23am
    Author:  Tom Duncalf

  ==============================================================================
*/

#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    class BrowserComponent : public juce::WindowsWebView2WebBrowserComponent
    {
    public:
        BrowserComponent (const juce::String initialUrl);

        void sendMessage (const juce::var message);
        bool pageAboutToLoad (const juce::String& newURL) override;

        void setOnMessageCallback (std::function<void (juce::var)> cb);

    protected:
        std::function<void (juce::var)> onMessageCallback;

        const juce::String urlSchema = "juce://";
        const juce::String jsCallbackName = "receiveMessageFromJuce";
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
