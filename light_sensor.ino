

void setupLDR() {
  // pinMode(pwmPin, OUTPUT);  //Specifyin the pin 6 as output 
  Serial.begin(9600); //Initialising the serial monitor
  Serial.println("Setting up the Light sensor");
  pinMode(LED_BUILTIN, OUTPUT);  //Specifying the pin 13 as output
  Wire.begin(sda_pin_ldr,scl_pin_ldr);  //Initialising the wire library
  TSL2561.init();  //Initialising the light sensor
  Serial.println("LDR sensor completed setting");
}

void runLDR() {
  float lux = TSL2561.readVisibleLux();  //Reading the ambient light from the sensor to the pre-declared variable lux and printing it on the serial monitor
  Serial.print(" The ambient light level is: ");
  Serial.println(lux);
  
  //If the value of ambient light is less than 1000 increase the LED intensity linearly as the light intensity decreases else keep the light off
  if(lux<=500)
  {
   digitalWrite(LED_BUILTIN, LOW);
   
  //  Serial.println("LED ON");
  //  delay(1000);
   
  }else{
   digitalWrite(LED_BUILTIN, HIGH);
   Serial.println("LED OFF");
  }
}




