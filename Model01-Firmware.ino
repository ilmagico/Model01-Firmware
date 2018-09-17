// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// my customizations

// Support for LED Caps Lock mode
#include "Kaleidoscope-CapsLock.h"

// Support for OneShot keys
//#include "Kaleidoscope-OneShot.h"

// Light up one-shot keys when they're active
#include "Kaleidoscope-LED-ActiveModColor.h"

// Invert behavior of Shift for TOPSY(key)
#include <Kaleidoscope-TopsyTurvy.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum {
    MACRO_VERSION_INFO,
};



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum {
    PRIMARY,
    FUNCTION,
    ALTPRIMARY,
    ALTFUNCTION,
    NUMPAD,
    NUMPADFUN
}; // layers


// couple of missing aliases
#define Key_LessThan     LSHIFT(Key_Comma)
#define Key_GreaterThan  LSHIFT(Key_Period)
#define Key_QuestionMark LSHIFT(Key_Slash)
#define Key_Underscore   LSHIFT(Key_Minus)

#define Key_DQuote       LSHIFT(Key_Quote)
#define Key_Plus         LSHIFT(Key_Equals)
#define Key_Tilde        LSHIFT(Key_Backtick)

#define Key_LCurly       Key_LeftCurlyBracket
#define Key_RCurly       Key_RightCurlyBracket
#define Key_LBracket     Key_LeftBracket
#define Key_RBracket     Key_RightBracket

#undef Key_Mute // we want to use the Consumer_Mute version
#define Key_Mute         Consumer_Mute
#define Key_VolUp        Consumer_VolumeIncrement
#define Key_VolDn        Consumer_VolumeDecrement

#define Key_Left         Key_LeftArrow
#define Key_Right        Key_RightArrow
#define Key_Up           Key_UpArrow
#define Key_Down         Key_DownArrow

#define Key_PcApp        Key_PcApplication
/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED
  (Key_CapsLock, Key_1, Key_2, Key_3, Key_4, Key_5, TOPSY(LBracket),
   Key_Escape,   Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Delete,
   Key_Tab,      Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_Backtick, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Home,

   Key_Backspace, Key_LeftGui, Key_LeftShift, Key_LeftControl,
   ShiftToLayer(FUNCTION),

   TOPSY(RBracket),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_End,       Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,

   Key_RightControl, Key_RightShift, Key_LeftAlt, Key_Spacebar,
   ShiftToLayer(FUNCTION)),


  [FUNCTION] =  KEYMAP_STACKED
  (Key_Backslash,   TOPSY(1),         TOPSY(2),        TOPSY(3),      TOPSY(4),         TOPSY(5),   Key_LBracket,
   Key_Pipe,        Key_F1,           Key_F2,          Key_F3,        Key_F4,           Key_F5,     Key_LEDEffectNext,
   ___,             LCTRL(Key_Left),  LCTRL(Key_Down), LCTRL(Key_Up), LCTRL(Key_Right), Key_F11,
   TOPSY(Backtick), Key_PrintScreen,  Key_Insert,      ___,           ___,              Key_F12,    Key_PageDown,

   LCTRL(Key_Backspace), ___, ___, ___,
   ___,

   Key_RBracket,  TOPSY(6), TOPSY(7),   TOPSY(8),     TOPSY(9),        TOPSY(0),         Key_F11,
   ___,           Key_F6,   Key_F7,     Key_F8,       Key_F9,          Key_F10,          TOPSY(Equals),
                  Key_Left, Key_Down,   Key_Up,       Key_Right,       TOPSY(Semicolon), TOPSY(Quote),
   Key_PageUp,    ___,      ___,        TOPSY(Comma), TOPSY(Period),   TOPSY(Slash),     TOPSY(Minus),

   ___, ___, ___, Key_Enter,
   ___),


  [ALTPRIMARY] = KEYMAP_STACKED
  (Key_CapsLock, Key_1, Key_2, Key_3, Key_4, Key_5, TOPSY(LBracket),
   Key_Escape,   Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Left,
   Key_Tab,      Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_Backtick, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Right,

   Key_Backspace, Key_LeftGui, Key_LeftShift, Key_LeftControl,
   ShiftToLayer(ALTFUNCTION),

   TOPSY(RBracket), Key_6, Key_7, Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
   Key_Up,          Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                    Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   Key_Down,        Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,

   Key_RightControl, Key_RightShift, Key_LeftAlt, Key_Spacebar,
   ShiftToLayer(ALTFUNCTION)),


  [ALTFUNCTION] =  KEYMAP_STACKED
  (Key_Backslash,   TOPSY(1),         TOPSY(2),        TOPSY(3),      TOPSY(4),         TOPSY(5),   Key_LBracket,
   Key_Pipe,        Key_F1,           Key_F2,          Key_F3,        Key_F4,           Key_F5,     Key_Home,
   ___,             LCTRL(Key_Left),  LCTRL(Key_Down), LCTRL(Key_Up), LCTRL(Key_Right), Key_F11,
   TOPSY(Backtick), Key_PrintScreen,  Key_Insert,      ___,           ___,              Key_F12,    Key_End,

   Key_Delete, ___, ___, ___,
   ___,

   Key_RBracket,  TOPSY(6), TOPSY(7),   TOPSY(8),     TOPSY(9),        TOPSY(0),         Key_F11,
   Key_PageUp,    Key_F6,   Key_F7,     Key_F8,       Key_F9,          Key_F10,          TOPSY(Equals),
                  Key_Left, Key_Down,   Key_Up,       Key_Right,       TOPSY(Semicolon), TOPSY(Quote),
   Key_PageDown,  Key_Enter, ___,        TOPSY(Comma), TOPSY(Period),   TOPSY(Slash),     TOPSY(Minus),

   ___, ___, ___, Key_Enter,
   ___),


  [NUMPAD] =  KEYMAP_STACKED
  (LockLayer(ALTPRIMARY), ___, ___, ___, ___, ___, ___,
   ___, ___, Key_mouseScrollUp, Key_mouseUp,   Key_mouseScrollDn, ___,               ___,
   ___, ___, Key_mouseL,        Key_mouseDn,   Key_mouseR,        Key_mouseScrollUp,
   ___, ___, Key_mouseBtnM,     Key_mouseBtnL, Key_mouseBtnR,     Key_mouseScrollDn, ___,

   ___, ___, ___, ___,
   ShiftToLayer(NUMPADFUN),

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ShiftToLayer(NUMPADFUN)),


  [NUMPADFUN] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, XXX,              Key_mouseScrollUp, XXX,              ___, ___,
   ___, ___, Key_mouseScrollL, Key_mouseScrollDn, Key_mouseScrollR, XXX,
   ___, ___, ___,              ___,               ___,              XXX, ___,

   ___, ___, ___, ___,
   ___,

   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___)
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidWhiteDim(80, 80, 80);
static kaleidoscope::LEDSolidColor solidWhiteBright(160, 160, 160);
// static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
// static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
// static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
// static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
// static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
// static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
// static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE
};

/** A tiny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  //.keys = { R3C6, R2C6, R3C7 }
                  // Prog + Left Fn + Right Fn + Num
                  { R0C0, R3C6, R3C9, R0C15 },
                 });

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
  TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  // LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidWhiteDim, solidWhiteBright,
  // solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  // LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  // AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  // StalkerEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The CapsLock plugin lights up CAPS LOCK mode in a similar way to numpad mode
  CapsLock,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // Enable one-shot/sticky keys
  // OneShot,

  // Use this to light up oneshot and sticky keys when active
  ActiveModColorEffect,

  // invert the behavior of shift for some keys
  TopsyTurvy

);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Turn off boot effect quickly
  BootGreetingEffect.timeout = 2000;

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // OneShot keys will light up in this color
  ActiveModColorEffect.highlight_color = CRGB(0x00, 0xff, 0xff);

  // Tune mouse acceleration
  MouseKeys.accelSpeed = 1;
  MouseKeys.decelSpeed = 4;
  MouseKeys.accelDelay = 13;
  MouseKeys.setSpeedLimit(130);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
  if (Layer.isOn(ALTPRIMARY)) {
    LEDControl.setCrgbAt(0, 0, CRGB(255, 0, 255));
  } else {
    LEDControl.refreshAt(0, 0);
  }
}
