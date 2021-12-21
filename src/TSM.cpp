#include "TSM.h"

/* TSM object, input the SPI bus and chip select pin */
TSM::TSM(HardwareSerial& stream) {
  _serial = &stream; // SPI bus
}

/* starts communication with the TSM */
int TSM::begin(long baudrate) {
  // begin SPI communication
  _serial->begin(baudrate);
  if(flush() < 0) {
    return -1;
  }
  // successful init, return 1
  return 1;
}

/* returns whether data from TSM is available*/
int TSM::available() {
  return _serial->available();
}

int TSM::flush() {
  _serial->flush();
  memset(_buffer, 0, sizeof(_buffer));
  return 1;
}

/* reads the most current raw data from TSM and stores in _buffer (member variable) */
uint8_t* TSM::readRawData() {
  String str = _serial->readStringUntil('\n');
  str.toCharArray((char*)_buffer, str.length());
  _buffer[str.length()] = '\0';
  return _buffer;
}

/* reads the most current raw data from TSM and stores in buf (argument) */
int TSM::readRawData(uint8_t* buf) {
  String str = _serial->readStringUntil('\n');
  str.toCharArray((char*)buf, str.length());
  buf[str.length()] = '\0';
  return 1;
}

/* reads the most current data from TSM and stores in _buffer (member variable) */
TSMData& TSM::readData() {
  String str = _serial->readStringUntil('\n');
  str.toCharArray((char*)_buffer, str.length());
  _buffer[str.length()] = '\0';
  _tsmData = dataParsing(_buffer, sizeof(_buffer));
  return _tsmData;
}

/* reads the most current data from TSM and stores in tsmData (argument) */
int TSM::readData(TSMData& tsmData) {
  String str = _serial->readStringUntil('\n');
  str.toCharArray((char*)_buffer, str.length());
  _buffer[str.length()] = '\0';
  tsmData = dataParsing(_buffer, sizeof(_buffer));
  return 1;
}


/* raw data parsing */
TSMData TSM::dataParsing(uint8_t* buf, size_t buf_len) {
  TSMData tsmData = {};
  char temp4[4];
  char temp6[6];
  char temp8[8];
  char temp10[10];

  unsigned int idx = 0;
  while(idx < buf_len) {
    switch (buf[idx]) {
      case 'A':
        if (buf[idx+1] == 'D') {
          memcpy(temp10, &buf[idx+3], sizeof(temp10));
          tsmData.airDensity = atof(temp10);
          idx = idx + 12;
        }
        break;
      case 'D':
        if (buf[idx+1] == ' ') {
          memcpy(temp4, &buf[idx+2], sizeof(temp4));
          tsmData.windDirHor = atoi(temp4);
          idx = idx + 6;
        }
        else if (buf[idx+1] == 'V') {
          memcpy(temp4, &buf[idx+3], sizeof(temp4));
          tsmData.windDirVer = atoi(temp4);
          idx = idx + 6;
        }
        break;
      case 'H':
        memcpy(temp6, &buf[idx+2], sizeof(temp6));
        tsmData.humidity = atof(temp6);
        idx = idx + 8;
        break;
      case 'P':
        if (buf[idx+1] == ' ') {
          memcpy(temp8, &buf[idx+2], sizeof(temp8));
          tsmData.pressure = atof(temp8);
          idx = idx + 10;
        }
        else if (buf[idx+1] == 'I') {
          memcpy(temp6, &buf[idx+3], sizeof(temp6));
          tsmData.pitch = atof(temp6);
          idx = idx + 8;
        }
        break;
      case 'R':
        if (buf[idx+1] == 'O') {
          memcpy(temp6, &buf[idx+3], sizeof(temp6));
          tsmData.roll = atof(temp6);
          idx = idx + 8;
        }
        break;
      case 'S':
        if (buf[idx+1] == ' ') {
          memcpy(temp6, &buf[idx+2], sizeof(temp6));
          tsmData.windSpeed3D = atof(temp6);
          idx = idx + 8;
        }
        else if (buf[idx+1] == '2') {
          memcpy(temp6, &buf[idx+3], sizeof(temp6));
          tsmData.windSpeed2D = atof(temp6);
          idx = idx + 8;
        }
        break;
      case 'T':
        memcpy(temp6, &buf[idx+2], sizeof(temp6));
        tsmData.sonicTemp = atof(temp6);
        idx = idx + 8;
        break;
      default:
        idx++;
        break;
    }
    if (buf[idx] == '\0') { break; }
  }
  return tsmData;
}
