// Which pin on the ESP8266 is connected to the NeoPixels?
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define brightness 255
#define pixelNumber 48
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(pixelNumber, PIN, NEO_GRB + NEO_KHZ800);

void initStripNeoPixel(){
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(brightness);
  pixels.show();
}
void initStripAnalog(){
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
}
void initStrip(){
  // set new color
  switch (lampType){
    case 1:
      initStripNeoPixel();
      break;
    case 2:
      initStripAnalog();
      break;
    default:
      break;
  }
}

void setColorNeoPixel(RGB color){
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(color.r, color.g, color.b));
  }
  pixels.show();
}
void setColorAnalog(RGB color){
  analogWrite(0,map(color.r,0,255,0,1024));
  analogWrite(1,map(color.g,0,255,0,1024));
  analogWrite(2,map(color.b,0,255,0,1024));
}
void setColor(RGB color){
  // set new color
  switch (lampType) {
    case 1:
      setColorNeoPixel(color);
      break;
    case 2:
      setColorAnalog(color);
      break;
  }
}
