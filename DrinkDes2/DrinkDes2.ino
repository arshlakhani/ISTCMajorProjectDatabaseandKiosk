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

const int sw1 = 16;
const int sw2 = 17;
const int sw3 = 5;
const int sw4 = 18;

const int drink1 = 34;
const int drink2 = 35;
const int drink3 = 32;
const int drink4 = 33;

int drinkPour - 5000;
long pressDuration = 0;
long stepDuration = 50;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);
  pinMode(drink1, OUTPUT);
  pinMode(drink2, OUTPUT);
  pinMode(drink3, OUTPUT);
  pinMode(drink4, OUTPUT);

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
  sw1status = digitalRead(sw1);
  sw2status = digitalRead(sw2);
  sw3status = digitalRead(sw3);
  sw4status = digitalRead(sw4);
  long pressDuration1 = 0;
  long pressDuration2 = 0;
  long pressDuration3 = 0;
  long pressDuration4 = 0;
  while(sw1status == 0){
    pressDuration += stepDuration;
    delay(stepDuration);
  }
  if(pressDuration != 0){
    client.publish("sw1stat", String(pressDuration).c_str());
    pressDuration = 0;
    digitalWrite(drink1, HIGH);
    delay(drinkPour);
    digitalWrite(drink1, LOW);
  }

  while(sw2status == 0){
    pressDuration += stepDuration;
    delay(stepDuration);
  }
  if(pressDuration != 0){
    client.publish("sw2stat", String(pressDuration).c_str());
    pressDuration = 0;
    digitalWrite(drink2, HIGH);
    delay(drinkPour);
    digitalWrite(drink2, LOW);
  }

  while(sw3status == 0){
    pressDuration += stepDuration;
    delay(stepDuration);
  }
  if(pressDuration != 0){
    client.publish("sw3stat", String(pressDuration).c_str());
    pressDuration = 0;
    digitalWrite(drink3, HIGH);
    delay(drinkPour);
    digitalWrite(drink3, LOW);
  }
  
  while(sw4status == 0){
    pressDuration += stepDuration;
    delay(stepDuration);
  }
  if(pressDuration != 0){
    client.publish("sw4stat", String(stepDuration).c_str());
    pressDuration = 0;
    digitalWrite(drink4, HIGH);
    delay(drinkPour);
    digitalWrite(drink4, LOW);
  }
  

  
  
  client.loop();
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