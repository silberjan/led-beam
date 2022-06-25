#define FASTLED_INTERNAL // Suppress build banner

#include <OneButton.h>
#include <EEPROM.h>

#include "state.h"

uint8_t mode = 0;
uint8_t BPM = 120;
uint8_t beat = 0;

CRGB leds[NUM_LEDS];
CRGB led_rgb = CRGB::Blue;

uint8_t hue = 0;
uint8_t sat = 255;
uint8_t val = 255;

uint8_t segmentLength = 12;

OneButton btn;

unsigned long taps[TAP_BUFFER_SIZE];

void setupFastLED()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(192);
  FastLED.show();
}

void setupState()
{
  btn = OneButton(3, false, false);
  btn.attachLongPressStart(changeMode);
  btn.attachClick(tapBpm);
  EEPROM.get(0, mode);
}

void stateLoop()
{
  btn.tick();
  beat = millis() / (60000 / BPM);
}

uint8_t getBpmDelay()
{
  return 1000 / BPM;
}

void addTap(unsigned long tap)
{
  if (taps[0] && tap - taps[0] > 5000)
  {
    memset(taps, 0, sizeof(taps));
    Serial.println("Cleared taps");
  }
  for (int i = TAP_BUFFER_SIZE - 1; i > 0; i--)
  {
    taps[i] = taps[i - 1];
  }
  taps[0] = tap;
}

void determineBpm()
{
  unsigned long summedTimes = 0;
  uint8_t numberOfTimes = 0;
  for (int i = 0; i < TAP_BUFFER_SIZE - 1; i++)
  {
    if (taps[i + 1])
    {
      Serial.print(taps[i] - taps[i + 1]);
      Serial.print("ms ");
      summedTimes += taps[i] - taps[i + 1];
      numberOfTimes++;
    }
  }
  Serial.println("");
  Serial.print(summedTimes);
  Serial.print(" ");
  Serial.println(numberOfTimes);
  if (numberOfTimes > 1)
  {
    BPM = 60000 / ((float)summedTimes / numberOfTimes);
    Serial.print("Avg delay: ");
    Serial.print(summedTimes / numberOfTimes);
    Serial.print("ms BPM: ");
    Serial.println(BPM);
  }
}

void tapBpm()
{
  addTap(millis());
  determineBpm();
}

void changeMode()
{
  mode = (mode + 1) % 6;
  EEPROM.update(0, mode);
  FastLED.clear(true);
}