/*
  ==============================================================================

    CLCenterPanelMenuBar.cpp
    Created: 9 Dec 2022 5:57:27pm
    Author:  Chris

  ==============================================================================
*/

#include "CLCenterPanelMenuBar.h"

CLCenterPanelMenuBar::CLCenterPanelMenuBar(ChorusDelayAudioProcessor* inProcessor) :
    CLPanelBase(inProcessor)
{
    setSize(
        CENTER_PANEL_MENU_BAR_WIDTH,
        CENTER_PANEL_MENU_BAR_HEIGHT);

    const int width = 85;

    mFxTypeComboBox =
        std::make_unique<CLParameterComboBox>(mProcessor->parameters, CLParameterID[kParameter_Type]);
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight()); // can only make calls to getWidth & getHeight because size has been set first
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kParameter_Type), dontSendNotification); // don't send an update message every time combo box is changed
    addAndMakeVisible(mFxTypeComboBox.get());
}

CLCenterPanelMenuBar::~CLCenterPanelMenuBar()
{

}

void CLCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}

void CLCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}
