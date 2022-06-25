#include "src/common.h"
#include "src/state.h"

#include "src/effects/fire.h"
#include "src/effects/pulse.h"
#include "src/effects/beacon.h"
#include "src/effects/torch.h"
#include "src/effects/lighthouse.h"
#include "src/effects/bounce.h"
#include "src/effects/colorCycle.h"
#include "src/effects/colorFlash.h"
#include "src/effects/sparkle.h"

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
    colorCycle();
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
  case 6:
    beacon();
    break;
  case 7:
    colorFlash();
    break;
  case 8:
    sparkle();
  default:
    break;
  }
  FastLED.show();
  stateLoop();
}
