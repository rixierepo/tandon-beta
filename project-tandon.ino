#include <DS3231.h>
#include <DHT.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define RELAY 1
#define pinDHT 2
#define pinPH 3
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY ""
#define DATABASE_URL "" 
 
DS3231 rtc(SDA, SCL); 
DHT dht(pinDHT, DHT11); //Pin, Jenis DHT
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long startingTime;
String tanggal;
String waktu;
float kelembaban;
float suhu;
int statusPengisian;
float volt;
float pHLevel;
int adcPH;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup()
{
  pinMode(RELAY, OUTPUT);
  pinMode(pinDHT, INPUT);
  pinMode(pinPH, INPUT);
  
  Serial.begin(9600); 
  rtc.begin(); 
  dht.begin();

  millisTime = millis();
  Serial.println("System Started at > " + startingTime);

  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set waktu otomatiss
  
  rtc.setDate(1, 10, 2022);   // set tanggal
  rtc.setTime(23, 59, 59);     // set waktu

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Network");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("OK");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
 
void loop(){ 
  
  // SENSOR PH
  adcPH = analogRead(pinPH);
  volt = adcPH * 5.0 / 1023;
  pHLevel = (6.4 * volt) - 5.7;

  // RTC
  tanggal = rtc.getDateStr(); // dd:mm:yy
  waktu = rtc.getTimeStr(); // hh:mm:ss

  // DHT11
  kelembaban = dht.readHumidity();
  suhu = dht.readTemperature();

  // RELAY
  statusPengisian = digitalRead(RELAY);

  if(statusPengisian != 1){
    Serial.println("Status Pengisian : OFF");
  }else{
    Serial.println("Status Pengisian : ON");
  }
  
  Serial.print(bulan + " | ");
  Serial.print(hari + " | "); 
  Serial.print(tanggal + " | ");
  Serial.println(waktu); 
  Serial.print("Suhu : " + suhu + " oC");
  Serial.println(" | Kelembaban : " + kelembaban + " %");
  
  if(waktu == "23:59:59"){
    digitalWrite(RELAY, HIGH);
  }
  if(waktu == "02:59:59"){
    digitalWrite(RELAY, LOW);
  }
  if(waktu == "05:59:59"){
    digitalWrite(RELAY, HIGH);
  }
  if(waktu == "08:59:59"){
    digitalWrite(RELAY, LOW);
  }
  if(waktu == "11:59:59"){
    digitalWrite(RELAY, HIGH);
  }
  if(waktu == "14:59:59"){
    digitalWrite(RELAY, LOW);
  }
  if(waktu == "17:59:59"){
    digitalWrite(RELAY, HIGH);
  }
  if(waktu == "20:59:59"){
    digitalWrite(RELAY, LOW);
  }

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
    Firebase.RTDB.setString(&fbdo, "data/tanggal", tanggal);
    Firebase.RTDB.setString(&fbdo, "data/waktu", waktu);
    Firebase.RTDB.setFloat(&fbdo, "data/ph", pHLevel);
    Firebase.RTDB.setFloat(&fbdo, "data/kelembaban", kelembaban);
    Firebase.RTDB.setFloat(&fbdo, "data/suhu", suhu);   
  }
}
