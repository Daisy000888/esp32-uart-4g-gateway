# ESP32 UART-4G Gateway

Sponsored by [TowerSoftware](http://www.towersoftwareltd.com/)

<img src="https://github.com/hotteshen/esp32-uart-4g-gateway/blob/master/doc/preview-3d-v1.2.png?raw=true">
<img src="https://github.com/hotteshen/esp32-uart-4g-gateway/blob/master/doc/preview-v1.0-testing.png?raw=true">

## Overview

An ESP32 powered gateway between 4G cellular and RS485 networks.

* ESP32
* Quad UART interface by 2 x WK2312 dual I2C - UART controller
* Isolated RS232 and RS485 ports
* Quectel EG95 4G module

## Repository Skeleton

```
├── doc
├── hardware
│   ├── easyeda         // Schematics and PCB design files in EasyEDA format
│   └── fabrication     // BOM, Geber, Pick&Place files for PCBA ordering
├── esp32-quaduart.ino  // Spike codes for hardware testing
└── README.md
```


## CHangeLog

### 1.2

* remove one WK2312, move UART pins for display and RS 485 direct to the ESP32
* improve EG95 antenna routing

### 1.1

* add 1M startup resistors for WK2312's crystal oscillators.
* add a 2M resistor and a 1nF/2kV capacitor between isolated ground and system ground

### 1.0

* Initial release
