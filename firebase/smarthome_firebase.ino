// firebase
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "....................."//sesuaikan dengan host firebase yang mau di koneksikan
#define FIREBASE_AUTH ".................."//sesuaikan dengan aut firebase yang mau di koneksikan
#define WIFI_SSID "................"//nama ssid yang terhubung
#define WIFI_PASSWORD "................"//password yang terhubung
//status indikator wifi
#define indi_wifi_off D0
#define indi_wifi_on D1
FirebaseData firebaseData;

//relay
#define relay_1 D6
#define relay_2 D7

void setup() {
  // program setup
  Serial.begin(9600);
  pinMode(relay_1, OUTPUT);//setup pin menjadi output
  pinMode(relay_2, OUTPUT);
  pinMode(indi_wifi_off, OUTPUT);
  pinMode(indi_wifi_on, OUTPUT);
  digitalWrite(indi_wifi_on, LOW);

  //WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  Serial.println();
  // jika wifi belum terhubung maka program akan berjalan di dalam function while
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(indi_wifi_off, HIGH);
    delay(80);
    digitalWrite(indi_wifi_off, LOW);
    delay(80);
  }
  // jika wifi sudah terhubung
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  //program loop
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(indi_wifi_on, HIGH);
    digitalWrite(indi_wifi_off, LOW);
  }

  // lamp1 control
  String lamp1;
  Firebase.getString(firebaseData, "Lampu_1");
  lamp1 = firebaseData.stringData();
  if (lamp1 == "0") {
    digitalWrite(relay_1, LOW);
  }
  if (lamp1 == "1") {
    digitalWrite(relay_1, HIGH);
  }
  // lamp2 control
  String lamp2;
  Firebase.getString(firebaseData, "Lampu_2");
  lamp2 = firebaseData.stringData();
  if (lamp2 == "0") {
    digitalWrite(relay_2, LOW);
  }
  if (lamp2 == "1") {
    digitalWrite(relay_2, HIGH);
  }
}
