
#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define API_KEY "AIzaSyAOoe0BiIc5c4YSV6zUh6P1SeGOMdKoAmo"
#define DATABASE_URL "https://my-heart-rate-default-rtdb.firebaseio.com/" 

#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "123456789"
 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
#define RXp2 16
#define TXp2 17
void setup() {
   Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
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
 
 auth.user.email = "ibrahimrizq@gmail.come";
  auth.user.password = "123456789";
   Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}
void loop() {
  String s =  getFirstLine(Serial2.readString());
    Serial.println("Message Received: ");
    Serial.println(s);
   bool t=Firebase.setInt(fbdo, "Sensor data/now/Oximeter SpO2 Value",s.toInt());
 Serial.print("ttttt");Serial.println(t);
}
String getFirstLine(String inputString) {
  // Find the position of the first newline character
  int newlinePos = inputString.indexOf('\n');

  // Extract the substring from the beginning to the newline character
  String firstLine = inputString.substring(0, newlinePos);

  return firstLine;
}
