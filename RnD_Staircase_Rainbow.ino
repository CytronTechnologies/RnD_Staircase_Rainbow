//Example sketch for Cytron RnD Staircase with RainbowBit LED
//Compiled with Arduino 1.0.5 IDE
//Please include the Adafruit_NeoPixel library
//Using BBFuino, 28 pcs of RainbowBit and Infrared sensor
#include <Adafruit_NeoPixel.h> //library developed by Adafruit.

#define RainbowBit_Pin  2   //pin 2 is connected to RainbowBit's Input pin.
#define sensor_G        10  //Ground floor sensor is connected to pin 10
#define sensor_1        3   //1st floor sensor is connected to pin 3
#define buzzer          13  //buzzer is connected to pin 13
#define LED             13  //LED on Arduino
#define BitNumber       28  //number of RainbowBit, it depends on the number of
                            //rainbowBit you connect

// Parameter 1 = number of RainbowBit in strip
// Parameter 2 = pin number connected to RainbowBit's input (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(BitNumber, RainbowBit_Pin, NEO_GRB + NEO_KHZ800);

//preset the color value
uint32_t purple = strip.Color(255, 0, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t cyan = strip.Color(0, 255, 255);
uint32_t white = strip.Color(255, 255, 255);
uint32_t blank = strip.Color(0, 0, 0);

void setup() {
  pinMode(LED, OUTPUT);  //configure LED also Buzzer pin as output pin
  digitalWrite(LED, LOW);  //off LED and buzzer.
  pinMode(sensor_G, INPUT);  //makesure the pin for sensor is input
  digitalWrite(sensor_G, HIGH);  //enable the internal pull up for sensor
  pinMode(sensor_1, INPUT);
  digitalWrite(sensor_1, HIGH);  //enable the internal pull up for sensor
    
  strip.begin();  //initialize register needed for RainbowBit
  delay(100);
  
  strip.show();  // Initialize all RainbowBits to 'off'
  delay(500);
}

void loop() {   
  digitalWrite(LED, LOW);
  delay(10);
  while(1)
  {
  if(digitalRead(sensor_1) == 0) // if 1st floor sensor detect obstacle
  {
    beep(1);
    if(random(3,11)%2) //choose the pattern randomly
    { 
    colorChase(Select_Color(random (7)), 10);  //show random color
    delay(3000);
    }
    else
    {
    colorWipe(Select_Color(random (7)), 450);  //Show random color
    delay(3000);     
    }
    colorWipe(blank, 200);    
  }
  else if(digitalRead(sensor_G) == 0) // if Ground floor sensor detect obstacle
  {
    beep(2);
    if(random(3,11)%2) 
    {     
    colorChase_R(Select_Color(random (7)), 7);  //show random color.
    delay(4000);
    }
    else
    {
    colorWipe_R(Select_Color(random (7)), 500);  //show random color
    delay(3000);    
    }    
    colorWipe_R(blank, 200);    
  }
  
  else  //if no sensor activated, make sure the RainbowBit is off.
  {
    colorWipe(blank,1);
  }
}
  // Some example procedures showing how to display to the Dot:
  /*colorWipe(strip.Color(255, 0, 0), 100); // Red
  delay(100);
  colorWipe_R(strip.Color(0, 255, 0), 100); // Green
  delay(100); 
  colorWipe(strip.Color(0, 0, 255), 100); // Blue
  delay(100);  
  colorWipe_R(strip.Color(255, 255, 255), 100); // White
  delay(100);  
  colorWipe(strip.Color(0, 0, 0), 100); // OFF
  delay(100);  
  rainbow(20);
  rainbowCycle(20);
  delay(100); 
  delay(1000);*/
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipe_R(uint32_t c, uint16_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i-1, c);
      strip.show();
      delay(wait);
  }
}

// Chase the dots one after the other with a color
void colorChase(uint32_t c, uint8_t wait) {
  for(uint16_t j = 0; j <strip.numPixels(); j++)
  {
  for(uint16_t i = strip.numPixels() ; i> j; i--) {
      strip.setPixelColor(i-1, c);
      strip.setPixelColor(i, 0);
      strip.show();
      delay(wait*(j+1)/4);      
      //delay(wait*((j/2)+1));
    }
    delay(wait/2);
  }
}

void colorChase_R(uint32_t c, uint8_t wait) {
  for(uint16_t j = strip.numPixels(); j >0 ; j--)
  {
  for(uint16_t i = 0 ; i< j; i++) {
      strip.setPixelColor(i, c);
      if(i != 0) strip.setPixelColor(i-1, 0);
      strip.show();
      delay(wait*(strip.numPixels() - j + 1)/2);      
      //delay(wait*((j/2)+1));
    }
    delay(wait/2);
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

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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
void beep (unsigned char times)
{
  while (times -- > 0)
  {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(80);
  }
}


uint32_t Select_Color(int mode)
{
  switch (mode)
  {  case 0:
     return blue;     
     case 1:
     return red;
     case 2:
     return green;
     case 3:
     return yellow;
     case 4:
     return purple;
     case 5:
     return cyan;
     case 6:
     return white;
     default:
     return white;
   }  
}
