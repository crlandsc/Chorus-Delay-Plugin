/*
  ==============================================================================

    CLPanelBase.cpp
    Created: 9 Dec 2022 5:56:19pm
    Author:  Chris

  ==============================================================================
*/

#include "CLPanelBase.h"
#include "CLInterfaceDefines.h"


CLPanelBase::CLPanelBase(ChorusDelayAudioProcessor* inProcessor) :
    mProcessor(inProcessor)
{

}

CLPanelBase::~CLPanelBase()
{

}

void CLPanelBase::mouseEnter(const MouseEvent& event)
{
    repaint();
}

void CLPanelBase::mouseExit(const MouseEvent& event)
{
    repaint();
}

void CLPanelBase::paint(Graphics& g)
{
    // Mouse interactions using paint routines
    /* Not implemented currently, but can incorporate later */
    if (isMouseOver()) {
        //g.setColour(CLColour_3);
        //g.fillAll();
    }
    else {
        
    }

    // --- Depricated paint routine --- //
    /*
    g.setColour(Colours::purple);
    g.fillAll(); // set background color
    g.setColour(Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 4, 2); // draw a rectangle at the boundary (rounded)
    */
}
