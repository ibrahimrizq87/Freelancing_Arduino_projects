#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// macros definitions 

#define WIFI_SSID "cap_project"
#define WIFI_PASSWORD "123456789"


#define TFTMODEL INITR_144GREENTAB

#define API_KEY "AIzaSyBS_B7zLI7iQJiIe2drFQDvDaJgQ0sAS0c"

#define DATABASE_URL "https://capstone-efd73-default-rtdb.firebaseio.com/" 

int PUMP= 4; // D2 
bool Empty=false;
int LED = 16; //D0 
int  BUZZER= 5;//D1 
int x = 0;

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


const int analogInPin = A0;
int sensorValue = 0; 
bool hasPermission =false;

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(PUMP,OUTPUT);
  digitalWrite(PUMP,HIGH);
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
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

  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;




  Firebase.begin(DATABASE_URL, API_KEY);



  Firebase.setDoubleDigits(5); 
   
      
}

void loop()
{   
  
  if (Firebase.ready()) 
  {
  
    Serial.printf("Get boolean state data:  %s\n", Firebase.getBool(fbdo, "/Embedded/Has_Permission/state") ? String(fbdo.to<bool>()).c_str() : fbdo.errorReason().c_str());
    hasPermission=fbdo.to<bool>();
    
   sensorValue = analogRead(analogInPin);
 Serial.println("-------------------------------------------------------------------------------------");
    Serial.print("sensor = ");
    Serial.println(sensorValue);
    
    Serial.println("-------------------------------------------------------------------------------------");
   
    if (sensorValue<70){
    String id = generateRandomString(10);
    x=random(110,130);
    
    Firebase.setInt(fbdo, "/Embedded/current/Reading", x);
    Firebase.setString(fbdo, "/Embedded/current/Condition", "Normal Range");
    
    Firebase.setInt(fbdo, "/Embedded/glucose_level/"+id+"/Reading", x);
    Firebase.setString(fbdo, "/Embedded/glucose_level/"+id+"/Condition", "Normal Range");
    
    }else if (sensorValue>70 && sensorValue<150){
    String id = generateRandomString(10);
    x=random(202,215);
    Firebase.setBool(fbdo, "/Embedded/Action needed/value", true);
    
    Firebase.setInt(fbdo, "/Embedded/current/Reading", x);
    Firebase.setString(fbdo, "/Embedded/current/Condition", "Higher than Normal");
    
    Firebase.setInt(fbdo, "/Embedded/glucose_level/"+id+"/Reading", x);
    Firebase.setString(fbdo, "/Embedded/glucose_level/"+id+"/Condition", "Higher than Normal");
        
        }else if (sensorValue>150 && sensorValue<500){
          String id = generateRandomString(10);
    x=random(245,255);
    Firebase.setInt(fbdo, "/Embedded/current/Reading", x);
    Firebase.setString(fbdo, "/Embedded/current/Condition", "Danger");
    Firebase.setInt(fbdo, "/Embedded/glucose_level/"+id+"/Reading", x);
    Firebase.setString(fbdo, "/Embedded/glucose_level/"+id+"/Condition", "Danger");
    if (!Empty){
      digitalWrite(PUMP,LOW);
      delay (3000);
      digitalWrite(PUMP,HIGH);
      Empty =true;
      }
      
      for (int i = 0 ; i < 10;i++){
      digitalWrite(LED ,HIGH);
      digitalWrite(BUZZER ,HIGH);
      delay (250);
      digitalWrite(LED ,LOW);
      digitalWrite(BUZZER ,LOW);
      delay (250);
      }
        }else if (sensorValue>500){
          /*do nothing*/
        }
        
if (!Empty){
  Firebase.setString(fbdo, "/Embedded/hardware state/amount", "FULL");
  }else {
    Firebase.setString(fbdo, "/Embedded/hardware state/amount", "EMPTY");
     for (int i = 0 ; i < 10;i++){
      digitalWrite(LED ,HIGH);
      digitalWrite(BUZZER ,HIGH);
      delay (100);
      digitalWrite(LED ,LOW);
      digitalWrite(BUZZER ,LOW);
      delay (100);
      }
    }
    
        if (hasPermission &&(!Empty) ){
          hasPermission = false;
           Firebase.setBool(fbdo, "/Embedded/Has_Permission/state", false);
          digitalWrite(PUMP,LOW);
      delay (3000);
      digitalWrite(PUMP,HIGH);
          Empty =true;
          }
 

   Serial.print("bool Empty");Serial.println(Empty);
   Serial.print("bool has permission");Serial.println(hasPermission);
  
  }


}



String generateRandomString(int length) {
  String characterSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  String randomString = "";
  
  for (int i = 0; i < length; i++) {
    int randomIndex = random(characterSet.length());
    randomString += characterSet.charAt(randomIndex);
  }
  
  return randomString;
}
