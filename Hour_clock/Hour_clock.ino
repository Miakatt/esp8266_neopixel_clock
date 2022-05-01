#include <Adafruit_NeoPixel.h>
#include <Time.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <math.h>

// Data out pin
#define LED_PIN      4
#define LED_COUNT    60
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// WiFi Parameters
const char* ssid = "Kikidoodle_Ext";
const char* pwd  = "Bottle$TORE101!";

//NTP Parameters
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");


uint8_t R = 0;
uint8_t G = 100;
uint8_t B = 255;

uint32_t hourColour = strip.Color(R,G,B);



// put your setup code here, to run once:
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // this is on pin2, output D4.
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  // Connect to network
  WiFi.begin(ssid, pwd);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n");
  Serial.println("Connection established.");
  Serial.println(WiFi.localIP());
  strip.begin();
  strip.clear();
  strip.setBrightness(24);
  strip.show(); // Initialize all pixels to 'off'
//--------------------------------------------------
// NTP Client initialization
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}


void rainbow(uint8_t wait, uint8_t led_hour, float led_minute_brightness) {
    uint16_t i, j;
    
    for(j=0; j<256; j++) {
      for(i=0; i<led_hour ; i++) {
        strip.setPixelColor(i, Wheel((i*1+j) & 255));    
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
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  int hour = timeClient.getHours();
  int mins = timeClient.getMinutes();
  // calculate how many LEDs to light based on hours. 
  int led_hour = hour * LED_COUNT/24;

//  Serial.println(hour);
//  Serial.println(led_hour);
 // Serial.println(led_minute_brightness);
  float led_minute_brightness =  mins/60.0;
  rainbow(500, led_hour, led_minute_brightness);

  strip.show();
  delay(500);
  strip.clear();
}
