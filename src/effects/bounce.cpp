#include "../common.h"

void bounce()
{
  uint8_t pos = beatsin8(BPM / 2, 0, segmentLength);
  pixelOnSegment(pos);
  fadeToBlackBy(leds, NUM_LEDS, 8);
}