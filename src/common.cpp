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

uint16_t noise_x;
uint16_t noise_y;

void colorNoise()
{
  noise_x = millis() / 5;
  noise_y = beatsin8(10, 10, 30);
  uint8_t noise = inoise8(noise_x, noise_y);
  hue = map(noise, 50, 190, 0, 255);
}