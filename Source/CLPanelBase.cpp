/*
  ==============================================================================

    CLPanelBase.cpp
    Created: 9 Dec 2022 5:56:19pm
    Author:  Chris

  ==============================================================================
*/

#include "CLPanelBase.h"


CLPanelBase::CLPanelBase(ChorusDelayAudioProcessor* inProcessor) :
    mProcessor(inProcessor)
{

}

CLPanelBase::~CLPanelBase()
{

}

void CLPanelBase::paint(Graphics& g)
{
    g.setColour(Colours::whitesmoke);
    g.fillAll(); // set background color

    g.setColour(Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight()); // draw a rectangle at the boundary
}
