/*
  ==============================================================================

    CLCenterPanel.h
    Created: 9 Dec 2022 5:57:11pm
    Author:  Chris

  ==============================================================================
*/

#pragma once
#include "CLPanelBase.h"
#include "CLCenterPanelMenuBar.h"
#include "CLFxPanel.h"

class CLCenterPanel :
    public CLPanelBase
{
public:

    CLCenterPanel(ChorusDelayAudioProcessor* inProcessor);
	~CLCenterPanel();

private:

    std::unique_ptr<CLCenterPanelMenuBar> mMenuBar;
    std::unique_ptr<CLFxPanel> mFxPanel;
};
