/*
  ==============================================================================

    CLInterfaceDefines.h
    Created: 9 Dec 2022 6:13:32pm
    Author:  Chris

  ==============================================================================
*/

#pragma once

#define MAIN_PANEL_WIDTH                750
#define MAIN_PANEL_HEIGHT               300

#define TOP_PANEL_WIDTH                 MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT                45

#define GAIN_PANEL_WIDTH                100
#define GAIN_PANEL_HEIGHT               MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT

#define CENTER_PANEL_WIDTH              MAIN_PANEL_WIDTH - (2 * GAIN_PANEL_WIDTH)
#define CENTER_PANEL_HEIGHT             GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH     CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT    35

#define FX_PANEL_WIDTH                  CENTER_PANEL_WIDTH
#define FX_PANEL_HEIGHT                 CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT
