/*
  ==============================================================================

    CLMainPanel.h
    Created: 9 Dec 2022 5:56:33pm
    Author:  Chris

  ==============================================================================
*/


#pragma once

#include "CLPanelBase.h"

#include "CLTopPanel.h"
#include "CLGainPanel.h"
#include "CLFxPanel.h"
#include "CLCenterPanel.h"

class CLMainPanel :
    public CLPanelBase
{
public:

    CLMainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLMainPanel();

private:

    std::unique_ptr<CLTopPanel> mTopPanel;
    std::unique_ptr<CLGainPanel> mInputGainPanel;
    std::unique_ptr<CLGainPanel> mOutputGainPanel;
    std::unique_ptr<CLCenterPanel> mCenterPanel;

};



/*
#pragma once

#include "CLPanelBase.h"

#include "CLTopPanel.h"
#include "CLGainPanel.h"
#include "CLFxPanel.h"
#include "CLCenterPanel.h"

class CLMainPanel
    : public CLPanelBase
{
public:
    CLMainPanel(ChorusDelayAudioProcessor* processor);
    ~CLMainPanel();

private:

    std::unique_ptr<CLTopPanel> mTopPanel;
    std::unique_ptr<CLGainPanel> mInputGainPanel;
    std::unique_ptr<CLGainPanel> mOutputputGainPanel;
    std::unique_ptr<CLCenterPanel> mCenterPanel;
};
*/

