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
    setSize(TOP_PANEL_WIDTH,
            TOP_PANEL_HEIGHT);

    int button_x = 15;
    int button_y = 10;
    int button_w = 55;
    int button_h = 25;

    mNewPreset = std::make_unique<TextButton>();
    mNewPreset->setButtonText("NEW");
    mNewPreset->setBounds(button_x, button_y, button_w, button_h);
    mNewPreset->addListener(this);
    addAndMakeVisible(mNewPreset.get());
    button_x = button_x + button_w;

    mSavePreset = std::make_unique<TextButton>();
    mSavePreset->setButtonText("SAVE");
    mSavePreset->setBounds(button_x, button_y, button_w, button_h);
    mSavePreset->addListener(this);
    addAndMakeVisible(mSavePreset.get());
    button_x = button_x + button_w;

    mSaveAsPreset = std::make_unique<TextButton>();
    mSaveAsPreset->setButtonText("SAVE AS");
    mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
    mSaveAsPreset->addListener(this);
    addAndMakeVisible(mSaveAsPreset.get());
    button_x = button_x + button_w;

    const int comboBox_w = 200;
    const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;

    mPresetDisplay = std::make_unique<ComboBox>();
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(mPresetDisplay.get());

    updatePresetComboBox();

}

CLTopPanel::~CLTopPanel()
{

}

void CLTopPanel::paint(Graphics& g)
{
    CLPanelBase::paint(g);

    g.drawFittedText("Chorus / Delay", 0, 0, getWidth() - 10, getHeight(), Justification::centredRight, 1);
}

void CLTopPanel::buttonClicked(Button* b)
{
    CLPresetManager* presetManager = mProcessor->getPresetManager();
    if (b == mNewPreset.get()) {
        presetManager->createNewPreset();
        updatePresetComboBox(); // update combobox when "New" is selected
    }
    else if (b == mSavePreset.get()) {
        presetManager->savePreset();
    }
    else if (b == mSaveAsPreset.get()) {
        displaySaveAsPopup();
    }
}

void CLTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == mPresetDisplay.get()) {
        CLPresetManager* presetManager = mProcessor->getPresetManager();

        const int index = mPresetDisplay->getSelectedItemIndex();
        presetManager->loadPreset(index);
    }
}

void CLTopPanel::displaySaveAsPopup()
{
    CLPresetManager* presetManager = mProcessor->getPresetManager();

    String currentPresetName = presetManager->getCurrentPresetName();

    AlertWindow window("Save As", "Please enter a name for your preset", AlertWindow::NoIcon);

    window.centreAroundComponent(this, getWidth(), getHeight()); // center in the top panel

    window.addTextEditor("presetName", currentPresetName, "Preset name: ");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);

    // If confirmed selected, then save preset
    if (window.runModalLoop()) {
        String presetName = window.getTextEditor("presetName")->getText();
        presetManager->saveAsPreset(presetName);

        updatePresetComboBox(); // Update combobox display
    }
}

void CLTopPanel::updatePresetComboBox()
{
    CLPresetManager* presetManager = mProcessor->getPresetManager();
    String presetName = presetManager->getCurrentPresetName();

    mPresetDisplay->clear(dontSendNotification); // clear combo box (don't send notification

    const int numPresets = presetManager->getNumberOfPresets(); // get number of presets

    // Iterate through number of presets and add them to the combobox
    for (int i = 0; i < numPresets; i++) {
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i + 1));
    }

    mPresetDisplay->setText(presetManager->getCurrentPresetName()); // Update combobox text to display currently loaded preset name

}
