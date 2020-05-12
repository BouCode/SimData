#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MQTT.h>

#define t1 5000
int temperatura1;
int temperatura2;
int humedad1;
int humedad2;

const char ssid[] = "MOVISTAR_3D70";
const char pass[] = "9CyTCP6ZEDftPmgSs9xb";

String NODO = String ("\"NODO1\"");

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("SimulacionData", "bdc2f847", "7d44be25ef8cf793")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);

  randomSeed(analogRead(0));
  connect();
}

void loop () {
  temperatura1 = random (20, 30);
  humedad1 = random (60, 70);
  temperatura2 = random (20, 40);
  humedad2 = random (60, 80);
  
  String temp1 = String (temperatura1);
  String hum1 = String (humedad1);
  String temp2 = String (temperatura2);
  String hum2 = String (humedad2);
  
  String convertJSON = String ("{" + NODO + ":{\"data\": [" + temp1 + "," + hum1 + "]" + "[" + temp2 + "," + hum2 + "]}}");
  Serial.println (convertJSON);
  client.loop();
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.

 
  //createJson ("NODO1", temperatura1, humedad1, temperatura2, humedad2);
    if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", convertJSON);
  }
  delay (t1);
} 
