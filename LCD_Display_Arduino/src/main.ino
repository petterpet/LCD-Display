#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

WiFiClient net;
PubSubClient client(net);

const char* mqtt_server = "192.168.x.x";
const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  while (WiFi.waitForConnectResult() != WL_CONNECTED);
  WiFi.begin(ssid, password);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hallo Welt!");

  delay(1000);
  lcd.clear();

  Serial.println("Setup beendet");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "LCD-Display";

    if (client.connect(clientId.c_str())) {
      client.subscribe("LCD-Display/#");

      Serial.println("MQTT verbunden");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String sTopic = String(topic);

  Serial.print("Empfange Topic: ");
  Serial.println(sTopic);

  payload[length] = '\0';
  String sValue = String((char*)payload);

  Serial.print("Empfange Wert: ");
  Serial.println(sValue);

  // Display
  if (sTopic.substring(sTopic.lastIndexOf("/") + 7) == "d") {
    // command
    Serial.println("command: " + sValue);

    if (sValue == "on") {
      lcd.backlight();
    }
    else if (sValue == "off") {
      lcd.noBacklight();
    }
    else if (sValue == "clear") {
      lcd.clear();
    }
  }
  else {
    // Text anzeigen
    Serial.println("Text: " + sValue);

    if (sTopic.substring(sTopic.lastIndexOf("/") + 5).toInt() == 1) {
      lcd.setCursor(0, 0);
      lcd.print(sValue);
    }
    else if (sTopic.substring(sTopic.lastIndexOf("/") + 5).toInt() == 2) {
      lcd.setCursor(0, 1);
      lcd.print(sValue);
    }
  }
}
