#ifndef TSM_H
#define TSM_H

#include "Arduino.h"

struct TSMData {
  float windSpeed3D;
  float windSpeed2D;
  int16_t windDirHor;
  int16_t windDirVer;
  float sonicTemp;
  float humidity;
  float pressure;
  float airDensity;
  float pitch;
  float roll;
};

class TSM{
  public:
    TSM(HardwareSerial& stream);
    int begin(long baudrate);
    int available();
    int flush();
    uint8_t* readRawData();
    int readRawData(uint8_t* buf);
    TSMData& readData();
    int readData(TSMData& tsmData);
  protected:
    TSMData dataParsing(uint8_t* buf, size_t buf_len);
    // serial(uart)
    HardwareSerial* _serial = {};
    // buffer for reading from sensor
    TSMData _tsmData = {};
    uint8_t _buffer[300];
};

#endif // TSM_H
