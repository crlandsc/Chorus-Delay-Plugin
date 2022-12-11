/*
  ==============================================================================

    CLGainPanel.h
    Created: 9 Dec 2022 5:57:52pm
    Author:  Chris

  ==============================================================================
*/


#pragma once

#include "CLPanelBase.h"
#include "CLParameterSlider.h"

class CLGainPanel :
    public CLPanelBase
{
public:

    CLGainPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLGainPanel();

    void setParameterID(int inParameterID);

private:

    std::unique_ptr<CLParameterSlider> mGainSlider;

};


/*
#pragma once

#include "CLPanelBase.h"
#include "CLParameterSlider.h"

class CLGainPanel
    : public CLPanelBase
{
public:
    CLGainPanel(ChorusDelayAudioProcessor* processor);
    ~CLGainPanel();

    // component override
    void paint(Graphics& g) override;

    void setParameterID(int inParameterID);

private:

    std::unique_ptr<CLParameterSlider> mGain;
};
*/
