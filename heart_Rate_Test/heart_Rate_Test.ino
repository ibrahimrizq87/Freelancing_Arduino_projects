#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SPI.h>


// WIFI username and password
#define WIFI_USERNAME_DATA "BEMO RIZQ"
#define WIFI_PASSWORD_DATA "123456789"

#define API_KEY "AIzaSyAxCUSggwkE61hz1DNDUuALAMis_3hdf0o"
#define DATABASE_URL "https://heart-rate-93aee-default-rtdb.firebaseio.com/" 

FirebaseData firebaseDataObject;
FirebaseConfig config;


unsigned int heartBeats = 0;
unsigned int heartRate = 0;
unsigned long previousMillis = 0;  
const long interval = 1000; 
unsigned int sensorValue = 0;


void setup()
{

  Serial.begin(115200);
  delay(2000);
  WiFi.begin(WIFI_USERNAME_DATA, WIFI_PASSWORD_DATA);
  Serial.print("Connecting to Wi-Fi");
  
  
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("=");
    delay(300);
    Serial.print("/");
  }

  
  Serial.println();
  Serial.print("connected successfuly");
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;


  
/*configers the connection with firebase*/
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
 
previousMillis = millis();
}

void loop()
{
 sensorValue = map(analogRead(A0), 1, 1024, 20, 200);

 Serial.print("heart Rate: ");Serial.println(sensorValue);
  if (Firebase.ready()) 
  {
    Firebase.setInt(firebaseDataObject, "/Heart Rate/Now/Heart Rate is", sensorValue);
    String path =  GenTxt();
    if(sensorValue > 83 && sensorValue< 140){
    Firebase.setString(firebaseDataObject, "/Heart Rate/Now/condition", "normal");
      }else if (sensorValue < 83){
        Firebase.setString(firebaseDataObject, "/Heart Rate/Now/condition", "alert low");
        Firebase.setString(firebaseDataObject, "/Heart Rate/Alert/LOW/"+path+"/value",sensorValue );
        Firebase.setString(firebaseDataObject, "/Heart Rate/Alert/LOW/"+path+"/condition", "alert low");
        }else if (sensorValue >140){
          Firebase.setString(firebaseDataObject, "/Heart Rate/Now/condition", "alert high");
          Firebase.setString(firebaseDataObject, "/Heart Rate/Alert/HIGH/"+path+"/value",sensorValue );
          Firebase.setString(firebaseDataObject, "/Heart Rate/Alert/HIGH/"+path+"/condition", "alert high");
          }
 
 delay (1000);
  }
}

String GenTxt(){
  String randString = "";
  String letters[40] = {"a", "b", "c", "d", "e", "f","g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
for(int i = 0; i<10; i++)
    {
           randString = randString + letters[random(0, 40)];

      }
return randString;
}
