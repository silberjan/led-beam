#pragma once

#define FASTLED_INTERNAL // Suppress build banner
#include <FastLED.h>

#include "state.h"

void staticColor(CHSV const &color, uint8_t start = 0U, uint8_t end = NUM_LEDS - 1);

void pixelOnSegment(uint8_t const &x);

void colorNoise();

CHSV getHSV();