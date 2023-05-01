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
  client.subscribe("gunjan/lock");
  Serial.println("Subscribed successfully");
}

void lock(){
  digitalWrite(LDR_LED, LOW);
  // digitalWrite(ALARM_PIN, LOW);
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
  if (message == "lock") {
    Serial.println("Cycle is locked!");
    isLocked = true;
    lock();
  } else if (message == "unlock") {
    Serial.println("Cycle is unlocked!");
    isLocked = false;
  }
  Serial.println();
  Serial.println("-----------------------");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed");
      Serial.println(client.state());
      delay(2000);
    }
  }
}