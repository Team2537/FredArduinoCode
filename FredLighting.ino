#include <Adafruit_NeoPixel.h>

 #define PIN 3

 Adafruit_NeoPixel strip = Adafruit_NeoPixel(96, PIN, NEO_GRB + NEO_KHZ800);


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

void loop() {
  // put your main code here, to run repeatedly:

/* Read Sensor 
Sensor value will be 1023 when open,
will drop to 78 when blocked
When sensor is blocked, advance slection by 1*/

  int sensorValue=analogRead(sensorPin);
  if (sensorValue<512) select++;
  if (select>=5) select = 0;
  delay(500); //slow rate of response to prevent skipping //

/* ALL GREEN */
  if (select == 0){
     for(i=0;i<=56;i++){
     strip.setPixelColor(i, 0, 255, 0);
     
     strip.setBrightness(140);
     strip.show();
     delay(5);
     }
     delay(500);
  } /* End Select = 0 */

/* GREEN CHASER */
 if (select == 1){
   
     for(i=0;i<=51;i++){
     strip.setPixelColor(i, 0, 125, 0);
     strip.setPixelColor(i+1, 0, 125, 0);
     strip.setPixelColor(i+2, 0, 125, 0);
     strip.setPixelColor(i+3, 0, 125, 0);
     strip.setPixelColor(i+4, 0, 125, 0);
     strip.setBrightness(140);
     strip.show();
     delay(20);
     strip.setPixelColor(i, 0, 0, 0);
     }
    strip.setPixelColor(i+1, 0, 0, 0);
    strip.setPixelColor(i+2, 0, 0, 0);
    strip.setPixelColor(i+3, 0, 0, 0);
    strip.setPixelColor(i+4, 0, 0, 0);
    strip.show();
     //Now backward*//
    for(i=55;i>=4;i--){
     strip.setPixelColor(i, 0, 125, 0);
     strip.setPixelColor(i-1, 0, 125, 0);
     strip.setPixelColor(i-2, 0, 125, 0);
     strip.setPixelColor(i-3, 0, 125, 0);
     strip.setPixelColor(i-4, 0, 125, 0);
     strip.setBrightness(140);
     strip.show();
     delay(20);
     strip.setPixelColor(i, 0, 0, 0);
     }
    strip.setPixelColor(i-1, 0, 0, 0);
    strip.setPixelColor(i-2, 0, 0, 0);
    strip.setPixelColor(i-3, 0, 0, 0);
    strip.setPixelColor(i-4, 0, 0, 0);
     strip.show();
     
     delay(300);
  } /* End Select = 1 */


  
  if (select == 2){    
      int i = 0;
      boolean dir;
      
          for (int r = 0; r < 56; r++) {
               red[r] = random(255);
          }

          for (int g = 0; g < 56; g++) {
               green[g] = random(255);
          }

          for (int b = 0; b < 56; b++) {
               blue[b] = random(255);
          }
        for(i=0;i<=56;i++){
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
          delay(5); 
        }
    delay(500);
      }/*End of Marco's Code */
  /*End Select 1 */

//  Turn Red
  if (select == 3){
    for (int i = 0; i < 55; i++){
      strip.setPixelColor(i, 255, 0, 0);
      strip.setBrightness(140);
      strip.show();
      delay(5);
    }
    delay(500);
  }

  //  Turn Blue
  if (select == 4){
    for (int i = 0; i < 55; i++){
      strip.setPixelColor(i, 0, 0, 255);
      strip.setBrightness(140);
      strip.show();
      delay(5);
    }
    delay(500);
  }
/* Turn off */
  if (select == 5){
     for(i=0;i<=56;i++){
         strip.setPixelColor(i, 0, 0, 0);
     }
     strip.setBrightness(140);
     strip.show();
     delay(10);
  } /* End Select = 3 */
}
/*  if (select == 4){
     for(i=0;i<=56;i++){
     strip.setPixelColor(i, 0, 255, 120);
     }
     strip.setBrightness(140);
     strip.show();
     delay(10);
  } /* End Select = 4 */
    

  
//  for (int i = 0; i < 56; i++){
//    strip.setPixelColor(i, 0, 0, 0);
//    strip.show();
//    delay(10);
//  }
