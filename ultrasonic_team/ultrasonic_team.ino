// zero which is front >> one is left >>> two is right
const int TRIG_PIN0    = 23;
const int ECHO_PIN0    = 22;

const int TRIG_PIN1   = 19;
const int ECHO_PIN1   = 18;

const int TRIG_PIN2   = 4;
const int ECHO_PIN2   = 2;

const int BUZZER_PIN  = 15;

int dist_0 = 0 ; // from zero ultera
int dist_1 = 0 ; // from left ultera
int dist_2 = 0 ; // from right ultera

int readUltrasonicSensor(int trigPin, int echoPin) {
  long duration;
  int dist;
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //distance = distanceToCm(duration); // remove
  dist=duration/57 ; // 57 is getting this offer for me cm directly 
  return dist;
}

void beep(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN0, OUTPUT);
  pinMode(ECHO_PIN0, INPUT);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  dist_0 = readUltrasonicSensor(TRIG_PIN0, ECHO_PIN0);
  dist_1 = readUltrasonicSensor(TRIG_PIN1, ECHO_PIN1);//left
  dist_2 = readUltrasonicSensor(TRIG_PIN2, ECHO_PIN2);//right

  Serial.print("dist0: ");Serial.println(dist_0);
  Serial.print("dist1: ");Serial.println(dist_1);
  Serial.print("dist2: ");Serial.println(dist_2);
  // change the name of distance in float func to be dist only 
  // Read ultrasonic sensor 1
  dist_0 = readUltrasonicSensor(TRIG_PIN0, ECHO_PIN0);
  if (dist_0 <= 70 ) { // detect some thing front 
    Serial.print("dist0: ");
    Serial.println(dist_0);
    beep(2);
    // start check other ultera 
  dist_1 = readUltrasonicSensor(TRIG_PIN1, ECHO_PIN1);//left
  dist_2 = readUltrasonicSensor(TRIG_PIN2, ECHO_PIN2);//right
  if ((dist_1 <= 50)&&(dist_2 <= 50 )) {
    //from right and left 
     Serial.println("return back");
          beep(12);

  }
   else if (dist_1 <= 50 ) {
    Serial.print("dist1: ");
    Serial.println(dist_1);
    beep(4);
  }else if (dist_2 <= 50 ) {
    Serial.print("dist2: ");
    Serial.println(dist_2);
    beep(6);
      }
  }
 
delay(1000);
}
