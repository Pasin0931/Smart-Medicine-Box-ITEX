#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6ReCDIu_Y"
#define BLYNK_TEMPLATE_NAME "medBoxInUse"
#define BLYNK_AUTH_TOKEN "y1oMWgdbA2QeHqYA9n8G8UX-qUN0MiRc"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "time.h"
#include "sntp.h"

#include <Adafruit_NeoPixel.h>

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include <HTTPClient.h>

#include <TridentTD_LineNotify.h>

#define LINE_TOKEN  "MBovazmJoELV5AWh33V9QOQ8Owuxj6mC7L7S3Y4WD2v"

//-----------------------------------------------------------------

static const uint8_t PIN_MP3_TX = 26; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 27; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

//-----------------------------------------------------------------

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 3600;

const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";

char ssid[] = "SANER_2.4G";
char pass[] = "0840756009";

//-----------------------------------------------------------------

int LEDPIN = 5;
int NUMPIXELS = 16;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

//-----------------------------------------------------------------

int setHours;
int setMinutes;
int setSetm;

String strHours;
String strMinute;

int numHour = 0;
int numMinute = 0;

char stop[] = {'3', '1', '0'};

char timeHour[3];
char timeMinute[3];

int alarmH;
int alarmM;

//-----------------------------------------------------------------

String GOOGLE_SCRIPT_ID = "AKfycbzWbrcUdIX71SKicfEksJS4sqWz9ztKajoOzYe0iB0wWwR9bjmWnbCv2OkR7Z8nrQtb";

int i = 0;

//-----------------------------------------------------------------

#define button 4

void setup()
{
  pinMode(button, INPUT_PULLUP);

  Serial.begin(115200);
  softwareSerial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(23,OUTPUT);
  sntp_set_time_sync_notification_cb( timeavailable );
  WiFi.begin(ssid, pass);
  sntp_servermode_dhcp(1);    // (optional)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  Serial.printf("Connecting to %s ", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  if (player.begin(softwareSerial)) {
    Serial.println("Connecting to DFPlayer Mini success!");
    player.volume(30);
  }
  else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  LINE.setToken(LINE_TOKEN);
  
  LINE.notify("Welcome, USER");

}

void loop()
{
  Blynk.run();
  printLocalTime();
  // Serial.println(digitalRead(button));
}

