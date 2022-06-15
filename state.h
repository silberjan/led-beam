#define FASTLED_INTERNAL // Suppress build banner
#include <FastLED.h>
#include <OneButton.h>

extern uint8_t BPM;
extern uint8_t mode;
extern uint8_t beat;

#define TAP_BUFFER_SIZE 6
extern unsigned long taps[TAP_BUFFER_SIZE];

uint8_t getBpmDelay();
void setupState();
void changeMode();
void tapBpm();
void stateLoop();