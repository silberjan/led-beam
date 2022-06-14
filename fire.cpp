#include "fire.h"
#include "beam.h"

#define HEIGHT 12
#define WIDTH 4

/* Refresh rate. Higher makes for flickerier
   Recommend small values for small displays */
#define FPS 16
#define FPS_DELAY 1000 / FPS

CRGBPalette16 gPal = HeatColors_p;

void fire()
{
  random16_add_entropy(random()); // We chew a lot of entropy

  drawFire();

  FastLED.show();
  FastLED.delay(FPS_DELAY);
}

/* Rate of cooling. Play with to change fire from
   roaring (smaller values) to weak (larger values) */
#define COOLING 16

/* How hot is "hot"? Increase for brighter fire */
#define HOT 170
#define MAXDROP 70
#define MAXHOT HOT *HEIGHT

void drawFire()
{
  static unsigned int spark[WIDTH]; // base heat
  CRGB stack[WIDTH][HEIGHT];        // stacks that are cooler

  // 1. Generate sparks to re-heat
  for (int i = 0; i < WIDTH; i++)
  {
    if (spark[i] < HOT)
    {
      int base = HOT * 2;
      spark[i] = random16(base, MAXHOT);
    }
  }

  // 2. Cool all the sparks
  for (int i = 0; i < WIDTH; i++)
  {
    spark[i] = qsub8(spark[i], random8(0, COOLING));
  }

  // 3. Build the stack
  /*    This works on the idea that pixels are "cooler"
        as they get further from the spark at the bottom */
  for (int i = 0; i < WIDTH; i++)
  {
    unsigned int heat = constrain(spark[i], HOT / 2, MAXHOT);
    for (int j = 0; j < HEIGHT; j++)
    {
      /* Calculate the color on the palette from how hot this
         pixel is */
      byte index = constrain(heat, 0, HOT);
      stack[i][j] = ColorFromPalette(gPal, index);

      /* The next higher pixel will be "cooler", so calculate
         the drop */
      unsigned int drop = random8(0, MAXDROP);
      if (drop > heat)
        heat = 0; // avoid wrap-arounds from going "negative"
      else
        heat -= drop;

      heat = constrain(heat, 0, MAXHOT);
    }
  }

  // 4. map stacks to led array
  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < HEIGHT; j++)
    {
      if (i % 2 == 0)
      {
        // even column
        leds[HEIGHT * i + j] = stack[i][j];
      }
      else
      {
        // odd column
        leds[HEIGHT * (i + 1) - 1 - j] = stack[i][j];
      }
    }
  }
}