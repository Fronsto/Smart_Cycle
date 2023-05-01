#include <Wire.h>
#include <ESP8266WiFi.h> 
#include <MPU6050.h>
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
#include <Digital_Light_TSL2561.h> 
#include <PubSubClient.h>

int sda_pin_ldr = D2; 
int scl_pin_ldr = D1;
int BUZZ_TIME = 100;

MPU6050 mpu;
int SCL_PIN=D1;
int SDA_PIN=D2;
int LED_PIN=D7;
int LDR_LED = D3;
int ALARM_PIN = D0;

String lats = "";
String longs = "";
float lux;
bool isLocked;

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
// WiFiServer server(80);

const char* ssid = "Realme7";
const char* password = "poke1235";
const char* mqtt_server = "91.121.93.94";
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
  if(isLocked == false)
  {
    runLDR();
  }

  // digitalWrite(LED_PIN, HIGH);
  Vector normAccel = mpu.readNormalizeAccel();
  Activites act = mpu.readActivites();
  if (act.isActivity && isLocked)
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(ALARM_PIN, HIGH);
    Serial.println("*************ACTIVITY DETECTED while locked*********");
     
    // Serial.println(normAccel.XAxis);
    delay(BUZZ_TIME);
    digitalWrite(ALARM_PIN, LOW);
    // Send gps data
    // sendGPSData();
  } 
  else
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(ALARM_PIN, LOW);
  }
  if(!client.connected()){
    reconnect();
  }


  // sendGPSData();
  // lats = "abc";
  // longs = "abc";
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



