#include "beam.h"
#include "fire.h"
#include "state.h"
#include "pulse.h"

void setup()
{
  Serial.begin(9600);
  setupFastLED();
  setupState();
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
  case 5:
    pulse();
    break;
  default:
    break;
  }
  FastLED.show();
  stateLoop();
}
