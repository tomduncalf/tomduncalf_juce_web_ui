#pragma once

namespace tomduncalf
{
namespace BrowserIntegration
{
    BrowserIntegrationPluginClient::BrowserIntegrationPluginClient (BrowserIntegration& b,
                                                                    juce::AudioProcessorValueTreeState& p,
                                                                    juce::String c)
        : BrowserIntegrationClient (c, b),
          parameterValueTree (p),
          valueTreeSynchroniser (p.state, "PARAMETERS", b) {}

    // This is a separate method rather than called from the constructor because it needs
    // to be called after all the members of the class implementing it have been setup
    void BrowserIntegrationPluginClient::setupBrowserPluginIntegration()
    {
        registerBrowserCallback ("init", [this] (juce::var) {
            sendParameterMetadata();
            valueTreeSynchroniser.sendFullSyncCallback();
        });

        registerBrowserCallback ("setParameter", [this] (juce::var data) {
            parameterValueTree.getParameterAsValue (data["id"].toString()).setValue (data["value"]);
        });
    }

    void BrowserIntegrationPluginClient::sendParameterMetadata()
    {
        juce::Array<juce::var> parameterInfos;

        for (auto parameterState: parameterValueTree.state)
        {
            auto id = parameterState.getProperty ("id").toString();
            auto rangedParameter = parameterValueTree.getParameter (id);

            auto* parameterInfo = new juce::DynamicObject();
            parameterInfo->setProperty ("id", id);

            if (auto floatParameter = dynamic_cast<juce::AudioParameterFloat*> (rangedParameter))
            {
                parameterInfo->setProperty ("type", "float");
                parameterInfo->setProperty ("label", floatParameter->label);
                parameterInfo->setProperty ("min", floatParameter->range.start);
                parameterInfo->setProperty ("max", floatParameter->range.end);
                parameterInfo->setProperty ("step", floatParameter->range.interval);
            }
            else if (auto intParameter = dynamic_cast<juce::AudioParameterInt*> (rangedParameter))
            {
                parameterInfo->setProperty ("type", "int");
                parameterInfo->setProperty ("label", intParameter->label);
                parameterInfo->setProperty ("min", intParameter->getRange().getStart());
                parameterInfo->setProperty ("max", intParameter->getRange().getEnd());
                parameterInfo->setProperty ("step", 1);
            }
            else if (auto boolParameter = dynamic_cast<juce::AudioParameterBool*> (rangedParameter))
            {
                parameterInfo->setProperty ("type", "bool");
                parameterInfo->setProperty ("label", boolParameter->label);
            }
            else if (auto choiceParameter = dynamic_cast<juce::AudioParameterChoice*> (rangedParameter))
            {
                parameterInfo->setProperty ("type", "choice");
                parameterInfo->setProperty ("choices", choiceParameter->choices);
                parameterInfo->setProperty ("label", choiceParameter->label);
            }

            parameterInfos.add (juce::var (parameterInfo));

#if BROWSER_INTEGRATION_WRITE_PARAMETER_CONFIG_IN_DEBUG
            writeParameterConfigForTs (parameterInfos);
#endif
        }

        sendEventToBrowser ("parameterMetadata", parameterInfos);
    }

    void BrowserIntegrationPluginClient::writeParameterConfigForTs (juce::Array<juce::var> parameterInfos)
    {
    }
}
}
