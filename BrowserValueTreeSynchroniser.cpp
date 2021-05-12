/*
  ==============================================================================

    BrowserValueTreeSynchroniser.cpp
    Created: 10 May 2021 3:04:24pm
    Author:  Tom Duncalf

  ==============================================================================
*/

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserValueTreeSynchroniser::BrowserValueTreeSynchroniser (juce::ValueTree& vt, juce::Identifier id, BrowserIntegration& b)
        : juce::ValueTreeSynchroniser (vt),
          treeId (id),
          browserIntegration (b)
    {
    }

    void BrowserValueTreeSynchroniser::stateChanged (const void* encodedChange, size_t encodedChangeSize)
    {
        auto* dataObj = new juce::DynamicObject();
        dataObj->setProperty ("treeId", treeId.toString());

        auto change = juce::Base64::toBase64 (encodedChange, encodedChangeSize);
        dataObj->setProperty ("change", change);

        browserIntegration.sendEventToBrowser ("valueTreeStateChange", dataObj);
    }
}// namespace BrowserIntegration
}// namespace tomduncalf
