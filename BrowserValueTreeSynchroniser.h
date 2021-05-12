/*
  ==============================================================================

    BrowserValueTreeSynchroniser.h
    Created: 10 May 2021 3:04:24pm
    Author:  Tom Duncalf

  ==============================================================================
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
