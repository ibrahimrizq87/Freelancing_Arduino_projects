#include <driver/i2s.h>

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


#define BCLK_PIN 25
#define DOUT_PIN 33
#define LRCL_PIN 32
#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // four columns
#define MOTOR 23
bool isNoise =false;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM]      = {19, 18, 5, 17}; // GPIO19, GPIO18, GPIO5, GPIO17 connect to the row pins
byte pin_column[COLUMN_NUM] = {16, 4, 2, 15};   // GPIO16, GPIO4, GPIO0, GPIO2 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup() {
  Serial.begin(9600);
  lcd.begin();                  
  lcd.backlight();
pinMode(MOTOR,OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 22050,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 8
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = BCLK_PIN,
    .ws_io_num = LRCL_PIN,
    .data_out_num = -1, // not used (only for speakers)
    .data_in_num = DOUT_PIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

void loop() {
  uint32_t sample = 0;
  size_t bytes_read;
  i2s_read(I2S_NUM_0, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);
  if (bytes_read > 0) {
    Serial.println(sample);
}

if (sample > 4090000000){
isNoise = true;
digitalWrite(MOTOR,HIGH);
delay(1000);
digitalWrite(MOTOR,LOW);
delay(1000);
digitalWrite(MOTOR,HIGH);
delay(1000);
digitalWrite(MOTOR,LOW);
delay(1000);
}else{
  digitalWrite(MOTOR,LOW);
  isNoise=false;
}

char key = keypad.getKey();
  if (key) {
  Serial.println(key); 
if (key == '1'){
   lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 1"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 1");
}else if (key == '2'){
   lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 2"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 2");
}else if (key == 'A'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: A"); 
  lcd.setCursor(0,1);
  lcd.print("second line: A");
}else if (key == '4'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 4"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 4");
}else if (key == '7'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 7"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 7");
}else if (key == '8'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 8"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 8");
}else if (key == '9'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 9"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 9");
}else if (key == 'C'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: C"); 
  lcd.setCursor(0,1);
  lcd.print("second line: C");
}else if (key == '*'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: *"); 
  lcd.setCursor(0,1);
  lcd.print("second line: *");
}else if (key == '0'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: 0"); 
  lcd.setCursor(0,1);
  lcd.print("second line: 0");
}else if (key == 'D'){
     lcd.clear();
lcd.setCursor(0, 0);
  lcd.print("first line: D"); 
  lcd.setCursor(0,1);
  lcd.print("second line: D");
}
  }
}