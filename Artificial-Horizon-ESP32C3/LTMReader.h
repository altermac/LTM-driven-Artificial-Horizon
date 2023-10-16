/* 
  LTM Reader Class
  Copyright (c) 2023 altermac (MIT Licence)
  LTM based on https://github.com/KipK/Ghettostation/blob/master/GhettoStation/LightTelemetry.cpp implementation
  and parts of ltm_telemetry_reader https://github.com/DzikuVx/ltm_telemetry_reader
*/
#ifndef _LTMReader_
#define _LTMReader_
#include <string.h>
#include <HardwareSerial.h> 

#ifndef LTM_RXPIN
#define LTM_RXPIN 14  // GPIO14
#endif
#ifndef LTM_TXPIN
#define LTM_TXPIN -1  // No TX, only downstream
#endif

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

// Flightmodes von Ardupilot?
static const char* flightModes[] = {
  "Manual",
  "Rate",
  "Angle",
  "Horizon",
  "Acro",
  "Stabilized1",
  "Stabilized2",
  "Stabilized3",
  "Altitude Hold",
  "GPS Hold",
  "Waypoints",
  "Head free",
  "Circle",
  "RTH",
  "Follow me",
  "Land",
  "Fly by wire A",
  "Fly by wire B",
  "Cruise",
  "Unknown"
};

class LTMReader {
  public:
    short pitch;
    short roll;
    short heading;
    uint16_t voltage;
    unsigned char rssi;
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

    uint8_t sensorStatus;

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