#include "common.h"

void staticColor(CHSV const &color, uint8_t start, uint8_t end)
{
  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
}

void pixelOnSegment(uint8_t const &x)
{
  leds[x] = getHSV();
  leds[segmentLength * 2 - 1 - x] = getHSV();
  leds[x + segmentLength * 2] = getHSV();
  leds[segmentLength * 4 - 1 - x] = getHSV();
}
