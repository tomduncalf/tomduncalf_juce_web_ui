/**
 A BrowserComponent wraps the default juce WebBrowserComponent, adding
 functionality to communicate with the browser instance using a custom
 URL scheme to pass data.
 */
#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    class BrowserComponent : public juce::WindowsWebView2WebBrowserComponent
    {
    public:
        /** Create a browser component with the default URL (in debug mode, loading
        from the React dev server, and in release mode, loading from the built
        application bundle in the Resources directory)
        */
        BrowserComponent();

        /** Create a browser component with a specific URL */
        BrowserComponent (const juce::String initialUrl);

        void sendMessage (const juce::var message, bool suppressLog = false);
        bool pageAboutToLoad (const juce::String& newURL) override;

        void setOnMessageCallback (std::function<void (juce::var)> cb);

        void loadUI();

    protected:
        std::function<void (juce::var)> onMessageCallback;

        const juce::String urlSchema = "juce://";
        const juce::String jsCallbackName = "receiveMessageFromJuce";
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
