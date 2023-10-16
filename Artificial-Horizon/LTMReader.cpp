/* 
  LTM Reader Class
  Copyright (c) 2023 altermac (MIT Licence)
*/

#include "LTMReader.h"

SoftwareSerial ltmSerial(LTM_RXPIN, LTM_TXPIN);

enum ltmStates {
  IDLE,
  HEADER_START1,
  HEADER_START2,
  HEADER_MSGTYPE,
  HEADER_DATA
};

#define LONGEST_FRAME_LENGTH 18
#define GFRAMELENGTH 18
#define AFRAMELENGTH 10
#define SFRAMELENGTH 11
#define OFRAMELENGTH 18
#define NFRAMELENGTH 10
#define XFRAMELENGTH 10

uint8_t serialBuffer[LONGEST_FRAME_LENGTH];
uint8_t state = IDLE;
char frameType;
char frameLength;
char receiverIndex;

char LTMReader::readByte(uint8_t offset) {
  return serialBuffer[offset];
}

int LTMReader::readInt(uint8_t offset) {
  return (int) serialBuffer[offset] + ((int) serialBuffer[offset + 1] << 8);
  //return (int) (serialBuffer[offset + 1] << 8 |serialBuffer[offset] );
}

int16_t LTMReader::readInt16(uint8_t offset) {
  return (int16_t) serialBuffer[offset] + ((int) serialBuffer[offset + 1] << 8);
}

int32_t LTMReader::readInt32(uint8_t offset) {
  return (int32_t) serialBuffer[offset] + ((int32_t) serialBuffer[offset + 1] << 8) + ((int32_t) serialBuffer[offset + 2] << 16) + ((int32_t) serialBuffer[offset + 3] << 24);
}

void LTMReader::init()
{
  ltmSerial.begin(9600);
  ltm_update = false;
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
            voltage = readInt16(0);
            capacityUsed = readInt16(2);
            rssi = readByte(4);
            airspeed = readByte(5);
            char raw = readByte(6);
            flightmode = raw >> 2;
            if (raw&(1<<0)) {
              armed=true;
            } else {
              armed=false;
            }
            if (raw&(1<<1)) {
              failsafe=true;
            } else {
              failsafe=false;
            }
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
        if (frameType == 'O') {
            homeLatitude = readInt32(0);
            homeLongitude = readInt32(4);
            homeAltitude = readInt32(8);

            uint8_t raw = readByte(13);
            if (raw==0) {
              homeFix=false;
            } else {
              homeFix=true;
            }
        }
        if (frameType == 'X') {
            hdop = readInt(0);
            sensorStatus = readByte(2);
        }
      
        state = IDLE;
        memset(serialBuffer, 0, LONGEST_FRAME_LENGTH);
        ltm_update = true;

      } else {
        /*
        * If no, put data into buffer
        */
        serialBuffer[receiverIndex++] = data;
      }
    }
  }
}