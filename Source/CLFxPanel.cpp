/*
  ==============================================================================

    CLFxPanel.cpp
    Created: 9 Dec 2022 5:57:43pm
    Author:  Chris

  ==============================================================================
*/

#include "CLFxPanel.h"

#include "CLParameters.h"
#include "CLHelperFunctions.h"

CLFxPanel::CLFxPanel(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
    //mStyle (kCLFxPanelStyle_Delay) // initialize as a delay
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);

    const int currentStyle = (int)mProcessor->getParameter(kParameter_Type); // Cast to an int
    setFxPanelStyle((CLFxPanelStyle)currentStyle); // can int to an enumerated list then assign
}

CLFxPanel::~CLFxPanel()
{
}

void CLFxPanel::paint(Graphics& g)
{
    CLPanelBase::paint(g);

    String label;

    switch (mStyle)
    {
    case(kCLFxPanelStyle_Delay): {
        label = "DELAY";
        //g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight() * 0.45, Justification::centred, 1);
    } break;

    case(kCLFxPanelStyle_Chorus): {
        label = "CHORUS";
        //g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight() * 0.45, Justification::centred, 1);
    } break;
    /*
    default: // If not initialized correctly, this case will default to throw error.
    case(kCLFxPanelStyle_TotalNumStyles): {
        // This shouldn't ever happen
        g.drawFittedText("NO NO NO!", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
        jassertfalse; // JUCE macro to stop debugging at this point whenever this line is read
    } break; */
    }

    g.setColour(CLColour_5);
    g.setFont(font_3);

    g.drawText(label, 0, 0, getWidth(), 80, Justification::centred);

    // Run pain routine on each slider - NEED TO IMPLEMENT JUCE'S LABEL CLASS
    for (int i = 0; i < mSliders.size(); i++) {
        paintComponentLabel(g, mSliders[i]);
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
        * SMART POINTER IMPLEMENTATION - DOES NOT WORK *
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
        // Implement with raw pointers (How to implement with smart pointers?)
        // --------------------------------------------------

        CLParameterSlider* time =
            new CLParameterSlider(
                mProcessor->parameters,
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
            new CLParameterSlider(
                mProcessor->parameters,
                CLParameterID[kParameter_WetDry],
                CLParameterLabel[kParameter_WetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        mSliders.add(wetdry);
        addAndMakeVisible(wetdry);
        x = x + (slider_size * 2);

    } break;

    case(kCLFxPanelStyle_Chorus):
    {

        /*
        * SMART POINTER IMPLEMENTATION - DOES NOT WORK *
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
        */

        // --------------------------------------------------
        // Implement with raw pointers (How to implement with smart pointers?)
        // --------------------------------------------------

        CLParameterSlider* rate =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_ModulationRate],
                CLParameterLabel[kParameter_ModulationRate]);
        rate->setBounds(x, y, slider_size, slider_size);
        mSliders.add(rate);
        addAndMakeVisible(rate);
        x = x + (slider_size * 2);

        CLParameterSlider* depth =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_ModulationDepth],
                CLParameterLabel[kParameter_ModulationDepth]);
        depth->setBounds(x, y, slider_size, slider_size);
        mSliders.add(depth);
        addAndMakeVisible(depth);
        x = x + (slider_size * 2);

        CLParameterSlider* wetdry =
            new CLParameterSlider(mProcessor->parameters,
                CLParameterID[kParameter_WetDry],
                CLParameterLabel[kParameter_WetDry]);
        wetdry->setBounds(x, y, slider_size, slider_size);
        mSliders.add(wetdry);
        addAndMakeVisible(wetdry);
        x = x + (slider_size * 2);

    } break;

    default: // If not initialized correctly, this case will default to throw error.
    case(kCLFxPanelStyle_TotalNumStyles): {

        // This shouldn't ever happen
        jassertfalse; // JUCE macro to stop debugging at this point whenever this line is read
    } break;
    }

    repaint(); // Repaint after style is switched
}

void CLFxPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{

    CLFxPanelStyle style = (CLFxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex(); // cast changed combobox to a style

    setFxPanelStyle(style); // set the "style" when the combo box has changed

}
