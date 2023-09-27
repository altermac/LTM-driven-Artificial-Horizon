
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
    ArtHorizon.horizon(TData.roll, TData.pitch);
    nextdisplay=millis()+50;
  };
  yield();
}


