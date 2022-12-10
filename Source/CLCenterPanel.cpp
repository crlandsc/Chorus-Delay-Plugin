/*
  ==============================================================================

    CLCenterPanel.cpp
    Created: 9 Dec 2022 5:57:11pm
    Author:  Chris

  ==============================================================================
*/

#include "CLCenterPanel.h"

CLCenterPanel::CLCenterPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);

    mMenuBar = std::make_unique<CLCenterPanelMenuBar>(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar.get());
}

CLCenterPanel::~CLCenterPanel()
{
}