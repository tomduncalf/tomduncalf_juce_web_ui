/**
 BrowerValueTreeSynchroniser is a juce::ValueTreeSynchroniser which sends
 its sync messages to a BrowserIntegration, for them to then be decoded
 on the JS side so it can maintain a copy of the value tree.
 */
#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    class BrowserValueTreeSynchroniser : public juce::ValueTreeSynchroniser, private juce::Timer
    {
    public:
        BrowserValueTreeSynchroniser (juce::ValueTree& vt, juce::Identifier id, BrowserIntegration& b);

        void stateChanged (const void* encodedChange, size_t encodedChangeSize) override;
        void flushUpdates();

    protected:
        juce::Identifier treeId;
        juce::StringArray queuedChanges;
        BrowserIntegration& browserIntegration;
        
    private:
        void timerCallback() override;
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
