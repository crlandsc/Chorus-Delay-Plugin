/*
  ==============================================================================

    CLPanelBase.h
    Created: 9 Dec 2022 5:56:19pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "CLInterfaceDefines.h"
#include "JuceHeader.h"
#include "CLHelperFunctions.h"

class CLPanelBase:
    public Component
{
public:
    CLPanelBase(ChorusDelayAudioProcessor* inProcessor);
    ~CLPanelBase();

    void mouseEnter(const MouseEvent& event) override;

    void mouseExit(const MouseEvent& event) override;

    void paint(Graphics& g) override; // override JUCE paint function - currently no functionality

protected: // make protected because this is a base class and members need to be inherited
    ChorusDelayAudioProcessor* mProcessor;
};
