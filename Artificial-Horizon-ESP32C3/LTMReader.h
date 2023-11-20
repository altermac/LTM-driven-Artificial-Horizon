/* 
  LTM Reader Class
  Copyright (c) 2023 altermac (MIT Licence)
  LTM based on GitHub\inav\src\main\telemetry\LTM.h and LTM.c
*/
#ifndef _LTMReader_
#define _LTMReader_
#include <string.h>
#include <HardwareSerial.h> 

static const char* fixTypes[] = {
  "NO",
  "NO",
  "2D",
  "3D"
};

static const char* windrose[17]  {
  "N","NNE","NE","ENE",
  "E","ESE","SE","SSE",
  "S","SSW","SW","WSW",
  "W","WNW","NW","NNW","N"
};

// Flightmodes for INAV: Modes not commented with inav are not used.
static const char* flightModes[] = {
  "Manual", // inav 
  "Acro", // inav (was "Rate") This is 'catch all' for everything else
  "Angle", // inav 
  "Horizon", // inav 
  "Acro",
  "Stabilized1",
  "Stabilized2",
  "Stabilized3",
  "Altitude Hold", // inav
  "NAV Loiter" // inav (was "GPS Hold")
  "NAV WP", // inav (was "Waypoints")
  "Heading Hold", // inav (was "Heading free")
  "Circle",
  "NAV RTH", // inav (was "RTH")
  "Follow me",
  "Land",
  "Fly by wire A",
  "Fly by wire B",
  "NAV Cruise", // inav (was "Cruise")
  "Unknown",
  "Launchmode", // inav
  "Autotune" // inav
};

class LTMReader {
  public:
    short pitch;
    short roll;
    short heading;
    uint16_t voltage;
    uint16_t capacityUsed;
    unsigned char rssi;
    unsigned char airspeed;
    bool armed;
    bool failsafe;
    unsigned char flightmode;

    int32_t latitude;
    int32_t longitude;
    int32_t altitude;
    uint8_t groundSpeed; 
    int16_t hdop;
    uint8_t gpsFix;
    uint8_t gpsSats;

    int32_t homeLatitude;
    int32_t homeLongitude;
    int32_t homeAltitude;
    bool homeFix;

    uint8_t sensorStatus;
    bool ltm_update;

  private:
    unsigned char readByte(uint8_t offset);
    int readInt(uint8_t offset);
    int16_t readInt16(uint8_t offset);  
    int32_t readInt32(uint8_t offset);
    float calc_dist(float flat1, float flon1, float flat2, float flon2);

  public:
    void init(short RXD1=10, short TXD1=9);
    void update();
};

#endif // _LTMReader_