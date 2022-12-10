/*
  ==============================================================================

    CLCenterPanelMenuBar.cpp
    Created: 9 Dec 2022 5:57:27pm
    Author:  Chris

  ==============================================================================
*/

#include "CLCenterPanelMenuBar.h"

CLCenterPanelMenuBar::CLCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

}

CLCenterPanelMenuBar::~CLCenterPanelMenuBar()
{

}
