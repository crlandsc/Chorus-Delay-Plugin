/*
  ==============================================================================

    CLTopPanel.h
    Created: 9 Dec 2022 5:58:12pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "CLPanelBase.h"

class CLTopPanel :
    public CLPanelBase,
    public Button::Listener,
    public ComboBox::Listener
{
public:

    CLTopPanel(ChorusDelayAudioProcessor* inProcessor);
    ~CLTopPanel();

    void paint(Graphics& g) override;

    void buttonClicked(Button* b) override;

    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;

private:

    void displaySaveAsPopup();

    void updatePresetComboBox();

    std::unique_ptr<ComboBox> mPresetDisplay;

    std::unique_ptr<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;

};