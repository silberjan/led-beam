#include "../common.h"

uint8_t lastSt = 0;

void colorFlash()
{
  // sawtooth wave
  uint8_t st = beat8(BPM, taps[0]);

  // flash on beat, then fade
  val = map(st, 0, 255, 255, 32);

  // how many led should be on from center
  uint8_t cnt = map(st, 0, 255, segmentLength, 0);

  for (int i = 0; i < cnt / 2; i++)
  {
    uint8_t pxl1 = segmentLength / 2 + i;
    uint8_t pxl2 = segmentLength / 2 - i;
    pixelOnSegment(pxl1);
    pixelOnSegment(pxl2);
  }

  fadeToBlackBy(leds, NUM_LEDS, 8);
  lastSt = st;
}