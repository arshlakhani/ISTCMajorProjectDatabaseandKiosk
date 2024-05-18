/*
  IoT Club - ISTC Workshop
  Controlling LED with MQTT

  This code demonstrates how to publish data to a specific MQTT topic.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Update these with your Wi-Fi credentials
const char* ssid = "ConForNode1";
const char* password = "12345678";

// MQTT Broker settings
const char* mqtt_server = "ec2-44-204-194-140.compute-1.amazonaws.com";
const int mqtt_port = 1883;

#define error 0 
#define serverRequest 1
#define defaultReq 2

#define highStatus 1
#define lowStatus 0

const int upirpins[4] = {15, 2, 4, 5};
const int downirpins[4] = {13, 12, 14, 27};
bool upStatus[4] = {0, 0, 0, 0};
bool downStatus[4] = {0, 0, 0, 0};
const int ledpins[4] = {18, 19, 21, 22};
bool status[4] = {0, 0, 0, 0};

WiFiClient espClient;
PubSubClient client(espClient);
void connectToMQTT() {
  while (!client.connected()) {  
    Serial.println("Connecting to MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe("ingredientData");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.printf("Message arrived [%s] %s\n", topic, message.c_str());

  int receivedStatus = message.toInt();
  for (int i = 0; i < 4; i++) {
    status[i] = receivedStatus;
  }
}

void ledIndicator(int pinNo, int stat) {
  bool temp = 0;
  if (stat == error) {
    for (int i = 0; i < 10; i++) {
      digitalWrite(pinNo, temp);
      temp = !temp;
      delay(100);
    }
  } else if (stat == serverRequest) {
    for (int i = 0; i <= 255; i += 5) {
      analogWrite(pinNo, i);
      delay(10);
    }
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(pinNo, i);
      delay(10);
    }
  } else if (stat == defaultReq) {
    digitalWrite(pinNo, HIGH);
    delay(100);
  }
}

void refreshStatus() {
  for (int i = 0; i < 4; i++) {
    upStatus[i] = digitalRead(upirpins[i]);
    downStatus[i] = digitalRead(downirpins[i]);
  }
  Serial.println("Status refreshed");
}
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(upirpins[i], INPUT);
    pinMode(downirpins[i], INPUT);
    pinMode(ledpins[i], OUTPUT);
  }
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  connectToMQTT();
}

void loop() {
  client.loop();
  refreshStatus();
  for (int k = 0; k < 4; k++) {
    if (status[k] == highStatus) {
      if (upStatus[k] == highStatus) {
        status[k] = lowStatus;
        Serial.printf("%d has been set to low\n", k);
      } else {
        ledIndicator(ledpins[k], serverRequest);
      }
    } else if (downStatus[k] == lowStatus) {
      ledIndicator(ledpins[k], error);
      Serial.println("error");
    } else {
      ledIndicator(ledpins[k], defaultReq);
      Serial.println("defaultReq");
    }
  }
}


