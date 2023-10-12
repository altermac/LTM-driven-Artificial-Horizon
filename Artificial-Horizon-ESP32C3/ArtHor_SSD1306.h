/* 
  Artificial Horizon for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)
*/

#ifndef _ArtHor_SSD1306_
#define _ArtHor_SSD1306_
#include "LTMReader.h"

class ArtHor_SSD1306 
{
  public:
  
  void init(int pinSDA = SDA, int pinSCL = SCL);
  void hud_horizon(short roll, short pitch);
  void art_horizon(short roll, short pitch);
  void soviet_horizon(short roll, short pitch);
  void dashboard(LTMReader& TData);

  private:
  void drawHUDframe ();
  void drawHorizon(short roll, short pitch);
  void sovietPlane (short roll, short pitch);
};

#endif