/* 
  Artificial Horizon for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "ArtHor_SSD1306.h"
#include "LTMReader.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include "sinus_cosinus.cpp"

static const unsigned char PROGMEM plane_bmp[] =
{ 
  0b00000111, 0b11100000,
  0b00001000, 0b00010000,
  0b11111000, 0b00011111,
  0b00001000, 0b00010000,
  0b00000111, 0b11100000
};

void ArtHor_SSD1306::init(int pinSDA, int pinSCL) {
  Wire.begin(pinSDA, pinSCL);
  // Initialize OLED-display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}
void ArtHor_SSD1306::hud_horizon(short roll, short pitch) {
  display.clearDisplay(); // Clear display buffer
  drawHUDframe();
  drawHorizon(roll,pitch);
  display.display(); // Update screen
} 

void ArtHor_SSD1306::art_horizon(short roll, short pitch) {
  display.clearDisplay(); // Clear display buffer
  display.fillRect(display.width()/4, 0, display.width()/2, display.height(), SSD1306_WHITE);
  display.fillCircle(display.width()/2, display.height()/2, display.height()/2-2, SSD1306_BLACK);
  drawHorizon(roll,pitch);
  display.display(); // Update screen
}

void ArtHor_SSD1306::soviet_horizon(short roll, short pitch) 
{
  display.clearDisplay(); // Clear display buffer
  drawHUDframe();
  sovietPlane(roll,pitch);
  display.display(); // Update screen
}

void ArtHor_SSD1306::dashboard(LTMReader& TData)
{
  short x1, y1, x2, y2, hoehe, index, index_p, roll, pitch;
  display.clearDisplay(); // Clear display buffer
  // Artificial Horizon top left 54x54
  display.fillRect(0, 0, 55, 54, SSD1306_WHITE);
  display.fillCircle(27, 27, 25, SSD1306_BLACK); 
  roll=-TData.roll;
  pitch=TData.pitch;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 27*cosinus[index]/1000+27;
  x2 = -27*cosinus[index]/1000+27;
  hoehe = -27*sinus[index_p]/1000+27;
  y1 = 27*sinus[index]/1000+hoehe;
  y2 = -27*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  display.drawBitmap(20,25,plane_bmp,16,5,SSD1306_WHITE);
  // GPS-Info and other Info
  display.setCursor(0,56);
  display.print((double) TData.latitude/10000000,7);
  display.print(" ");
  display.print((double) TData.longitude/10000000,7);

  display.setCursor(58, 0);
  display.print("GPS-Fix: ");
  display.print(fixTypes[TData.gpsFix]);
  display.setCursor(58, 11);
  display.print("Sats:   ");
  display.print(TData.gpsSats);
  display.setCursor(58, 22);
  if (TData.armed){display.print("Armed");} else {display.print("Disarmed");}
  display.setCursor(58, 33);
  display.print("km/h:   ");
  display.print(TData.groundSpeed);
  display.setCursor(58, 44);
  display.print("H:");
  display.print(TData.heading);
  index=round((TData.heading)/22.5);
  display.print((char)247);
  display.print("-");
  display.print(windrose[index]);
  display.display(); // Update screen
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
  hoehe = -(display.height()/2)*sinus[index_p]/1000+(display.height()/2);
  y1 = (display.height()/2)*sinus[index]/1000+hoehe;
  y2 = -(display.height()/2)*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  display.drawBitmap(display.width()/2-7,display.height()/2-2,plane_bmp,16,5,SSD1306_WHITE);
}

void ArtHor_SSD1306::sovietPlane (short roll, short pitch) {
  // AGB-3K Style: bird turns and horizontal line for pitch
  short x1, x2, x3, x4, x5, y1, y2, y3, y4, y5, hoehe, index, index_p;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 32*cosinus[index]/1000+64;
  x2 = 4*cosinus[index]/1000+64;
  x3 = -32*cosinus[index]/1000+64;
  x4 = -4*cosinus[index]/1000+64;
  y1 = 32*sinus[index]/1000+32;
  y2 = 4*sinus[index]/1000+32;
  y3 = -32*sinus[index]/1000+32;
  y4 = -4*sinus[index]/1000+32;
  index=index+90;
  if (index>360) {index=index-360;};
  x5 = 10*cosinus[index]/1000+64;
  y5 = 10*sinus[index]/1000+32;
  hoehe = -32*sinus[index_p]/1000+32;
  // Roll
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  display.drawLine(x3, y3, x4, y4, SSD1306_WHITE);
  display.drawLine(x2, y2, x5, y5, SSD1306_WHITE);
  display.drawLine(x4, y4, x5, y5, SSD1306_WHITE);
  // Pitch
  display.drawLine(20, hoehe, display.width()-20, hoehe, SSD1306_WHITE);
  display.drawLine(display.width()/2+5, hoehe-15, display.width()/2-5, hoehe-15, SSD1306_WHITE);
  display.drawLine(display.width()/2+5, hoehe+15, display.width()/2-5, hoehe+15, SSD1306_WHITE);
  //Separation
  display.drawPixel(x1, y1, SSD1306_BLACK);
  display.drawPixel(x3, y3, SSD1306_BLACK);
  display.drawLine(x2, y2, x4, y4, SSD1306_BLACK);
}
