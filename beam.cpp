#include "beam.h"

CRGB leds[NUM_LEDS];
CRGB led_rgb = CRGB::Blue;
uint8_t hue = 0;
uint8_t sat = 255;
uint8_t val = 255;

uint8_t segmentLength = 12;

void setupFastLED()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(192);
  FastLED.show();
}

uint16_t x;
uint16_t y;

void colorNoise()
{
  x = millis() / 5;
  y = beatsin8(10, 10, 30);
  uint8_t noise = inoise8(x, y);
  hue = map(noise, 50, 190, 0, 255);
  led_rgb = CHSV(hue, sat, val);
}

void staticColor(CRGB color = led_rgb, uint8_t start = 0U, uint8_t end = NUM_LEDS - 1)
{
  for (int i = start; i <= end; i++)
  {
    leds[i] = color;
  }
}

void lightsaber()
{
  uint8_t pos1 = map(beat8(60, 0), 0, 255, 0, segmentLength - 1);
  uint8_t pos2 = segmentLength * 2 - 1 - pos1;
  uint8_t pos3 = segmentLength * 2 + pos1;
  uint8_t pos4 = segmentLength * 4 - 1 - pos1;
  leds[pos1] = led_rgb;
  leds[pos2] = led_rgb;
  leds[pos3] = led_rgb;
  leds[pos4] = led_rgb;
  fadeToBlackBy(leds, NUM_LEDS, 1);
}

void lighthouse()
{
  uint8_t x = millis() * 0.25;
  uint8_t val_seg_1 = map(cubicwave8(x), 0, 255, 0, 192);
  uint8_t val_seg_2 = map(cubicwave8(x + 64), 0, 255, 0, 192);
  uint8_t val_seg_3 = map(cubicwave8(x + 128), 0, 255, 0, 192);
  uint8_t val_seg_4 = map(cubicwave8(x + 192), 0, 255, 0, 192);
  uint8_t l_hue = 24;
  staticColor(CHSV(l_hue, sat, val_seg_1), 0, segmentLength - 1);
  staticColor(CHSV(l_hue, sat, val_seg_2), segmentLength, segmentLength * 2 - 1);
  staticColor(CHSV(l_hue, sat, val_seg_3), segmentLength * 2, segmentLength * 3 - 1);
  staticColor(CHSV(l_hue, sat, val_seg_4), segmentLength * 3, segmentLength * 4 - 1);
}

void torch()
{
  // blur1d(leds, NUM_LEDS, 0.5);
  uint8_t x = millis() / 50;
  uint8_t n = 4;
  uint8_t o = segmentLength / n;
  for (int i = 0; i <= n; i++)
  {
    pixelOnSegment((x + i * o) % segmentLength);
  }

  fadeToBlackBy(leds, NUM_LEDS, 48);
}

void pixelOnSegment(uint8_t x)
{
  leds[x] = led_rgb;
  leds[segmentLength * 2 - 1 - x] = led_rgb;
  leds[x + segmentLength * 2] = led_rgb;
  leds[segmentLength * 4 - 1 - x] = led_rgb;
}

void bounce()
{
  uint8_t x = millis() * 0.125;
  uint8_t pos = map(cubicwave8(x), 0, 255, 0, segmentLength - 1);
  pixelOnSegment(pos);
  fadeToBlackBy(leds, NUM_LEDS, 6);
}