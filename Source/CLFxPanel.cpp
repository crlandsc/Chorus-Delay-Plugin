/*
  ==============================================================================

    CLFxPanel.cpp
    Created: 9 Dec 2022 5:57:43pm
    Author:  Chris

  ==============================================================================
*/

#include "CLFxPanel.h"

#include "CLParameters.h"

CLFxPanel::CLFxPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
    //mStyle (kCLFxPanelStyle_Delay) // initialize as a delay
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);

    setFxPanelStyle(kCLFxPanelStyle_Delay);
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

    mSliders.clear();

    const int slider_size = 56;
    int x = 130; // will be updated (don't make const)
    int y = (getHeight() * 0.5) - (slider_size * 0.5); // will be updated (don't make const)

    switch (mStyle)
    {
    case(kCLFxPanelStyle_Delay):
    {
        /*
        // Construct Delay Time Slider
        std::unique_ptr<CLParameterSlider> time =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_DelayTime],
                CLParameterLabel[kParameter_DelayTime]);
        time->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(time.get()); // Add to parent and make visible
        mSliders.add(time.get()); // Add to array
        x = x + (slider_size * 2); // Increment position of each knob as it is applied (using same x value)

        // Construct Delay Feedback Slider
        std::unique_ptr<CLParameterSlider> feedback =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_DelayFeedback],
                CLParameterLabel[kParameter_DelayFeedback]);
        feedback->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(feedback.get());
        mSliders.add(feedback.get());
        x = x + (slider_size * 2);

        // Construct Delay Wet/Dry Slider
        std::unique_ptr<CLParameterSlider> wetdry =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_DelayWetDry],
                CLParameterLabel[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(wetdry.get());
        mSliders.add(wetdry.get());
        x = x + (slider_size * 2);

        */


        // --------------------------------------------------
        // Implement with raw pointers (is these an acceptable way to use smart pointers)
        // --------------------------------------------------

        CLParameterSlider* time =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_DelayTime],
                CLParameterLabel[kParameter_DelayTime]);
        time->setBounds(x, y, slider_size, slider_size);
        mSliders.add(time);
        addAndMakeVisible(time);
        x = x + (slider_size * 2);

        CLParameterSlider* feedback =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_DelayFeedback],
                CLParameterLabel[kParameter_DelayFeedback]);
        feedback->setBounds(x, y, slider_size, slider_size);
        mSliders.add(feedback);
        addAndMakeVisible(feedback);
        x = x + (slider_size * 2);

        CLParameterSlider* wetdry =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_DelayWetDry],
                CLParameterLabel[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        mSliders.add(wetdry);
        addAndMakeVisible(wetdry);
        x = x + (slider_size * 2);





    } break;

    case(kCLFxPanelStyle_Chorus):
    {

        // -------------- [NEED TO IMPLEMENT WITH RAW POINTERS] --------------

        // Construct Chorus Rate Slider
        std::unique_ptr<CLParameterSlider> rate =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_ModulationRate],
                CLParameterLabel[kParameter_ModulationRate]);
        rate->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(rate.get());
        mSliders.add(rate.get());
        x = x + (slider_size * 2);

        // Construct Chorus Depth Slider
        std::unique_ptr<CLParameterSlider> depth =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_ModulationDepth],
                CLParameterLabel[kParameter_ModulationDepth]);
        depth->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(depth.get());
        mSliders.add(depth.get());
        x = x + (slider_size * 2);

        // Construct Chorus Wet/Dry Slider
        std::unique_ptr<CLParameterSlider> wetdry =
            std::make_unique<CLParameterSlider>(mProcessor->parameters,
                CLParameterID[kParameter_DelayWetDry],
                CLParameterLabel[kParameter_DelayWetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        addAndMakeVisible(wetdry.get());
        mSliders.add(wetdry.get());
        x = x + (slider_size * 2);

    } break;

    //default: // If not initialized correctly, this case will default to throw error.
    //case(kCLFxPanelStyle_TotalNumStyles): {

    //    // This shouldn't ever happen
    //    jassertfalse; // JUCE macro to stop debugging at this point whenever this line is read
    //} break;
    }

}
