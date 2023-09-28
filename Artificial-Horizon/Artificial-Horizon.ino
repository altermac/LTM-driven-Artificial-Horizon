
#include "ArtHor_SSD1306.h"
#include "LTMReader.h"

// Artificial Horizon
ArtHor_SSD1306 ArtHorizon;
// LTMReader Object
LTMReader TData;

long nextdisplay=0;

void setup() 
{
  // Serial.begin(9600); // only debug
  // Telemetry initialisieren
  TData.init();
  // Articicial Horizon 
  ArtHorizon.init();
  delay(500);
}

void loop() 
{
  TData.update();
  if (millis()>nextdisplay) 
  {
    // choose one of the following lines by removing comment:
    //ArtHorizon.hud_horizon(TData.roll, TData.pitch); // western:HUD-Design
    //ArtHorizon.art_horizon(TData.roll, TData.pitch);  // western: spheric design
    ArtHorizon.soviet_horizon(TData.roll, TData.pitch);  // soviet: moving plane
    nextdisplay=millis()+50;
  };
  yield();
}


