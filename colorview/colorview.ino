#include <Wire.h>
#include "Adafruit_TCS34725.h"


#define redpin 3
#define greenpin 5
#define bluepin 6

#define commonAnode true


byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); 
  }
  

  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }

  }
}


void loop() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false); 

  delay(60);  
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  

  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
 

  Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

  analogWrite(redpin, gammatable[(int)r]);
  analogWrite(greenpin, gammatable[(int)g]);
  analogWrite(bluepin, gammatable[(int)b]);

   int Data_r = (int)r;
   int Data_g = (int)g;
   int Data_b = (int)b;
   
  if (Data_r>135 && Data_g<85 && Data_b<55){
    Serial.write(3); //yellow
    Serial.print("yellow");
  }
  if (Data_r<72 && Data_g>105 && Data_b>80){
    Serial.write(2); //blue
    Serial.print("blue");
  } else{
    Serial.write(1);
  }

}
 

