#include "../common.h"

#include "lighthouse.h"

uint16_t x;
uint16_t y;

void lighthouse()
{
  uint8_t x = beat8(BPM, taps[0]);
  uint8_t val_seg_1 = map(cubicwave8(x), 0, 255, 0, 192);
  uint8_t val_seg_2 = map(cubicwave8(x + 64), 0, 255, 0, 192);
  uint8_t val_seg_3 = map(cubicwave8(x + 128), 0, 255, 0, 192);
  uint8_t val_seg_4 = map(cubicwave8(x + 192), 0, 255, 0, 192);

  staticColor(CHSV(hue, sat, val_seg_1), 0, segmentLength - 1);
  staticColor(CHSV(hue, sat, val_seg_2), segmentLength, segmentLength * 2 - 1);
  staticColor(CHSV(hue, sat, val_seg_3), segmentLength * 2, segmentLength * 3 - 1);
  staticColor(CHSV(hue, sat, val_seg_4), segmentLength * 3, segmentLength * 4 - 1);
}
