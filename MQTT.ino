// setup the MQTT Client
void setupMQTT()
{
  WiFi.begin(ssid, password); // Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED)
  {
    // trying to connect to the network until the status is WL_CONNECTED
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  digitalWrite(ALARM_PIN, HIGH);
  delay(30);
  digitalWrite(ALARM_PIN, LOW);

  Serial.println(WiFi.SSID());
  client.setServer(mqtt_server, mqtt_port); // Connect to MQTT Broker
  client.setCallback(MQTTcallback);
          // Set callback function for MQTT client
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266"))
    {
      Serial.println("connected");
      digitalWrite(ALARM_PIN, HIGH);
      delay(30);
      digitalWrite(ALARM_PIN, LOW);
    }
    else
    {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.subscribe("gunjan/lock"); // Subscribe to the topic that is used to unlock
  Serial.println("Subscribed successfully");
}

void lock()
{
  // when cycle is locked, the headlight needs to turned off.
  digitalWrite(LDR_LED, LOW);
}

// The Callback function is fired when the MQTT client receives a message.
void MQTTcallback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String message;

  // store the payload in the string
  for (int i = 0; i < length; i++)
  {
    message = message + (char)payload[i];
  }
  Serial.print(message);

  // if the message is "lock", then lock the cycle
  if (message == "lock")
  {
    Serial.println("Cycle is locked!");
    isLocked = true;
    lock();
    digitalWrite(ALARM_PIN, HIGH);
    delay(40);
    digitalWrite(ALARM_PIN, LOW);
  }
  // if the message is "unlock", then unlock the cycle
  else if (message == "unlock")
  {
    Serial.println("Cycle is unlocked!");
    isLocked = false;
    digitalWrite(ALARM_PIN, HIGH);
    delay(30);
    digitalWrite(ALARM_PIN, LOW);
    delay(80);
    digitalWrite(ALARM_PIN, HIGH);
    delay(30);
    digitalWrite(ALARM_PIN, LOW);
  }
  Serial.println();
  Serial.println("-----------------------");
}

// Function to reconnect to the MQTT Broker incase the connection breaks
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266"))
    {
      Serial.println("Connected");
      digitalWrite(ALARM_PIN, HIGH);
      delay(30);
      digitalWrite(ALARM_PIN, LOW);
    }
    else
    {
      Serial.print("Failed");
      Serial.println(client.state());
      delay(2000);
    }
  }
}