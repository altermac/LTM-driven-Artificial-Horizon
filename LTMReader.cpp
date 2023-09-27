#include "LTMReader.h"

static const int RXPin = 14, TXPin = -1; // GPIO 12 or -1 for no TXPin
SoftwareSerial ltmSerial(RXPin, TXPin);

enum ltmStates {
  IDLE,
  HEADER_START1,
  HEADER_START2,
  HEADER_MSGTYPE,
  HEADER_DATA
};

#define LONGEST_FRAME_LENGTH 18
/*
* LTM based on https://github.com/KipK/Ghettostation/blob/master/GhettoStation/LightTelemetry.cpp implementation
*/

#define GFRAMELENGTH 18
#define AFRAMELENGTH 10
#define SFRAMELENGTH 11
#define OFRAMELENGTH 18
#define NFRAMELENGTH 10
#define XFRAMELENGTH 10

// Flightmodes von Ardupilot?
const char* flightModes[] = {
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


uint8_t serialBuffer[LONGEST_FRAME_LENGTH];
uint8_t state = IDLE;
char frameType;
byte frameLength;
byte receiverIndex;

byte LTMReader::readByte(uint8_t offset) {
  return serialBuffer[offset];
}

int LTMReader::readInt(uint8_t offset) {
  return (int) serialBuffer[offset] + ((int) serialBuffer[offset + 1] << 8);
  //return (int) (serialBuffer[offset + 1] << 8 |serialBuffer[offset] );
}

short LTMReader::readInt16(uint8_t offset) {
  return (int16_t) serialBuffer[offset] + ((int) serialBuffer[offset + 1] << 8);
}

int32_t LTMReader::readInt32(uint8_t offset) {
  return (int32_t) serialBuffer[offset] + ((int32_t) serialBuffer[offset + 1] << 8) + ((int32_t) serialBuffer[offset + 2] << 16) + ((int32_t) serialBuffer[offset + 3] << 24);
}

//Function to calculate the distance between two waypoints
float LTMReader::calc_dist(float flat1, float flon1, float flat2, float flon2)
{
    float dist_calc=0;
    float dist_calc2=0;
    float diflat=0;
    float diflon=0;

    //I've to spplit all the calculation in several steps. If i try to do it in a single line the arduino will explode.
    diflat=radians(flat2-flat1);
    flat1=radians(flat1);
    flat2=radians(flat2);
    diflon=radians((flon2)-(flon1));

    dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
    dist_calc2= cos(flat1);
    dist_calc2*=cos(flat2);
    dist_calc2*=sin(diflon/2.0);
    dist_calc2*=sin(diflon/2.0);
    dist_calc +=dist_calc2;

    dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));

    dist_calc*=6371000.0; //Converting to meters
    //Serial.println(dist_calc);
    return dist_calc;
}

void LTMReader::init()
{
  ltmSerial.begin(9600);
}

void LTMReader::update() 
{
  if (ltmSerial.available()) {

    char data = ltmSerial.read();

    if (state == IDLE) {
      if (data == '$') {
        state = HEADER_START1;
      }
    } else if (state == HEADER_START1) {
      if (data == 'T') {
        state = HEADER_START2;
      } else {
        state = IDLE;
      }
    } else if (state == HEADER_START2) {
      frameType = data;
      state = HEADER_MSGTYPE;
      receiverIndex = 0;

      switch (data) {
        case 'G':
          frameLength = GFRAMELENGTH;
          break;
        case 'A':
          frameLength = AFRAMELENGTH;
          break;
        case 'S':
          frameLength = SFRAMELENGTH;
          break;
        case 'O':
          frameLength = OFRAMELENGTH;
          break;
        case 'N':
          frameLength = NFRAMELENGTH;
          break;
        case 'X':
          frameLength = XFRAMELENGTH;
          break;
        default:
          state = IDLE;
      }

    } else if (state == HEADER_MSGTYPE) {

      /*
      * Check if last payload byte has been received.
      */
      if (receiverIndex == frameLength - 4) {
        /*
        * If YES, check checksum and execute data processing
        */

        if (frameType == 'A') {
            pitch = readInt16(0);
            roll = readInt16(2);
            heading = readInt16(4);
        }

        if (frameType == 'S') {
            voltage = readInt(0);
            rssi = readByte(4);

            byte raw = readByte(6);
            flightmode = raw >> 2;
        }

        if (frameType == 'G') {
            latitude = readInt32(0);
            longitude = readInt32(4);
            groundSpeed = readByte(8);
            altitude = readInt32(9);

            uint8_t raw = readByte(13);
            gpsSats = raw >> 2;
            gpsFix = raw & 0x03;
        }

        if (frameType == 'X') {
            hdop = readInt(0);
            sensorStatus = readByte(2);
        }
      
        state = IDLE;
        memset(serialBuffer, 0, LONGEST_FRAME_LENGTH);

      } else {
        /*
        * If no, put data into buffer
        */
        serialBuffer[receiverIndex++] = data;
      }

    }
  }
}