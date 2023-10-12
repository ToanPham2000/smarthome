#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>
#include <AccelStepper.h>
#include "html.h"

#define DHT1PIN D3
#define DHT2PIN D4
#define DHTTYPE DHT11

#define IN1 D5
#define IN2 D6
#define IN3 D7
#define IN4 D8
const int stepsPerRevolution = 2048;  //quay 1 vòng
const int totalSteps = stepsPerRevolution * 2;  // quay 2 vòng thuận
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);
int rain;
int INPUT_CBM = A0;
const float maxTemperature = 27.0;
const float minTemperature = 24.0;
bool autoMode = false;
ESP8266WebServer webServer(80);
char* ssid = "ESP";
char* pass = "12345678";
const char* mqtt_server = "192.168.250.100";
const int mqtt_port = 1883;
float temperature1, temperature2;
float humidity1, humidity2;
DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
const char* client_id = "ESP8266_01";
const char* switch_topic = "switch";
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void getReadings() {
  temperature1 = dht1.readTemperature();
  humidity1 = dht1.readHumidity();
  temperature2 = dht2.readTemperature();
  humidity2 = dht2.readHumidity();
  if (isnan(temperature1) || isnan(humidity1) || isnan(temperature2) || isnan(humidity2)) {
    // Serial.println("Lỗi nhiệt!");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("T1:");
  lcd.print(round(temperature1 * 10) / 10.0, 0);  
  lcd.write(0xDF);
  lcd.print("C ");
  lcd.setCursor(9, 0);
  lcd.print("H1:");
  lcd.print(round(humidity1 * 10) / 10.0, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("T2:");
  lcd.print(round(temperature2 * 10) / 10.0, 0); 
  lcd.write(0xDF);
  lcd.print("C ");
  lcd.setCursor(9, 1);
  lcd.print("H2:");
  lcd.print(round(humidity2 * 10) / 10.0, 0);
  lcd.print("%");

}
void CBM(){
  rain = analogRead(INPUT_CBM);
  // Serial.println(rain);
  static unsigned char sttRain = 0;
  if (rain <400 ) {
    if (sttRain == 0) {
      sttRain = 1;
      stepper.setCurrentPosition(0);
      // stepper.setSpeed(1000);
      stepper.runSpeed();
      stepper.runToNewPosition(4096);
    }
  } else {
    if (sttRain == 1) {
      sttRain = 0;
      stepper.setCurrentPosition(4096);
      // stepper.setSpeed(-1000);
      stepper.runSpeed();
      stepper.runToNewPosition(0);
    }
  }
  delay(1000);
}
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);
  if (strcmp(topic, switch_topic) == 0) {
    if (message == "batthuquanao") {
      stepper.setCurrentPosition(0);
      stepper.runSpeed();
      stepper.runToNewPosition(4096);
    } else if (message == "tatthuquanao") {
      stepper.setCurrentPosition(4096);
      stepper.runSpeed();
      stepper.runToNewPosition(0);
    } else if (message == "battudong") {
      autoMode = true;

    } else if (message == "tattudong") {
      autoMode = false;
      client.publish(switch_topic,"tatquatkhach");
      client.publish(switch_topic,"tatquatngu");

    }
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(client_id)) {
      Serial.println("Connected to MQTT broker.");
      client.subscribe(switch_topic);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(INPUT_CBM, INPUT);
  // cài tốc độ 
  stepper.setMaxSpeed(1000.0); // Tốc độ tối đa
  stepper.setAcceleration(2000.0); 
  dht1.begin();
  dht2.begin();
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  webServer.on("/", [](){
    String s = FPSTR(MainPage);
    webServer.send(200, "text/html", s);
  });
    webServer.on("/docnhietdo1", [](){
    // float temperature1 = dht1.readTemperature();
      String s = String(temperature1);
      webServer.send(200, "text/plain", s);
  });
  webServer.on("/docdoam1", [](){
    // float humidity1 = dht1.readHumidity();
      String s = String(humidity1);
      webServer.send(200, "text/plain", s);
  });
  webServer.on("/docnhietdo2", [](){
    // float temperature2 = dht2.readTemperature();
      String s = String(temperature2);
      webServer.send(200, "text/plain", s);
  });
  webServer.on("/docdoam2", [](){
    // float humidity2 = dht2.readHumidity();
      String s = String(humidity2);
      webServer.send(200, "text/plain", s);
  });
  webServer.begin();
}

void loop() {
  getReadings();
  if (autoMode) {
    CBM();
    static unsigned char stt1 = 0;
    static unsigned char stt2 = 0;
    if (temperature1 > maxTemperature) {
      if(stt1 == 0){
      stt1 = 1;
      // Bật quạt
      client.publish(switch_topic,"batquatkhach");
      }
    } else if (temperature1 < minTemperature) {
      stt1 = 0;
      client.publish(switch_topic,"tatquatkhach");
    }
    if (temperature2 > maxTemperature) {
      if(stt2 == 0){
      stt2 = 1;
      client.publish(switch_topic,"batquatngu");
      }
    } else if (temperature2 < minTemperature) {
      stt2 = 0;
      client.publish(switch_topic,"tatquatngu");
    }
    // delay(5000);
  }
  webServer.handleClient();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}