/*
  ==============================================================================

    CLLookAndFeel.h
    Created: 20 Dec 2022 7:58:18am
    Author:  Chris

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CLInterfaceDefines.h"

class CLLookAndFeel
    : public LookAndFeel_V4
{
public:

    CLLookAndFeel()
    {
        // Store Image Assets
        mSliderImage = ImageCache::getFromMemory(BinaryData::Chorus_Delay_knob_png, BinaryData::Chorus_Delay_knob_pngSize);

        // Combobox colors
        setColour(ComboBox::backgroundColourId, CLColour_3);
        setColour(ComboBox::outlineColourId, CLColour_2);
        setColour(ComboBox::arrowColourId, CLColour_1);
        setColour(ComboBox::textColourId, CLColour_1);

        // Button text colors
        setColour(TextButton::buttonColourId, CLColour_1);
        setColour(TextButton::textColourOnId, CLColour_1);
        setColour(TextButton::textColourOffId, CLColour_1);
    }

    virtual ~CLLookAndFeel()
    {
    }


    // ----------------- Buttons ----------------- //
    Font getTextButtonFont(TextButton&, int buttonHeight) override
    {
        return font_1;
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        Colour fillColour;

        // Button hover & click colors
        if (isButtonDown) {
            fillColour = CLColour_6;
        }
        else if (isMouseOverButton) {
            fillColour = CLColour_3;
        }
        else
        {
            fillColour = CLColour_5;
        }

        // Create rectangle for buttons
        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        g.setColour(fillColour);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }

    // ----------------- Combo Boxes ----------------- //

    Font getLabelFont(Label& label) override
    {
        return font_1;
    }

    // Popup Menu colors & design
    void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const String& text, const String& shortcutKeyText,
        const Drawable* icon, const Colour* textColour) override
    {
        juce::Rectangle<int> r(area);

        Colour fillColour = isHighlighted ? CLColour_5 : CLColour_4;
        g.setColour(fillColour);

        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);

        Colour myTextColour = isTicked ? CLColour_7 : CLColour_1;
        g.setColour(myTextColour);
        g.setFont(font_1);
        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, Justification::left, 1);
    }

    // Combobox colors & design
    void drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds(0, 0, width, height);

        g.setColour(CLColour_3);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

        juce::Rectangle<int> arrow(width - 30, 0, 20, height);

        Path path;

        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);

        Colour arrowColour = box.findColour(ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColour);
        g.strokePath(path, PathStrokeType(2.0f));
    }


    // ----------------- Sliders ----------------- //
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth(); // determines number of frame within png (i.e. num steps)
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1)); // determines which frame to use

        const float radius = jmin(width * 0.5, height * 0.5); // smaller of 2 values
        const float centerX = x + (0.5 * width);
        const float centerY = y + (0.5 * height);
        const float rx = centerX - radius;
        const float ry = centerY - radius;

        g.drawImage(
            mSliderImage,
            rx,
            ry,
            2 * radius,
            2 * radius,
            0,
            frameIndex * mSliderImage.getWidth(),
            mSliderImage.getWidth(),
            mSliderImage.getWidth());
    }


private:

    Image mSliderImage;

};