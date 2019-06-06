#include <SPI.h>
#include <MFRC522.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define RST_PIN D1
#define SS_PIN D2

#define RED D0
#define GREEN D3
#define BLUE D4

const char *service_endpoint = "http://3.211.115.166/api/make_transaction";

const int cost = -10;

WiFiClient client;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect("RestaurantRFID");

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reading UID");
}

void loop() {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);

  int new_card = mfrc522.PICC_IsNewCardPresent();
  if (!new_card)
    return;

  int read_card = mfrc522.PICC_ReadCardSerial();
  if (!read_card)
    return;

  unsigned long uid = getID();
  Serial.print("Card uid: ");
  Serial.println(uid);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Will not make request");
    return;
  }

  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 100);

  Serial.println("Making http request");

  String body = "{\"value\":" + String(cost) + ",\"rfid\":" + String(uid) + "}";
  HTTPClient http;

  http.begin(service_endpoint);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(body);
  String payload = http.getString();

  Serial.print("HTTP code: ");
  Serial.println(httpCode);

  if (httpCode == 200) {
    Serial.print("Payload: ");
    Serial.println(payload);

    analogWrite(RED, 0);
    analogWrite(GREEN, 100);
    analogWrite(BLUE, 0);

    delay(2000);
  }else{
    analogWrite(RED, 100);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);

    delay(1000);
  }

  http.end();
}

unsigned long getID(){
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA();
  return hex_num;
}