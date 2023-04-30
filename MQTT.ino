void setupMQTT(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(MQTTcallback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266")) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  // client.subscribe("gunjan/gpsdata");
  // Serial.println("Subscribed successfully");
}

void MQTTcallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  Serial.print(message);
  if (message == "on") {
    Serial.println("got the message on");
    digitalWrite(LED_BUILTIN, LOW);
  } else if (message == "off") {
    Serial.println("got the message off");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266")) {
      Serial.println("Connected");
      client.subscribe("gunjan/test1");
    } else {
      Serial.print("Failed");
      Serial.println(client.state());
      delay(2000);
    }
  }
}