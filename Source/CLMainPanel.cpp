/*
  ==============================================================================

    CLMainPanel.cpp
    Created: 9 Dec 2022 5:56:33pm
    Author:  Chris

  ==============================================================================
*/


#include "CLMainPanel.h"
#include "CLParameters.h"

CLMainPanel::CLMainPanel(ChorusDelayAudioProcessor* inProcessor):
    CLPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH,
        MAIN_PANEL_HEIGHT);

    mTopPanel = std::make_unique<CLTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());

    mInputGainPanel = std::make_unique<CLGainPanel>(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mInputGainPanel->setParameterID(kParameter_InputGain);
    addAndMakeVisible(mInputGainPanel.get());

    mCenterPanel = std::make_unique<CLCenterPanel>(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel.get());

    mOutputGainPanel = std::make_unique<CLGainPanel>(inProcessor);
    mOutputGainPanel->setTopLeftPosition(
        MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH,
        TOP_PANEL_HEIGHT);
    mOutputGainPanel->setParameterID(kParameter_OutputGain);
    addAndMakeVisible(mOutputGainPanel.get());

}

CLMainPanel::~CLMainPanel()
{

}





/*
#include "CLMainPanel.h"


CLMainPanel::CLMainPanel(ChorusDelayAudioProcessor* inProcessor)
    :CLPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH,
        MAIN_PANEL_HEIGHT);

    mTopPanel = std::make_unique<CLTopPanel>(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel.get());

    mInputGainPanel = std::make_unique<CLGainPanel>(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mInputGainPanel->setParameterID(kParameter_InputGain);
    addAndMakeVisible(mInputGainPanel.get());

    mCenterPanel = std::make_unique<CLCenterPanel>(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel.get());

    mOutputputGainPanel = std::make_unique<CLGainPanel>(inProcessor);
    mOutputputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH,
        TOP_PANEL_HEIGHT);
    mOutputputGainPanel->setParameterID(kParameter_OutputGain);
    addAndMakeVisible(mOutputputGainPanel.get());
}

CLMainPanel::~CLMainPanel()
{

}
*/

