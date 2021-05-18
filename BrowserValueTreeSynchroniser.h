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
    class BrowserValueTreeSynchroniser : public juce::ValueTreeSynchroniser
    {
    public:
        BrowserValueTreeSynchroniser (juce::ValueTree& vt, juce::Identifier id, BrowserIntegration& b);

        void stateChanged (const void* encodedChange, size_t encodedChangeSize) override;

    protected:
        juce::Identifier treeId;
        BrowserIntegration& browserIntegration;
    };
}// namespace BrowserIntegration
}// namespace tomduncalf
