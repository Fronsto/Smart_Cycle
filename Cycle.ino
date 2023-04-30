#include <Wire.h>
#include <ESP8266WiFi.h> 
#include <MPU6050.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>

MPU6050 mpu;
int SCL_PIN=D1;
int SDA_PIN=D2;
int LED_PIN=D7;

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
const char* ssid = "nord1"; //ssid of your wifi
const char* password = "samit123"; //password of your wifi
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
WiFiServer server(80);

void setupGPS();
void sendGPSData();

void setupMPU();
void checkMPUSettings();
void setup() 
{
  Serial.begin(9600);
  
  setupMPU();
  checkMPUSettings();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // setupGPS();
}

void loop()
{
  Activites act = mpu.readActivites();
  if (act.isActivity)
  {
    digitalWrite(LED_PIN, HIGH);
    // Send gps data
    sendGPSData();
  } else
  {
    digitalWrite(LED_PIN, LOW);
  }


  delay(50);
}


