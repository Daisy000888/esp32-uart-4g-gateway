# ESP32 UART-4G Gateway

Sponsored by [TowerSoftware](http://www.towersoftwareltd.com/)

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

### 1.1

* add 1M startup resistors for WK2312's crystal oscillators.
* add a 2M resistor and a 1nF/2kV capacitor between isolated ground and system ground

### 1.0

* Initial release
