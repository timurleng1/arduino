/***************************************************
  This is an example for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC5947.h"

// How many boards do you have chained?
#define NUM_TLC5974 5

#define data   4
#define clock   5
#define latch   6
#define oe  -1  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch);

void setup() {
  Serial.begin(9600);

  Serial.println("TLC5974 test");
  tlc.begin();
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }
}

void snake(uint16_t leds){

    uint16_t i;

  for (i = 0; i < leds; i++) {
    tlc.setPWM(i, 4096);
    
    tlc.setPWM(i+1, 4096);
    tlc.setPWM(i+2, 4096);
    tlc.setPWM(i+3, 4096);
    tlc.setPWM(i+4, 4096);
    tlc.setPWM(i+5, 4096);
    

        tlc.write();
    delay(50);
    tlc.setPWM(i, 0);
    tlc.write();
    
  }

}

void cross(uint16_t pattern) {

  int arr[] = { 
  
  1, 2, 8,9,
  14, 15, 19, 20,
  29,30, 32, 33,
  44, 45, 46,
  59, 60, 61,
  74, 75, 77, 78,
  87, 88, 92, 93,
  98, 99, 105, 106,
  108, 116
  };



  int length = sizeof(arr)/sizeof(int);
  uint16_t i;
  uint16_t j;
  if (pattern == 1) {
  
   for (i = 0; i < length; i++) {
      tlc.setPWM(arr[i], 4096);
      tlc.setPWM(arr[i+4], 4096);
      tlc.setPWM(arr[i+8], 4096);
      tlc.setPWM(arr[i+12], 4096);
      tlc.setPWM(arr[i], 0);
          tlc.write();
  
      
  
    }
  
  }

  if (pattern == 2) {
  
    for (j = 0; j < 32; j++) {
    
      int intensity = j*128;
    
      for (i = 0; i < length+1; i++) {
        tlc.setPWM(arr[i], intensity); 
        }
    
      tlc.write();
      delay(10);
    
    }
    
    for (j = 32; j > 0; j--) {
    
      int intensity = j*128; 
    
      for (i = 0; i < length+1; i++) {
        tlc.setPWM(arr[i], intensity);  
    }
    
    tlc.write();
    delay(10);
    
    }
    
  }

}

void glow(uint16_t leds) {
    uint16_t i;
    uint16_t j;

for (j = 0; j < 32; j++) {
    
      int intensity = j*128;
    
      for (i = 0; i < leds; i++) {
        tlc.setPWM(i, intensity); 
        }
    
      tlc.write();
      delay(10);
    
    }
    
    for (j = 32; j > 0; j--) {
    
      int intensity = j*128; 
    
      for (i = 0; i < leds; i++) {
        tlc.setPWM(i, intensity);  
    }
    
    tlc.write();
    delay(10);
    
    }

}


void loop() {

  uint16_t leds;
  leds = 117;


  snake(leds);

  //cross(2);

  

}
