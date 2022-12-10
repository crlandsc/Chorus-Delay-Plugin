/*
  ==============================================================================

    CLGainPanel.h
    Created: 9 Dec 2022 5:57:52pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "CLPanelBase.h"

class CLGainPanel :
    public CLPanelBase
{
public:

    CLGainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLGainPanel();

private:

};