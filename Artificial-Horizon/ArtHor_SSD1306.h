#ifndef _ArtHor_SSD1306_
#define _ArtHor_SSD1306_

class ArtHor_SSD1306 
{
  public:
  
  void init();
  void horizon(short roll, short pitch);

  private:
  void drawPlane ();
  void drawHUDframe ();
  void drawHorizon(short roll, short pitch);
  void fastRuPlane (short roll, short pitch); 
  void SovietPlane (short roll, short pitch);

};

#endif