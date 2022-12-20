/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "CLInterfaceDefines.h"
#include "CLLookAndFeel.h"

//==============================================================================
ChorusDelayAudioProcessorEditor::ChorusDelayAudioProcessorEditor(ChorusDelayAudioProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (
        MAIN_PANEL_WIDTH,
        MAIN_PANEL_HEIGHT);

    mMainPanel = std::make_unique<CLMainPanel>(&audioProcessor); // editor has refernce to processor, not pointer
    mMainPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMainPanel.get());

    mLookAndFeel = std::make_unique<CLLookAndFeel>();
    setLookAndFeel(mLookAndFeel.get()); // set look and feel

    LookAndFeel::setDefaultLookAndFeel(mLookAndFeel.get()); // set default look and feel to cover everything

    mBackgroundImage =
        ImageCache::getFromMemory(BinaryData::Chorus_Delay_bg_png, BinaryData::Chorus_Delay_bg_pngSize);
}

ChorusDelayAudioProcessorEditor::~ChorusDelayAudioProcessorEditor()
{
}

//==============================================================================
void ChorusDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImage(mBackgroundImage, getLocalBounds().toFloat());
}

void ChorusDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
