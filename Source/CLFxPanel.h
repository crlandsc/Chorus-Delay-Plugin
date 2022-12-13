/*
  ==============================================================================

    CLFxPanel.h
    Created: 9 Dec 2022 5:57:43pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "CLPanelBase.h"
#include "CLParameterSlider.h"

enum CLFxPanelStyle
{
    kCLFxPanelStyle_Delay,
    kCLFxPanelStyle_Chorus,
    kCLFxPanelStyle_TotalNumStyles
};

class CLFxPanel :
    public CLPanelBase
{
public:

    CLFxPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLFxPanel();

    void paint(Graphics& g) override;

    void setFxPanelStyle(CLFxPanelStyle inStyle);

private:

    CLFxPanelStyle mStyle;

    OwnedArray<CLParameterSlider> mSliders;
};
