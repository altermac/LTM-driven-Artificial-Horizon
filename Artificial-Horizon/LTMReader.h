#ifndef _LTMReader_
#define _LTMReader_

#include <SoftwareSerial.h>


static const char* fixTypes[] = {
  "NO",
  "2D",
  "3D"
};

class LTMReader {
  public:
    short pitch;
    short roll;
    short heading;
    uint16_t voltage;
    byte rssi;
    bool armed;
    bool failsafe;
    byte flightmode;

    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
    uint8_t groundSpeed; 
    int16_t hdop;
    uint8_t gpsFix;
    uint8_t gpsSats;

    int32_t homeLatitude;
    int32_t homeLongitude;

    uint8_t sensorStatus;

  private:
 


  byte readByte(uint8_t offset);
  int readInt(uint8_t offset);
  int16_t readInt16(uint8_t offset);  
  int32_t readInt32(uint8_t offset);
  float calc_dist(float flat1, float flon1, float flat2, float flon2);

public:
  void init();
  void update();

};

#endif // _LTMReader_