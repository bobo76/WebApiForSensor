ESP8266 DHT22 Temperature & Humidity Web Server
This project reads temperature and humidity from a DHT22 sensor connected to an ESP8266 board, then serves readings via a built-in web interface and a JSON API. Network credentials and sensitive data remain local using a secrets file.

Features
🟢 Web Dashboard: Displays real-time temperature and humidity at /

🟣 REST API: Returns latest reading as JSON at /data

🟡 mDNS Support: Access via http://albert.local/ (if supported by your network)

🔒 WiFi credentials kept private via secrets file

🔴 Onboard LED indicates request activity

Hardware Connections
"DHT22 Pin","ESP8266 Board Pin"
"- (GND)","GND"
"+ (VCC)","3.3V"
"out","D1 (GPIO5)"

File/Code Structure
main.ino or .cpp — Main sketch code

arduino_secrets.h — WiFi credentials (not in repo)

webpage.h — HTML template for dashboard