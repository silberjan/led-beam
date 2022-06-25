#include "../common.h"

void bounce()
{
  uint8_t x = beat8(BPM, taps[0]);
  uint8_t pos = map(cubicwave8(x), 0, 255, 0, segmentLength - 1);
  pixelOnSegment(pos);
  fadeToBlackBy(leds, NUM_LEDS, 6);
}