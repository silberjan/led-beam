#include "../common.h"

void torch()
{
  // blur1d(leds, NUM_LEDS, 0.5);
  uint8_t x = millis() / 50;
  uint8_t n = 4;
  uint8_t o = segmentLength / n;
  for (int i = 0; i <= n; i++)
  {
    uint8_t segmentPos = (x + i * o) % segmentLength;
    pixelOnSegment(segmentPos);
  }

  fadeToBlackBy(leds, NUM_LEDS, 48);
}