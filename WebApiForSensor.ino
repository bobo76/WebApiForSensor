// pin -   => grnd
// pin +   => 3.3V
// pin out => D1

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"
#include "webpage.h"

#define DHTPIN 5       // Digital pin  #2 on ESP8266
#define DHTTYPE DHT22  // Sensor type

#define STASSID "*****"
#define STAPSK "*****"

ESP8266WebServer server(80);

const char* ssid = STASSID;
const char* password = STAPSK;
const char* hostname = "albert";

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature_C;

const int led = LED_BUILTIN;

void handleRoot() {
  digitalWrite(led, 0);
  loopReadTemperature();

  String page = String(MAIN_page);  // Copy from PROGMEM into RAM
  page.replace("%TEMP%", String(temperature_C, 1));
  page.replace("%HUMIDITY%", String(humidity, 1));
  page.replace("%ip_address%", WiFi.localIP().toString());

  server.send(200, "text/html", page);
  delay(500);
  digitalWrite(led, 1);
}

void handleGetData() {
  if (server.method() != HTTP_GET) {
    digitalWrite(led, 0);
    server.send(405, "text/plain", "Method Not Allowed: " + getHttpMethodName());
    delay(500);
    digitalWrite(led, 1);
    return;
  }
  loopReadTemperature();

  digitalWrite(led, 0);
  server.send(200, "application/json", getData());
  delay(250);
  digitalWrite(led, 1);
}

void handleNotFound() {
  digitalWrite(led, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += getHttpMethodName();
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  delay(250);
  digitalWrite(led, 1);
}

String getHttpMethodName() {
  switch (server.method()) {
    case HTTP_GET: return "GET";
    case HTTP_POST: return "POST";
    case HTTP_PUT: return "PUT";
    case HTTP_PATCH: return "PATCH";
    case HTTP_DELETE: return "DELETE";
    default: return "UNKNOWN";
  }
}

String getData() {
  String data = "{\"humidity\": " + String(humidity) + ", " + "\"temperature\": " + String(temperature_C) + "}";
  return data;
}

void setupNetwork() {
  digitalWrite(led, 1);

  WiFi.mode(WIFI_STA);  // Set WiFi to station mode
  WiFi.begin(ssid, password);
  Serial.println(F("Init wifi"));

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));

  Serial.print(F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(hostname)) {
    Serial.println(F("Error starting mDNS"));
  } else {
    Serial.print(F("mDNS responder started: "));
    Serial.println(WiFi.hostname());
  }

  server.on("/", handleRoot);
  server.on("/data", handleGetData);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println(F("HTTP server started"));
}

void setupSensor() {
  dht.begin();
}

void setup(void) {
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  setupNetwork();
  delay(2000);
  setupSensor();
}

void loopReadTemperature() {
  temperature_C = dht.readTemperature();
  humidity = dht.readHumidity();

  // Check for error reading
  if (isnan(humidity) || isnan(temperature_C)) {
    Serial.println(F(" DHT reading failed "));
    Serial.print(humidity);
    Serial.print(F(", "));
    Serial.println(temperature_C);
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  Serial.print(F("Temperature: "));
  Serial.print(temperature_C);
  Serial.println(F("°C"));
}

void loop(void) {
  MDNS.update();

  server.handleClient();
}
