#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include "DHT.h"

#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define USERNAME "atmduino"
#define DEVICE_ID "smartkos_02"
#define DEVICE_CREDENTIAL "dormeunbi"

#define SSID "pandawa"
#define SSID_PASSWORD "Werkud4r@"

#define relay_lamp D6
#define relay_doorLock D7
#define doorSensor D0

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  dht.begin();
  pinMode(doorSensor, INPUT_PULLUP);
  pinMode(relay_lamp , OUTPUT);
  pinMode(relay_doorLock, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["Lamp All"] << digitalPin(relay_lamp);
  thing["Door Lock"] << digitalPin(relay_doorLock);

  thing["Sensor Temp & Humd"] >> [](pson & out) {
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
  };

  thing["Door Sensor"] >> [](pson & out) {
    int door = digitalRead(doorSensor);
    String doorState;
    if (door == 1) {
      doorState = "Door Open";
    }
    else {
      doorState = "Door Close";
    }
    out["Door State"] = doorState;
  };
}

void loop() {
  thing.handle();
}
