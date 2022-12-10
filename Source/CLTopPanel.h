/*
  ==============================================================================

    CLTopPanel.h
    Created: 9 Dec 2022 5:58:12pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "CLPanelBase.h"

class CLTopPanel :
    public CLPanelBase
{
public:

    CLTopPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLTopPanel();

    void paint(Graphics& g) override;

private:


};