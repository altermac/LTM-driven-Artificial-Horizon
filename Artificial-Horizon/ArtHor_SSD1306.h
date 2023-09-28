#ifndef _ArtHor_SSD1306_
#define _ArtHor_SSD1306_

class ArtHor_SSD1306 
{
  public:
  
  void init();
  void hud_horizon(short roll, short pitch);
  void art_horizon(short roll, short pitch);
  void soviet_horizon(short roll, short pitch);

  private:
  void drawHUDframe ();
  void drawHorizon(short roll, short pitch);
  void sovietPlane (short roll, short pitch);

};

#endif