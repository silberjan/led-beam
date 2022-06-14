#pragma once

#define FASTLED_INTERNAL // Suppress build banner
#include <FastLED.h>

#define NUM_LEDS 48
#define LED_PIN 2

extern CRGB leds[];
extern CRGB led_rgb;
extern uint8_t segmentLength;

void staticColor(CRGB color, uint8_t start, uint8_t end);
void setupFastLED();
void lightsaber();
void lighthouse();
void torch();
void colorNoise();
void staticColor();
void pixelOnSegment(uint8_t x);
void bounce();
