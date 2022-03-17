#include <Adafruit_NeoPixel.h>

//For NeoPixel
const unsigned int NEO_PIN=6;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, NEO_PIN, NEO_GRB + NEO_KHZ800);
//For SRF05
const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int BAUD_RATE=9600;
// For buzzer
const int BUZZER = 9;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  strip.begin();
  strip.setBrightness(100); 
  strip.show();
  //rainbow(1);
  colorWipe(strip.Color(0, 0, 255), 2); //Blue
  tone(BUZZER, 1500); 
  delay(1000);        
  noTone(BUZZER);     

}

void loop() {
//SRF05
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

 const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
 int distance= duration/29/2;
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } 
  else{
        if(distance>=7 && distance<=12)
        {
          colorWipe(strip.Color(0, 255, 0), 50); //Distance sans monstre
        } 
        if(distance>12)
        {
          colorWipe(strip.Color(255, 0, 0), 50);  //Couvercle ouvert
          tone(BUZZER, 500); 
          delay(1000);
          noTone(BUZZER); 
         } 
        if(distance<7)
        {
          rainbow(20); //Monstre détecté
         } 
  }
 delay(100);
 }

 // Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
