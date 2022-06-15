#define FASTLED_INTERNAL // Suppress build banner
#include <FastLED.h>
#include "state.h"
#include "beam.h"

#include "pulse.h"

uint8_t lastBeat = 0;
uint8_t pulseHue = 0;

void pulse()
{
  uint8_t val = squarewave8(beatsin8(BPM, 0, 255, taps[0]), 8);

  if (lastBeat != beat)
  {
    pulseHue = random(0, 255);
    lastBeat = beat;
  }
  staticColor(CHSV(pulseHue, 255, val), 0, NUM_LEDS - 1);
}