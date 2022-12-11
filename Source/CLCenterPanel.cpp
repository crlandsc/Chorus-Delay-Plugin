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

    mFxPanel = std::make_unique<CLFxPanel>(inProcessor);
    mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mFxPanel.get());
}

CLCenterPanel::~CLCenterPanel()
{
}