# Smart Cycle Project
## CS321 - Smart Systems Lab 2023 Course Project
### Group Members:
- [Anindya Vijayvargeeya](https://github.com/Fronsto)
- [Gunjan Dhanuka](https://github.com/GunjanDhanuka)
- [Pranjal Singh](https://github.com/pranjal198)

## Files and their uses
- `Cycle.ino`: The main driver code that calls all the helper functions and runs the actual `setup` and `loop` functions. It also contains the MQTT commands to send data to the appropriate channels.
- `GPS_Module.ino`: The code to setup the GPS sensor using SerialStream and then parse the data coming from that stream to get the latitude and longitude.
- `MPU_Module.ino`: The code to setup the MPU6050 sensor, and then set the configuration values. It also has the `checkMPUSettings` function that runs a suite of tests on the MPU and prints the values of various parameters obtained from the Accelerometer and Gyroscope.
- `MQTT.ino`: The code to connect the NodeMCU to an MQTT Broker, and make it subscribe to the required channels to receive data. It also contains the `MQTTcallback` function that is fired whenever the MQTT client receives a message on one of its subscribed channels. The `reconnect` function tries to re-connect to the broker automatically incase there is a connection drop.
- `light_sensor.ino`: The code is to setup the Grove Digital Light Sensor using the TSL2561 library. The `runLDR()` function reads the Ambient Light value in lux and if it falls below a certain threshold (here, 500 lux) then it turns on the LED connected to the headlight of the cycle. When the ambient light is above that threshold, it turns that LED back off.
- `ESP8266_MPU6050-master.zip`: This library is used to interface the MPU6050 sensor with the IDE.
- `TinyGPSPlus-1.0.2.zip`: This library is used to interface the GPU sensor and interpret the GPS values.
