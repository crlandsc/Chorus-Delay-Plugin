/*
  ==============================================================================

    CLTopPanel.cpp
    Created: 9 Dec 2022 5:58:12pm
    Author:  Chris

  ==============================================================================
*/

#include "CLTopPanel.h"

CLTopPanel::CLTopPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

CLTopPanel::~CLTopPanel()
{

}

void CLTopPanel::paint(Graphics& g)
{
    CLPanelBase::paint(g);

    g.drawFittedText("Chorus / Delay", 0, 0, getWidth() - 10, getHeight(), Justification::centredRight, 1);
}
