#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SPI.h>


// WIFI username and password
#define WIFI_USERNAME_DATA "best team"
#define WIFI_PASSWORD_DATA "987654321"

#define API_KEY "AIzaSyB5LTT_U038JfmGMbSl6vZfmpKhYj-MRWM"
#define DATABASE_URL "https://blind-stick-fe032-default-rtdb.firebaseio.com/" 

FirebaseData firebaseDataObject;
FirebaseConfig config;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define PUSH_BUTTON 13

const int trigPin = 12;
const int echoPin = 14;

const int trigPin2 = 5;
const int echoPin2 = 16;

const int trigPin3 = 4;
const int echoPin3 = 0;

int distance = 0;
int distance2 = 0;
int distance3 = 0;
bool buttonState=false;



void setup()
{

  Serial.begin(115200);
  delay(2000);
  WiFi.begin(WIFI_USERNAME_DATA, WIFI_PASSWORD_DATA);
  Serial.print("Connecting to Wi-Fi");
  pinMode(PUSH_BUTTON,INPUT);
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


  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); 
  pinMode(echoPin3, INPUT);
  
/*configers the connection with firebase*/
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
 

  if (Firebase.ready()) 
  {
    Firebase.setBool(firebaseDataObject, "/StickData/ButtonState/value", false);
    }
}

void loop()
{
 distance = measureDistance(trigPin,echoPin);
 distance2 = measureDistance(trigPin2,echoPin2);
 distance3 = measureDistance(trigPin3,echoPin3);
 if ((distance < 50 && distance2 < 50)||(distance < 50 && distance3 < 50)){
  if (distance2 < 50 ){
    distance2 =51;
    }
    if (distance3 < 50 ){
    distance3 =51;
    }
  }else if (distance3 < 50 && distance2 < 50){
    distance3 =51;
    }
  Serial.print("Distance 1: ");Serial.println(distance);
  Serial.print("Distance 2: ");Serial.println(distance2);
  Serial.print("Distance 3: ");Serial.println(distance3);
 
 Serial.print("sensor data: ");Serial.println(digitalRead(PUSH_BUTTON));
 buttonState=digitalRead(PUSH_BUTTON);
 
  if (Firebase.ready()) 
  {

if (buttonState){
    Firebase.setBool(firebaseDataObject, "/StickData/ButtonState/value", true);
  }
       Firebase.setInt(firebaseDataObject, "/StickData/CurrentState/distance", distance);
       Firebase.setInt(firebaseDataObject, "/StickData/CurrentState/distance2", distance2);
       Firebase.setInt(firebaseDataObject, "/StickData/CurrentState/distance3", distance3);
       
       if ((distance >200)&&(distance2 >200)&&(distance3 >200)){
        Firebase.setString(firebaseDataObject,"/StickData/CurrentState/state", "clear");
        }
        if ((distance <200 && distance>100)||(distance2 <200 && distance2>100)||(distance3 <200 && distance3>100))
        {
        Firebase.setString(firebaseDataObject,"/StickData/CurrentState/state", "Far_object");
        }
        if ((distance <100 && distance>50)||(distance2 <100 && distance2>50)||(distance3 <100 && distance3>50))
        {
        Firebase.setString(firebaseDataObject,"/StickData/CurrentState/state", "near_object");
        }
        if ((distance <50 )||(distance2 <50 )||(distance3 <50 ))
        {
        Firebase.setString(firebaseDataObject,"/StickData/CurrentState/state", "stop_no_distance");
        }
       
      
  
  }
  delay(1000);
}
int measureDistance(const int trig,const int echo ){
long duration;
float distanceCm;
float distanceInch;

   digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
   
  // Prints the distance on the Serial Monitor
 
 
  return distanceCm ;
  }
