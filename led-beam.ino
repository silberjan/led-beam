#include "beam.h"
#include "fire.h"
#include <OneButton.h>
#include <EEPROM.h>

uint8_t mode = 0;
OneButton btn;

void setup()
{
  Serial.begin(9600);
  setupFastLED();
  btn = OneButton(3, false, false);
  btn.attachClick(handleClick);
  EEPROM.get(0, mode);
}

void handleClick()
{
  mode = (mode + 1) % 5;
  EEPROM.update(0, mode);
  FastLED.clear(true);
}

void loop()
{
  switch (mode)
  {
  case 0:
    colorNoise();
    lightsaber();
    break;
  case 1:
    lighthouse();
    break;
  case 2:
    torch();
    break;
  case 3:
    fire();
    break;
  case 4:
    bounce();
    break;
  default:
    break;
  }
  FastLED.show();
  btn.tick();
}
