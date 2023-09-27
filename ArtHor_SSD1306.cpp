#include "ArtHor_SSD1306.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define PI 3.1415926536
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include "sinus_cosinus.cpp"

static const unsigned char PROGMEM plane_bmp[] =
{ 
  0b00001111, 0b11110000,
  0b11111001, 0b10011111,
  0b00001001, 0b10010000,
  0b11111001, 0b10011111,
  0b00001111, 0b11110000
};

void ArtHor_SSD1306::init() {
  // Initialize OLED-display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

}
void ArtHor_SSD1306::horizon(short roll, short pitch) {
  display.clearDisplay(); // Clear display buffer
  drawHUDframe();
  drawHorizon(roll,pitch);
  //fastRuPlane(roll, pitch);
  drawPlane();
  display.display(); // Update screen
}

void ArtHor_SSD1306::drawPlane () 
{
  /*
  display.drawLine(display.width()/2-10, display.height()/2, display.width()/2+10, display.height()/2, SSD1306_WHITE);
  display.drawLine(display.width()/2-10, display.height()/2+1, display.width()/2+10, display.height()/2+1, SSD1306_WHITE);
  display.drawLine(display.width()/2-4, display.height()/2-7, display.width()/2+4, display.height()/2-7, SSD1306_WHITE);
  display.drawLine(display.width()/2, display.height()/2, display.width()/2, display.height()/2-7, SSD1306_WHITE);
  */
  display.drawBitmap(display.width()/2-10,display.height()/2-2,plane_bmp,16,5,SSD1306_WHITE);
}

void ArtHor_SSD1306::drawHUDframe () 
{
  display.drawLine(display.width()-20, 0, display.width()-20, display.height(), SSD1306_WHITE);
  display.drawLine(20, 0, 20, display.height(), SSD1306_WHITE);
  for(int i=1; i< display.height(); i+=10){
    display.drawLine(display.width()-23, i, display.width()-20, i, SSD1306_WHITE);
    display.drawLine(23, i, 20, i, SSD1306_WHITE);
  };
}

void ArtHor_SSD1306::drawHorizon(short roll, short pitch)
{
  short x1, y1, x2, y2, hoehe, index, index_p;
  roll=-roll;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 32*cosinus[index]/1000+64;
  x2 = -32*cosinus[index]/1000+64;
  hoehe = -32*sinus[index_p]/1000+32;
  y1 = 32*sinus[index]/1000+hoehe;
  y2 = -32*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
}

void ArtHor_SSD1306::fastRuPlane (short roll, short pitch) {
  short x1, x2, x3, x4, x5, y1, y2, y3, y4, y5, hoehe, index, index_p;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 32*cosinus[index]/1000+64;
  x2 = 4*cosinus[index]/1000+64;
  x3 = -32*cosinus[index]/1000+64;
  x4 = -4*cosinus[index]/1000+64;
  hoehe = -32*sinus[index_p]/1000+32;
  y1 = 32*sinus[index]/1000+hoehe;
  y2 = 4*sinus[index]/1000+hoehe;
  y3 = -32*sinus[index]/1000+hoehe;
  y4 = -4*sinus[index]/1000+hoehe;
  index=index+90;
  if (index>360) {index=index-360;};
  x5 = 10*cosinus[index]/1000+64;
  y5 = 10*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_INVERSE);
  display.drawLine(x3, y3, x4, y4, SSD1306_INVERSE);
  display.drawLine(x2, y2, x5, y5, SSD1306_INVERSE);
  display.drawLine(x4, y4, x5, y5, SSD1306_INVERSE);
}

void ArtHor_SSD1306::SovietPlane (short roll, short pitch) {
  short x1, x2, x3, y1, y2, y3, hoehe, index, index_p;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 32*cosinus[index]/1000+64;
  x2 = -32*cosinus[index]/1000+64;
  hoehe = -32*sinus[index_p]/1000+32;
  y1 = 32*sinus[index]/1000+hoehe;
  y2 = -32*sinus[index]/1000+hoehe;
  index=index+90;
  if (index>360) {index=index-360;};
  x3 = -12*cosinus[index]/1000+64;
  y3 = -12*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  display.drawLine(64, hoehe, x3, y3, SSD1306_WHITE);
}