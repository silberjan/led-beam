#define FASTLED_INTERNAL // Suppress build banner

#include <OneButton.h>
#include <EEPROM.h>

#include "state.h"

uint8_t mode = 0;
uint8_t BPM = 120;
uint8_t beat = 0;

uint8_t lastBeat = 0;

CRGB leds[NUM_LEDS];
CRGB led_rgb = CRGB::Blue;

uint8_t hue = 0;
uint8_t sat = 255;
uint8_t val = 255;

uint8_t segmentLength = 12;

OneButton btn1;
OneButton btn2;

bool dynamicColor = false;

unsigned long taps[TAP_BUFFER_SIZE];

CHSV getHSV()
{
  return CHSV(hue, sat, val);
}

void setupFastLED()
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(192);
  FastLED.show();
}

void setupState()
{
  btn1 = OneButton(3, false, false);
  btn1.attachLongPressStart(changeMode);
  btn1.attachClick(tapBpm);
  btn2 = OneButton(4, false, false);
  btn2.attachClick(changeColor);
  btn2.attachLongPressStart(changeColorMode);
  EEPROM.get(0, mode);
}

void stateLoop()
{
  btn1.tick();
  btn2.tick();
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
    // Serial.println("Cleared taps");
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
      // Serial.print(taps[i] - taps[i + 1]);
      // Serial.print("ms ");
      summedTimes += taps[i] - taps[i + 1];
      numberOfTimes++;
    }
  }
  // Serial.println("");
  // Serial.print(summedTimes);
  // Serial.print(" ");
  // Serial.println(numberOfTimes);
  if (numberOfTimes > 1)
  {
    BPM = 60000 / ((float)summedTimes / numberOfTimes);
    // Serial.print("Avg delay: ");
    // Serial.print(summedTimes / numberOfTimes);
    // Serial.print("ms BPM: ");
    // Serial.println(BPM);
  }
}

void tapBpm()
{
  Serial.println("btn1");
  addTap(millis());
  determineBpm();
}

void changeColor()
{
  Serial.println("btn2");
  hue += 32;
}

void changeMode()
{
  mode = (mode + 1) % 8;
  val = 255;
  sat = 255;
  EEPROM.update(0, mode);
  FastLED.clear(true);
}

void changeColorMode()
{
  dynamicColor = !dynamicColor;
}

void dynamicColorLoop()
{
  if (beat > lastBeat)
  {
    // change color on next beat
    hue += 32;
  }
  lastBeat = beat;
}