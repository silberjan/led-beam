#include "../common.h"

void torch()
{
  uint8_t pos = map(beat8(BPM, taps[0]), 0, 255, 0, segmentLength);
  uint8_t off = segmentLength / 2;
  pixelOnSegment(pos % segmentLength);
  pixelOnSegment((pos + off) % segmentLength);
  fadeToBlackBy(leds, NUM_LEDS, 48);
}