#include "../common.h"

void beacon()
{
  uint8_t pos1 = map(beat8(BPM, taps[0]), 0, 255, 0, segmentLength - 1);
  uint8_t pos2 = segmentLength * 2 - 1 - pos1;
  uint8_t pos3 = segmentLength * 2 + pos1;
  uint8_t pos4 = segmentLength * 4 - 1 - pos1;
  leds[pos1] = getHSV();
  leds[pos2] = getHSV();
  leds[pos3] = getHSV();
  leds[pos4] = getHSV();
  fadeToBlackBy(leds, NUM_LEDS, BPM / 30);
}