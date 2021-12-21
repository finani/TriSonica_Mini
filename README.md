# TriSonica Mini
TriSonica Mini library for communicating with the [TriSonica Mini](https://anemoment.com/features/) wind sensor.

# Description
The TriSonica Mini supports Serial(UART) commmunication up to 40 Hz.

# Usage
This library supports Serial(UART) commmunication with the TriSonica Mini.

## Installation
Simply clone or download this library into your Arduino/libraries folder.

## Function Description
This library supports Serial(UART) communication with the TSM.

## TSM Class

### TSM Object Declaratioon

**TSM(HardwareSerial& stream)**
An TSM object should be declared to use. Multiple TSM objects could be used on the different Serial(UART). For example, the following code declares an TSM object called *tsm* with an TSM sensor located on Serial(UART) 6.

```C++
TSM TSMini(Serial6);
```

### Common Setup Functions
The following function is used to setup the TriSonica Mini. This should be called once before data collection, typically this is done in the Arduino *void setup()* function. The *begin* function should always be used. This function is described in detail, below.

**int begin(long baudrate)**
This should be called in your setup function. It initializes communication with the TriSonica Mini at the baudrate. This function returns a positive value on a successful initialization and returns a negative value on an unsuccessful initialization. If unsuccessful, please check your wiring or try resetting power to the sensor. The following is an example of setting up the TriSonica Mini.

```C++
int status;
status = TSMini.begin(115200);
```

**int available()**
It shows the Serial(UART) communication is available. You can read the sensor data, if this function returns a positive value.

```C++
int status;
status = TSMini.available();
```

**int flush()**
It flushes the Serial(UART). It means to clear the buffer of Serial(UART).

```C++
int status;
status = TSMini.flush();
```

### Common Data Collection Functions
The functions below are used to collect data from the TriSonica Mini.

#### Real-Time Data Collection
**int readRawData()** reads the sensor and stores the raw data in a buffer, it should be called every time you would like to retrieve data from the sensor. If the argument existed as a uint8_t* buffer, this function stores the raw data in the buffer. If not, it returns a uint8_t* buffer.

```C++
uint8_t* buffer = IMU.readRawSensor();
IMU.readRawSensor(uint8_t* buffer);
```

**int readData()** reads the sensor and stores the data in a TSMData(structure), it should be called every time you would like to retrieve data from the sensor. If the argument existed as a TSMData, this function stores the data in the TSMData. If not, it returns a TSMData.

```C++
TSMData tsmData = IMU.readSensor();
IMU.readSensor(TSMData& tsmData);
```

## Example List

* **Basic_Serial**: demonstrates declaring an *TSM* object, initializing the sensor, and collecting data. Serial(UART) is used to communicate with the TriSonica Mini.
* **Advanced_I2C**: demonstrates a more advanced setup. In this case, the sensor data is stored a structure *TSMData* after data parsing. Serial(UART) is used to communicate with the TriSonica Mini.

# Wiring and Pullups

Please refer to the [TriSonica Mini datasheet](https://anemoment.com/wp-content/uploads/2021/07/TSM-User-Manual-2021-07-09.pdf). This library should work well for other breakout boards or embedded sensors, please refer to your vendor's pinout diagram.

## Serial(3.3V LVTTL UART)
The TriSonica pins should be connected as:
   * VIN(Brown)
     * Voltage Input of 9V to 36V
   * GND(Red)
     * Ground connection. Only one of the GND connections are required for proper operation. Multiple GND connections are provided as a convenience for system wiring.
   * URX(Gray)
     * 3.3V LVTTL UART Serial Data Input.
   * UTX(Light Green)
     * 3.3V LVTTL-UART Serial Data Output.
   * 232(Black)
     * Force Single Ended Serial mode. When this pin is connected to GND the TSM will start in EIA232 or LVTTL-UART mode with the settings of 115200,8,N,1 regardless of the software settings of the instrument.
