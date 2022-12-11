/*
  ==============================================================================

    CLFxPanel.cpp
    Created: 9 Dec 2022 5:57:43pm
    Author:  Chris

  ==============================================================================
*/

#include "CLFxPanel.h"

CLFxPanel::CLFxPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor),
    mStyle (kCLFxPanelStyle_Delay) // initialize as a delay
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
}

CLFxPanel::~CLFxPanel()
{
}

void CLFxPanel::paint(Graphics& g)
{
    CLPanelBase::paint(g);

    switch (mStyle)
    {
    case(kCLFxPanelStyle_Delay): {

        g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
    } break;

    case(kCLFxPanelStyle_Chorus): {

        g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
    } break;

    default: // If not initialized correctly, this case will default to throw error.
    case(kCLFxPanelStyle_TotalNumStyles): {

        // This shouldn't ever happen
        g.drawFittedText("NO NO NO!", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
        jassertfalse; // JUCE macro to stop debugging at this point whenever this line is read
    } break;
    }
}

void CLFxPanel::setFxPanelStyle(CLFxPanelStyle inStyle)
{
    mStyle = inStyle;
}
