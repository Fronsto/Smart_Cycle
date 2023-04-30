#include <Wire.h> // This library allows you to communicate with I2C/TWI devices
#include <Digital_Light_TSL2561.h> 

int sda_pin = 0;  //Declaring the pin where the external LED will be connected
int scl_pin = 2;  // Declaring the inbuilt LED for a similar action
float value = 0;  // Declaring the intensity which will be outputted to the LEDs

void setup() {
  // pinMode(pwmPin, OUTPUT);  //Specifyin the pin 6 as output 
  pinMode(LED_BUILTIN, OUTPUT);  //Specifying the pin 13 as output
  Wire.begin(sda_pin,scl_pin);  //Initialising the wire library
  Serial.begin(74880); //Initialising the serial monitor
  TSL2561.init();  //Initialising the light sensor
}

void loop() {
  float lux = TSL2561.readVisibleLux();  //Reading the ambient light from the sensor to the pre-declared variable lux and printing it on the serial monitor
  Serial.print(" The ambient light level is: ");
  Serial.println(lux);
  
  //If the value of ambient light is less than 1000 increase the LED intensity linearly as the light intensity decreases else keep the light off
  if(lux<=500)
  {
   digitalWrite(LED_BUILTIN, LOW);
   
   Serial.println("LED ON");
   delay(1000);
   
  }else{
   digitalWrite(LED_BUILTIN, HIGH);
  }
  

  delay(300);
}




