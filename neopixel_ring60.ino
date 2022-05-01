#include <Adafruit_NeoPixel.h>
#include <Time.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <math.h>

// Data out pin

#define LED_PIN      2
#define LED_COUNT    60
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// WiFi Parameters
const char* ssid = "";
const char* pwd  = "";

//NTP Parameters
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org");
//Days of week
String weekdays[7]={"Sun", "Mon", "Tues", "Wed", "Thurs","Fri","Sat"};
//Months
String months[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

uint32_t hourColour = strip.Color(255, 0, 255);
uint32_t minuteColour = strip.Color(0, 100, 255);
uint32_t secondColour = strip.Color(50, 255, 50);



// put your setup code here, to run once:
void setup() {
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

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
 /* time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch time: ");
  Serial.println(epochTime);

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);
  */
  int hour = timeClient.getHours();
  int mins = timeClient.getMinutes();
  int secs = timeClient.getSeconds();
  int day  = timeClient.getDay();

  
 // Serial.print("Raw Hours ");
 // Serial.print(hour);
  Serial.print(":");
  Serial.print(mins);
  Serial.println();
  if (hour>=12){
    hour -= 12;
  }
  hour = 5*hour + round(5*mins/60);
  strip.setPixelColor(hour, hourColour);
  strip.setPixelColor(mins, minuteColour);
  strip.setPixelColor(secs, secondColour); 
  strip.show();
  delay(500);
  strip.clear();
}
