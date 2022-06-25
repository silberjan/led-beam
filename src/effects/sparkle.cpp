#include "../common.h"

void sparkle()
{
  if (random8() < BPM)
  {
    leds[random16(NUM_LEDS)] = CRGB::White;
  }
  fadeToBlackBy(leds, NUM_LEDS, 10);
}