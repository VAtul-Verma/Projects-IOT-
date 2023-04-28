
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


const int red_led=13;
const int green_led =2;
const int buzzer=14;
float LPGthreshold = 150;
const int relay = 15;
const int firstalermthresold = 220;

//bool smsSent = false;
#define SerialMon Serial








void setup() {


  SerialMon.begin(115200);


//    pinMode(pin,INPUT);/
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
   Wire.begin(5, 4);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  // Clear the buffer.
  display.clearDisplay();
  
  // Draw bitmap on the screen
 display.println("Hello Olus");
  display.display();
  delay(3000);
  }

void loop() {
  // To access your stored values on inputString, inputInt, inputFloat


  float Sensor_value =analogRead(26);
display.clearDisplay();
  Serial.println(Sensor_value);
   display.println(Sensor_value);
  display.display();
  delay(2000);

  
  if((Sensor_value > LPGthreshold)){
      digitalWrite(green_led,LOW);
      digitalWrite(red_led,HIGH);
        delay(2000);
      Serial.println("Gas Leaked");
      delay(1000);
   //   tone(buzzer, 1000,500); // Send 1KHz sound signal...
   if(Sensor_value<firstalermthresold){
        tone(buzzer,500);
      delay(1000);
     // noTone(buzzer); // Stop sound...
     noTone();  
      delay(500);
  //   tone(buzzer, 1000,500);
   tone(buzzer,1000);
     delay(1000);
     // noTone(buzzer); // Stop sound...
     noTone();  
      delay(500);
   }else{
    digitalWrite(relay,LOW);
      delay(1000);
    digitalWrite(relay,HIGH);
      delay(1000);
    digitalWrite(relay,LOW);
      delay(1000);
       digitalWrite(relay,HIGH);
      delay(1000);
  }
  }
   
  else{
    digitalWrite(red_led,LOW);
    delay(200);
    digitalWrite(green_led,HIGH);
    delay(200);
    digitalWrite(green_led,LOW);
    
    digitalWrite(relay,HIGH);
    delay(2000);
   // noTone(buzzer);
   noTone();
    
    }

    delay(5000);
}

int playing = 0;
void tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(pin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
  playing = pin; // store pin
}
void noTone() {
  tone(playing, 0);
}
