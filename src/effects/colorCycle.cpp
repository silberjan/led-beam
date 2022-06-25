#include "../common.h"

void colorCycle()
{
  hue = beatsin8(5, 0U, 255U, taps[0]);
  staticColor(getHSV());
}