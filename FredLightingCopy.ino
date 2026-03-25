// Final "Halt on Press" Version - 3-19-2026
#include <Adafruit_NeoPixel.h>

#define PIN 3
#define NUM_OF_LEDS 56

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int red[56], green[56], blue[56];
int sensorPin = A0;
int select = 0;

void setup() {
  strip.begin();
  strip.setBrightness(140);
  strip.show(); 
  randomSeed(analogRead(A1));
}

// This function now only handles the MODE SWAP after release
boolean check() {
  if (analogRead(sensorPin) < 512) {
    // Wait until released
    while (analogRead(sensorPin) < 512) {
      delay(10); 
    }
    
    // Advance mode
    select++;
    if (select > 4) select = 0;
    
    delay(50); // Small debounce
    return true; 
  }
  return false;
}

void clearStrip() {
  for (int k = 0; k < NUM_OF_LEDS; k++) {
    strip.setPixelColor(k, 0, 0, 0);
  }
  strip.show();
}

void greenChaserTask(int i) {
  int chaser_len = 5;
  strip.setPixelColor(i, 0, 125, 0);
  // Modulo prevents negative index crashes
  strip.setPixelColor((i - chaser_len + NUM_OF_LEDS) % NUM_OF_LEDS, 0, 0, 0);
  strip.show();
}

void randomLightsTask(int i) {
  if (i == 0) {
    for (int r = 0; r < 56; r++) {
      red[r] = random(255);
      green[r] = random(255);
      blue[r] = random(255);
    }
  }
  strip.setPixelColor(i, red[i], green[i], blue[i]);
  for (int k = 0; k < 56; k++) {
    if(red[k] > 4) red[k] -= 4;
    if(green[k] > 4) green[k] -= 4;
    if(blue[k] > 4) blue[k] -= 4;
  }
  strip.show();  
}

void colorBandTask(int i, int r, int g, int b) {
  strip.setPixelColor(i, r, g, b);
  strip.show();
}

void loop() {
  for (int i = 0; i < NUM_OF_LEDS; i++) {
    
    // 1. Check for the press (and hold here)
    if (check()) {
      clearStrip();
      break; // Exit 'for' loop to start next animation
    }

    // 2. Run animations ONLY if sensor isn't being held
    if (select == 0)      greenChaserTask(i);
    else if (select == 1) randomLightsTask(i);
    else if (select == 2) colorBandTask(i, 0, 255, 0); // Green
    else if (select == 3) colorBandTask(i, 0, 0, 255); // Blue
    else if (select == 4) colorBandTask(i, 255, 0, 0); // Red
    
    delay(18);
  }
}
