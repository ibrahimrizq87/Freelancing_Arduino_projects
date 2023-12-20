عن#define BLYNK_TEMPLATE_ID "TMPL2FDH33uzk"
#define BLYNK_TEMPLATE_NAME "project"
#define BLYNK_AUTH_TOKEN "KllkRatVALTzXrPHN8hUuX1qSUQUvVu7"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

#define BUTTONPIN   21
#define BUTTONPIN2   23


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "BEMO RIZQ";  // type your wifi name
char pass[] = "123456789";  // type your wifi password

BlynkTimer timer;

int ECG_value =0;
int ECG_value2 =0;
int delta = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int currentheartBeat=random(70,75);
bool buttonState=false;
bool buttonState2=false;
bool add_delata=false;
bool negativeDelta=false;
int previousHeartBeat=random(70,75);
int number=0;
int interval =1000  *60;
int counter = 0;
int counter2 = 0;
void caluculate(){
   unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
  { 
    previousMillis = currentMillis;

      delta = currentheartBeat-previousHeartBeat;
    previousHeartBeat=  currentheartBeat;
    currentheartBeat=random(70,75);
 
    /*
    if (add_delata){
      add_delata =false;
        delta = random(40,70);
    }else if (negativeDelta){
      negativeDelta=false;
      delta = random(-40,-70);
      }else{
        delta = random(-10,10);
        } */
        
        
        }  
        if (buttonState){
          currentheartBeat++;
          }
          if (buttonState2){
             currentheartBeat--;
            }
    
  if (counter == 3 )
  {
    ECG_value = random(900,1000);
    delay (100);
    }
    else if (counter == 6)
    {
    ECG_value = random(900,1000);
    counter =0;
    delay (100);
    }else{
    ECG_value = random(500,600);
    }
    counter++;
     if (counter2 == 7 )
  {
    ECG_value2 = random(900,1000);
    delay (100);
    }
    else if (counter2 == 14)
    {
    ECG_value2 = random(900,1000);
    counter2 =0;
    delay (100);
    }else{
    ECG_value2 = random(500,600);
    }
    counter2++;
}
void sendSensor()
{


    Blynk.virtualWrite(V0, delta);
    Blynk.virtualWrite(V1, ECG_value);
     Blynk.virtualWrite(V2, ECG_value2);
     Blynk.virtualWrite(V4,currentheartBeat );
     Blynk.virtualWrite(V3,previousHeartBeat );
     
    Serial.print("ECG Value: ");
    Serial.println(ECG_value);
    Serial.print("Delat: ");
    Serial.println(delta);
}
void setup()
{   
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
   pinMode(BUTTONPIN, INPUT);
    pinMode(BUTTONPIN2, INPUT);
  }

void loop()
{
  buttonState  = digitalRead(BUTTONPIN);
  buttonState2  = digitalRead(BUTTONPIN2);
  
Serial.print("button1:: ");Serial.println(buttonState);
Serial.print("button2:: ");Serial.println(buttonState2);
  caluculate();
  Blynk.run();
  timer.run();
 }
 
