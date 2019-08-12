#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#define WLAN_SSID       "xxxxxx"
#define WLAN_PASS       "xxxxxx"
#define CH_ID 000000      // Ganti 000000 dengan channel number
#define WRITE_APIKEY "ABC"   // Ganti ABC dengan kode API

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
  
  // Mengukur sinyal wifi (RSSI)
  long rssi = WiFi.RSSI();
  // Mengirimkan data ke Field 1 didalam channel Thingspeak anda
  int sinyal = ThingSpeak.writeField(CH_ID, 1, rssi, WRITE_APIKEY);
  statusCode = ThingSpeak.getLastReadStatus();
  
  if (statusCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(statusCode));
  }
  // Mengupdate data ke Channel setiap 15 detik
  delay(15000);
}
