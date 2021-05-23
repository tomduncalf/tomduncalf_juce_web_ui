namespace tomduncalf
{
namespace BrowserIntegration
{
#define VALUE_TREE_SYNCHRONISER_BATCH_CHANGES 0

    BrowserValueTreeSynchroniser::BrowserValueTreeSynchroniser (juce::ValueTree& vt, juce::Identifier id, BrowserIntegration& b)
        : juce::ValueTreeSynchroniser (vt),
          treeId (id),
          browserIntegration (b)
    {
        startTimerHz (30);
    }

    void BrowserValueTreeSynchroniser::stateChanged (const void* encodedChange, size_t encodedChangeSize)
    {
        // TODO could filter out redundant multiple changes to a single parameter
        // in a single batch here or elsewhere
        auto change = juce::Base64::toBase64 (encodedChange, encodedChangeSize);
        queuedChanges.add (change);

#if VALUE_TREE_SYNCHRONISER_BATCH_CHANGES
        // do nothing?
#else
        flushUpdates();
#endif
    }

    void BrowserValueTreeSynchroniser::timerCallback()
    {
        flushUpdates();
    }

    void BrowserValueTreeSynchroniser::flushUpdates()
    {
        if (queuedChanges.size() > 0)
        {
            auto* dataObj = new juce::DynamicObject();
            dataObj->setProperty ("treeId", treeId.toString());
            dataObj->setProperty ("changes", queuedChanges);
            browserIntegration.sendEventToBrowser ("valueTreeStateChange", dataObj);

            queuedChanges.clear();
        }
    }
}// namespace BrowserIntegration
}// namespace tomduncalf
