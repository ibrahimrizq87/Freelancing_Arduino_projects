#define BLYNK_TEMPLATE_ID "TMPL2V9o6IJNW"
#define BLYNK_TEMPLATE_NAME "my project"
#define BLYNK_AUTH_TOKEN "D0vZlj1WyonVJFuFfv-oFq9Q_uohRRZT"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
#define BUZZER 32

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "my project";  
char pass[] = "111222333444";  

BlynkTimer timer;

int Pulses = 0;
int PulsesInCloud = 0;
bool alert=false;
int sensorV = 0;
unsigned long previousMillis = 0;  
const long interval = 1000 *20; 

void sendSensor()
{
    Blynk.virtualWrite(V0, PulsesInCloud);
    Blynk.virtualWrite(V1, alert);
    if (alert)
    {
 Blynk.virtualWrite(V2, "Alert High Heart rate");
    }else{
       Blynk.virtualWrite(V2, "normal");
    }
   
}

void setup()
{
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
  previousMillis = millis();
  pinMode(BUZZER,OUTPUT);
}



void loop() {
  Blynk.run();
  timer.run();
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    delay(5000);
    Serial.println(" ------------------------------------- ");
    Serial.print("BPM: "); Serial.println(Pulses*3);
   Serial.println(" ------------------------------------- ");
    PulsesInCloud = Pulses*3;
    if (PulsesInCloud > 100 ){
      alert =true;
    }else{
      alert =false;
    }
    Pulses=0;
    previousMillis = millis();
    }

sensorV =analogRead(A0);
Serial.println(sensorV);


if (sensorV >= 1950 &&sensorV < 2100){
Pulses++;
}
 
if (alert){
  for(int i = 0 ; i<20;i++){
digitalWrite(BUZZER,HIGH);
delay(100);
digitalWrite(BUZZER,LOW);
delay(100);
  }
  
}

}

  
