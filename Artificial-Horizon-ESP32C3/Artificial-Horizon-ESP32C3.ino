/* 
  Artificial Horizon for SSD1306 OLED with LTMReader Class
  Copyright (c) 2023 altermac (MIT Licence)
*/

#include "ArtHor_SSD1306.h"
//#define LTM_RXPIN 14  // default GPIO 14, uncomment and change when needed
#include "LTMReader.h"

ArtHor_SSD1306 ArtHorizon;
LTMReader TData;
long nextdisplay=0;

void setup() 
{
  Serial.begin(9600); // only for debug purposes on Serial Monitor

  // Telemetry initialize
  TData.init(10,9); // without parameter default is RX=10 (GPIO10),TX=9 (GPIO9)

  // Articicial Horizon 
  ArtHorizon.init(6,7); // use without parameter when SDA and SCL are set correct by boards manager
  delay(500);
}

void loop() 
{
  TData.update();
  if (millis()>nextdisplay) 
  {
    // choose one of the following 4 lines by removing comment:
    //ArtHorizon.hud_horizon(TData.roll, TData.pitch); // western: HUD-Design
    //ArtHorizon.art_horizon(TData.roll, TData.pitch);  // western: spheric design
    //ArtHorizon.soviet_horizon(TData.roll, TData.pitch);  // soviet: moving plane
    ArtHorizon.dashboard(TData);  // Dashboard with western artificial horizon
    nextdisplay=millis()+50;
  };
  yield(); // let the ESP32 do some unrelated things
}


