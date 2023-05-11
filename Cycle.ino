#include <Wire.h>
#include <ESP8266WiFi.h>
#include <MPU6050.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
#include <Digital_Light_TSL2561.h> // library to handle the Light Sensor
#include <PubSubClient.h>          // library to handle MQTT

int sda_pin_ldr = D2; // pin for SDA for LDR sensor
int scl_pin_ldr = D1; // pin for SCL for LDR sensor
int BUZZ_TIME = 100;  // time for which buzzer will buzz

MPU6050 mpu;        // The MPU6050 object
int SCL_PIN = D1;   // SCL pin for MPU6050
int SDA_PIN = D2;   // SDA pin for MPU6050
int LED_PIN = D7;   // LED pin for the tailight
int LDR_LED = D3;   // LED pin for the headlight
int ALARM_PIN = D0; // Buzzer pin

String lats = "";
String longs = "";
float lux;     // variable to store the ambient light value
bool isLocked; // variable to store the lock status

TinyGPSPlus gps;         // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
float latitude, longitude;
int year, month, date, hour, minute, second;
String date_str, time_str, lat_str, lng_str;
int pm;

const char *ssid = "Realme7";
const char *password = "poke1235";
const char *mqtt_server = "91.121.93.94";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void setupGPS();
void getGPSData();

void setupMPU();
void checkMPUSettings();

void setupLDR();
void runLDR();

void setupMQTT();
void reconnect();

void setup()
{
  Serial.begin(9600);
  Serial.println("started");
  setupMPU();
  checkMPUSettings();

  pinMode(LED_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(ALARM_PIN, LOW);
  setupLDR();
  setupMQTT();
  // setupGPS();
  isLocked = true;
  Serial.println("setup done");
}

void loop()
{
  Serial.println("Looping...");
  // getGPSData();
  if (isLocked == false)
  {
    runLDR();
  }

  Vector normAccel = mpu.readNormalizeAccel();
  Activites act = mpu.readActivites();
  if (act.isActivity && isLocked)
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(ALARM_PIN, HIGH);
    Serial.println("*************ACTIVITY DETECTED while locked*********");
    delay(BUZZ_TIME);
    digitalWrite(ALARM_PIN, LOW);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(ALARM_PIN, LOW);
  }
  if (!client.connected())
  {
    reconnect();
  }

  Serial.println("Sending MQTT data..");
  char buf[20];
  dtostrf(latitude, 3, 6, buf);
  client.publish("gunjan/latitude", buf);
  dtostrf(longitude, 3, 6, buf);
  client.publish("gunjan/longitude", buf);
  dtostrf(normAccel.XAxis, 3, 6, buf);
  client.publish("gunjan/accl_x", buf);
  dtostrf(normAccel.YAxis, 3, 6, buf);
  client.publish("gunjan/accl_y", buf);
  dtostrf(normAccel.ZAxis, 3, 6, buf);
  client.publish("gunjan/accl_z", buf);
  dtostrf(lux, 3, 6, buf);
  client.publish("gunjan/lux", buf);
  delay(1000);
  client.loop();
}
