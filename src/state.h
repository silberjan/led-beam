#pragma once

#define FASTLED_INTERNAL // Suppress build banner
#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS 48
#define LED_PIN 2

extern CRGB leds[];
extern uint8_t segmentLength;

extern uint8_t BPM;
extern uint8_t mode;
extern uint8_t beat;

extern uint8_t lastBeat;

extern uint8_t hue;
extern uint8_t sat;
extern uint8_t val;

extern bool dynamicColor;

#define TAP_BUFFER_SIZE 6
extern unsigned long taps[];

void setupFastLED();
uint8_t getBpmDelay();
void setupState();
void changeMode();
void tapBpm();
void stateLoop();
void changeColor();
void changeColorMode();
void dynamicColorLoop();