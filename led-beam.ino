#include "src/common.h"
#include "src/state.h"

#include "src/effects/fire.h"
#include "src/effects/strobe.h"
#include "src/effects/beacon.h"
#include "src/effects/torch.h"
#include "src/effects/lighthouse.h"
#include "src/effects/bounce.h"
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
    lighthouse();
    break;
  case 1:
    torch();
    break;
  case 2:
    fire();
    break;
  case 3:
    bounce();
    break;
  case 4:
    strobe();
    break;
  case 5:
    beacon();
    break;
  case 6:
    colorFlash();
    break;
  case 7:
    sparkle();
  default:
    break;
  }
  if (dynamicColor)
  {
    dynamicColorLoop();
  }
  FastLED.show();
  stateLoop();
}
