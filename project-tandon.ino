#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

#include <SimpleDHT.h>
#include <Wire.h>
#include "RTClib.h"

#define pinDHT 2

RTC_DS3231 rtc;
SimpleDHT22 dht22(pinDHT); 

AsyncWebServer server(80);

const char* ssid = "SYAFALIO"; // Your WiFi SSID
const char* password = "03102010"; // Your WiFi Password

int pinDHT22 = 2;
int err = SimpleDHTErrSuccess;
float temperature = 0;
float humidity = 0;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

void setup () {

  Serial.begin(115200);
  pinMode(pinDHT, INPUT);

  delay(3000); 

  WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    server.begin();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
  }
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(", ");

    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print('\t');

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); 
    Serial.println(err);
    delay(2000);
  return;
  }
  Serial.print("OK > ");
  Serial.print("Suhu : "); 
  Serial.print((float)temperature); 
  Serial.println(" *C, ");
  Serial.print("Kelembaban : "); 
  Serial.print((float)humidity); 
  Serial.println(" RH%");
  Serial.println(" ");

  delay(1000);
}

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
}
