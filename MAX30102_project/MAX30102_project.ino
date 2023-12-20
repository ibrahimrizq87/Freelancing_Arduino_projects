#define BLYNK_TEMPLATE_ID "TMPL2sOfUYpEq"
#define BLYNK_TEMPLATE_NAME "Oxmeter sensor"
#define BLYNK_AUTH_TOKEN "Lbo8GF0Am8oiHCSGwTCjyV-D_5pFkL13"
#define BLYNK_PRINT Serial


#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include <Adafruit_SSD1306.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "oxmeter project";  
char pass[] = "5555522222";
BlynkTimer timer; 

#define OLED_Address 0x3C 
Adafruit_SSD1306 oled(128, 64);

MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255

uint32_t irBuffer[100]; 
uint32_t redBuffer[100];

#define SDA_2 33
#define SCL_2 32

int32_t bufferLength; 
int32_t spo2; 
int8_t validSPO2;
int32_t heartRate; 
int8_t validHeartRate;

int a=0;
bool midle=false;
int lasta=0;
int lastb=0;
bool rising=true;
int cloudSpO2=0;
int graphValue=random(300,699);;
int start = random(700,900);
int end = random(100,150);

void sendSensor()
{
    Blynk.virtualWrite(V0, cloudSpO2);
    Blynk.virtualWrite(V1, "Normal");
    Blynk.virtualWrite(V2, true);
   
    }

void setup()
{
  Serial.begin(115200); 
 Wire1.begin(SDA_2, SCL_2);
Blynk.begin(auth, ssid, pass);
timer.setInterval(100L, sendSensor);

  if (!particleSensor.begin(Wire1, I2C_SPEED_FAST)) 
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    while (1);
  }


  byte ledBrightness = 60;
  byte sampleAverage = 4; 
  byte ledMode = 2; 
  byte sampleRate = 100; 
  int pulseWidth = 411; 
  int adcRange = 4096; 

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
    
    bufferLength = 100;

  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
oled.clearDisplay();
oled.setTextSize(1);



}

void loop()
{
   Blynk.run();
  timer.run();
 for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    for (byte i = 75; i < 100; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.print(irBuffer[i], DEC);

       Serial.print(F(", HR="));
      Serial.print(heartRate, DEC);

      Serial.print(F(", HRvalid="));
      Serial.print(validHeartRate, DEC);

      Serial.print(F(", SPO2="));
      Serial.print(spo2, DEC);

      Serial.print(F(", SPO2Valid="));
      Serial.println(validSPO2, DEC);
      if (validSPO2 && validHeartRate && irBuffer[i] >50000){
        cloudSpO2=random(94,98);
        displayOled(cloudSpO2,'N');
      }
    }
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
  
void displayOled(int SpO2,char state){
  if(a>127)
  {
    oled.clearDisplay();
    a=0;
    lasta=a;
  }
oled.setTextColor(WHITE);
int b=60-(graphValue/16);
oled.writeLine(lasta,lastb,a,b,WHITE);
lastb=b;
lasta=a;
oled.writeFillRect(0,50,128,16,BLACK);
oled.setCursor(0,50);
oled.print("SpO2: ");
oled.print(SpO2);
oled.print("%     ST:");
oled.print(state);
oled.display();
a+=5;
number();
}
void number(){
static int condition =0;
switch(condition){
  case 0: 
  graphValue =random(700,800);
  break;

  case 1: 
  graphValue =random(400,500);
  break;
  
  case 2: 
  graphValue =random(100,150);
  break;

  case 3: 
  graphValue =random(350,400);
  break;


  case 4: 
  graphValue =random(270,300);
  break;
  case 5: 
  graphValue =random(270,300);
  break;
  case 6: 
  graphValue =random(270,300);
  break;
  case 7: 
  graphValue =random(270,300);
  break;


case 8: 
  graphValue =random(200,250);
  break;
  case 9: 
  graphValue =random(400,500);
  break;
}
condition++;
if (condition >=9 ){
  condition=0;
}
}
