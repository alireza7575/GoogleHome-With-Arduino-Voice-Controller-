#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#endif

#include <esp8266-google-home-notifier.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "........";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "........";
char pass[] = "........";
GoogleHomeNotifier ghn;

BLYNK_WRITE(V2) {
  if (param.asInt()) {
    if (ghn.notify("Hello!") != true) {
      Serial.println(ghn.getLastError());
      return;
    }
    Serial.println("Done.");
  }
  else {
    if (ghn.notify("bye!") != true) {
      Serial.println(ghn.getLastError());
      return;
    }
    Serial.println("Done.");
  }
}

void setup() {
  // Debug console
  Blynk.begin(auth, ssid, pass);
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  Serial.print("connecting to Wi-Fi");

  const char displayName[] = "Living Room speaker";

  Serial.println("connecting to Google Home...");
  if (ghn.device(displayName, "en") != true) {
    Serial.println(ghn.getLastError());
    return;
  }
  Serial.print("found Google Home(");
  Serial.print(ghn.getIPAddress());
  Serial.print(":");
  Serial.print(ghn.getPort());
  Serial.println(")");

  if (ghn.notify("Hello, World!") != true) {
    Serial.println(ghn.getLastError());
    return;
  }
  Serial.println("Done.");
}

void loop() {
  Blynk.run();
}
