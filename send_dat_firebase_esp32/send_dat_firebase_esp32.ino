#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define API_KEY "AIzaSyAOoe0BiIc5c4YSV6zUh6P1SeGOMdKoAmo"
#define DATABASE_URL "https://my-heart-rate-default-rtdb.firebaseio.com/" 

#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "123456789"


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;



void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    unsigned long ms = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    Firebase.reconnectWiFi(true);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

   Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

    
}

void loop()
{
Firebase.setInt(fbdo, "test/int", 0);
}
