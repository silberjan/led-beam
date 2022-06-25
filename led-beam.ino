#include "src/common.h"
#include "src/state.h"

#include "src/effects/fire.h"
#include "src/effects/pulse.h"
#include "src/effects/beacon.h"
#include "src/effects/torch.h"
#include "src/effects/lighthouse.h"
#include "src/effects/bounce.h"

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
    beacon();
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
