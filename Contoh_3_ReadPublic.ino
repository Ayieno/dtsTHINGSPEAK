#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#define WLAN_SSID       "xxxxxx"
#define WLAN_PASS       "xxxxxx"
#define CH_ID 000000      // Ganti 000000 dengan channel ID PUBLIK yang tersedia di thingspeak
WiFiClient  client;
void setup() {
  Serial.begin(115200);
  delay(100);
  ThingSpeak.begin(client);

  // Menghubungkan ke WIFI.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}
void loop() {

  int statusCode = 0;
  
float field = ThingSpeak.readFloatField(CH_ID, 1); // ganti angka 1 apabila ingin membaca field lainnya sesuai dengan nomor field channel tersebut
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Data Reading Successful: ");
    Serial.println(field);
  }
  else
  {
    Serial.println("Unable to read channel");
  }
  delay(15000);
  
}
