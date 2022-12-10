/*
  ==============================================================================

    CLGainPanel.cpp
    Created: 9 Dec 2022 5:57:52pm
    Author:  Chris

  ==============================================================================
*/

#include "CLGainPanel.h"

CLGainPanel::CLGainPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    //setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);

}

CLGainPanel::~CLGainPanel()
{

}

