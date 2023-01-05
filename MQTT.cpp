#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Emboss";
const char* password = "12345678";
const char* mqtt_host = "192.168.209.170";
const char* clientId = "esp8266";
const char* username = "kosu";
const char* pass = "koosu";
const char* topicname = "controldevice";
const char* topicsub = "server";
const int mqtt_port = 1883;


WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Message received [ ");
  Serial.print(topic);
  Serial.println("]");

  for (int i =0;i<length;i++){
    Serial.println((char)payload[i]);
  }
  Serial.println();

  if((char)payload[0]=='1'){
    digitalWrite(BUILTIN_LED, LOW);
  }else{
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void reconnect(){
  while (!client.connected())
  {
    Serial.println("Attempting MQTT Connection...");
    
    if(client.connected()){
      client.connect(clientId, username, pass);
      Serial.println("Client Connected");
    }else{
      Serial.print("Failed, ");
      Serial.print(client.state());
      Serial.println("\nTrying again in 5 Seconds...");

      delay(5000);
    }
  }

  client.publish(topicname, "HelloWorld");
  client.subscribe(topicsub);
  
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  client.setServer(mqtt_host, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
}