#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "html.h"
#define Rx D3
#define Tx D4
ESP8266WebServer webServer(80);
SoftwareSerial mySerial(Rx, Tx); 
char* ssid = "ESP";
char* pass = "12345678";
const char* mqtt_server = "192.168.250.100";
const int mqtt_port = 1883;

const char* client_id = "ESP8266_00";
const char* switch_topic = "switch";
const char* giong_noi = "voice";
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // Chuyển đổi payload từ dạng byte sang chuỗi
  String message = "";
  for (int i = 0; i < length; i++) {
  message += (char)payload[i];
  }
  Serial.println(message);
  if (strcmp(topic, switch_topic) == 0) {
     if (message == "batdenkhach") {
      digitalWrite(D7, LOW);
    } else if (message == "tatdenkhach") {
      digitalWrite(D7, HIGH);
    }
  }
}

void reconnect() {
// Vòng lặp kết nối lại đến broker MQTT
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");

// Kết nối đến broker MQTT
if (client.connect(client_id)) {
  Serial.println("connected");
  client.subscribe(switch_topic);
  // client.publish(giong_noi);
} else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  delay(5000);
}
}
}
void setup() {
  pinMode(D7, OUTPUT);
  digitalWrite(D7,HIGH);
  mySerial.begin(9600);
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  webServer.on("/", [](){
    String s = FPSTR(MainPage);
    webServer.send(200, "text/html", s);
  });
    webServer.on("/oncua", [](){
    mySerial.print("dooron");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offcua", [](){
    mySerial.print("dooroff");
    webServer.send(200, "text/plain");
  });
  webServer.on("/ondenkhach", [](){
    client.publish(switch_topic,"batdenkhach");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offdenkhach", [](){
    client.publish(switch_topic,"tatdenkhach");
    webServer.send(200, "text/plain");
  });
  webServer.on("/onquatkhach", [](){
    client.publish(switch_topic,"batquatkhach");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offquatkhach", [](){
    client.publish(switch_topic,"tatquatkhach");
    webServer.send(200, "text/plain");  
  });
    webServer.on("/ondenngu", [](){
    client.publish(switch_topic,"batdenngu");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offdenngu", [](){
    client.publish(switch_topic,"tatdenngu");
    webServer.send(200, "text/plain");
  });
    webServer.on("/onquatngu", [](){
    client.publish(switch_topic,"batquatngu");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offquatngu", [](){
    client.publish(switch_topic,"tatquatngu");
    webServer.send(200, "text/plain");
  });
    webServer.on("/onphongtam", [](){
    client.publish(switch_topic,"batphongtam");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offphongtam", [](){
    client.publish(switch_topic,"tatphongtam");
    webServer.send(200, "text/plain");
  });
    webServer.on("/onsanphoi", [](){
    client.publish(switch_topic,"batsanphoi");
    webServer.send(200, "text/plain");
  });
  webServer.on("/offsanphoi", [](){
    client.publish(switch_topic,"tatsanphoi");
    webServer.send(200, "text/plain");
  });
    webServer.on("/onvoice", [](){
    client.publish("voice","batgiongnoi");
    webServer.send(200, "text/plain");
  });
    webServer.on("/offvoice", [](){
    client.publish("voice","tatgiongnoi");
    webServer.send(200, "text/plain");
  });
  webServer.begin();
}
void loop() {
  webServer.handleClient();
  if (!client.connected()) {
  reconnect();
  }
  client.loop();
}