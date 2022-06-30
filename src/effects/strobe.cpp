#include "../state.h"
#include "../common.h"

#include "strobe.h"

void strobe()
{
  uint8_t val = squarewave8(beatsin8(BPM, 0, 255, taps[0]), 8);

  if (lastBeat != beat)
  {
    lastBeat = beat;
  }
  staticColor(CHSV(hue, 255, val));
}