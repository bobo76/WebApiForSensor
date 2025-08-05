# ESP8266 DHT22 Web Server

This project reads temperature and humidity from a DHT22 sensor using an ESP8266 and provides a web dashboard as well as a JSON API endpoint.

## Features

- Web dashboard at `/` (shows temperature, humidity, and ESP8266 IP)
- JSON API data at `/data`
- mDNS support: access as `http://albert.local/` (if supported by your network)
- Easy, secure local WiFi credentials with `arduino_secrets.h`
- Onboard LED indicates web/API requests

## Circuit Connections

| DHT22 Pin      | ESP8266 Pin  |
|----------------|--------------|
| `-` (GND)      | GND          |
| `+` (VCC)      | 3.3V         |
| `out`          | D1 (GPIO5)   |

## Library Dependencies

- ESP8266WiFi
- ESP8266WebServer
- ESP8266mDNS
- Adafruit DHT sensor library

All available in the Arduino Library Manager.

## Usage

1. **Clone or download this repo**

2. **Add your WiFi credentials**

   Copy this to a new file named `arduino_secrets.h` (do not commit this file!):

