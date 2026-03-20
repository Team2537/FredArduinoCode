#include <Adafruit_NeoPixel.h>

#define PIN 3
#define NUM_OF_LEDS 56

Adafruit_NeoPixel strip = Adafruit_NeoPixel(56, PIN, NEO_GRB + NEO_KHZ800);


int randomNumber;
int red[56];
int green[56];
int blue[56];
  int sensorPin = A0;
  int sensorValue = 0;
  int select = 0;
  int i,j;
  int element[8][3];


void setup() {
  // put your setup code here, to run once:
   strip.begin();
  strip.show(); // Initialize all pixels to 'off'


 randomSeed(analogRead(A1));
}

boolean check(){
  boolean change = false;
  int sensorValue=analogRead(sensorPin);
  if (sensorValue < 512) {select++; change = true;}
  if (select > 4) select = 0;
  return change;
}



void clearStrip(){
  for (int i = 0; i < NUM_OF_LEDS; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void greenChaserTask(int i){
  int chaser_len = 5;

  strip.setPixelColor(i, 0, 125, 0);
  int prev_led;
  if (i < chaser_len) {
    prev_led = NUM_OF_LEDS - chaser_len + i;
  } else {
    prev_led = i - chaser_len;
  }

  strip.setPixelColor(prev_led, 0, 0, 0);
  strip.setPixelColor(i, 0, 125, 0);
  strip.setBrightness(140);
  strip.show();
}

void randomLightsTask(int i){
  if (i == 0){
    for (int r = 0; r < 56; r++) {
     red[r] = random(255);
    }

    for (int g = 0; g < 56; g++) {
     green[g] = random(255);
    }

    for (int b = 0; b < 56; b++) {
     blue[b] = random(255);
    }
  }
  strip.setPixelColor(i, red[i], green[i], blue[i]);

  for (int r = 0; r < 56; r++) {
     red[r] -= 4;
  }
          
  for (int g = 0; g < 56; g++) {
     green[g] -= 4;
  }
          
  for (int b = 0; b < 56; b++) {
     blue[b] -= 4;
  }
          
  strip.setBrightness(140);
  strip.show();  
}

void colorBandTask(int i, int r, int g, int b){
    strip.setPixelColor(i, r, g, b);
    strip.setBrightness(140);
    strip.show();
}

void greenBandTask(int i){
  colorBandTask(i, 0, 255, 0);
}

void redBandTask(int i){
  colorBandTask(i, 255, 0, 0);
}

void blueBandTask(int i){
  colorBandTask(i, 0, 0, 255);
}


void loop() {
  // put your main code here, to run repeatedly:

  /* Read Sensor 
  Sensor value will be 1023 when open,
  will drop to 78 when blocked
  When sensor is blocked, advance slection by 1*/
  
  /* ALL GREEN */

  for (i = 0; i < NUM_OF_LEDS; i ++){
    if (select == 0)      greenChaserTask(i);
    else if (select == 1) randomLightsTask(i);
    else if (select == 2) greenBandTask(i);
    else if (select == 3) blueBandTask(i);
    else if (select == 4) redBandTask(i);
    if (check()) {clearStrip(); break;}
    delay(10);
   }
  delay(500);
  }
