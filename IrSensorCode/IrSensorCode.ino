/*
  IoT Club - ISTC Workshop
  Controlling LED with MQTT

  This code demonstrates how to publish data to a specific MQTT topic .
*/

#include <WiFi.h>
#include <PubSubClient.h>

// Update these with your Wi-Fi credentials
const char* ssid = "ConForNode1";
const char* password = "12345678";

// MQTT Broker settings
const char* mqtt_server = "192.168.1.50";
const int mqtt_port = 1883;

const int irSen[8] = [1,2,3,4,5,6,7,8];
const int ledpins[4] = [9,10,11,12];

int drinkPour - 5000;
long pressDuration = 0;
long stepDuration = 50;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  for(int i = 0;i<8;i++){
    pinMode(irSen[i],INPUT);
  }
  for(int i = 0;i<4;i++){
    pinMode(ledpins[i],OUTPUT);
  }

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

/**
 * Function to continuously check the connection status, 
 * and reconnect to MQTT if not connected. 
 */
void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  
}

/**
 * Function to establish connection to MQTT server.
 *
 * @return void
 *
 * @throws None
 */
void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker!");
     
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// Callback function for received MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

}