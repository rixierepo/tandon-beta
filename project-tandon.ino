#include <RTClib.h>

#define triggerRelay 1
#define dataSuhu 2
#define dataKelembaban 5
#define dataPH 3

uint8_t jam0 = 0;
uint8_t jam3 = 3;
uint8_t jam6 = 6;
uint8_t jam9 = 9;
uint8_t jam12 = 12;
uint8_t jam15 = 15;
uint8_t jam18 = 18;
uint8_t jam21 = 21;
uint8_t menit = 0;

//uint8_t jamPertama = 00;
//uint8_t menitPertama = 00;
//uint8_t jamKedua = 03;
//uint8_t menitKedua = 00;
//uint8_t jamKetiga = 06;
//uint8_t menitKetiga = 00;
//uint8_t jamKeempat = 09;
//uint8_t menitKeempat = 00;
//uint8_t jamKelima = 12;
//uint8_t menitKelima = 00;
//uint8_t jamKeenam = 15;
//uint8_t menitKeenam = 00;
//uint8_t jamKetujuh = 18;
//uint8_t menitKetujuh = 00;
//uint8_t jamKedelapan = 21;
//uint8_t menitKedelapan = 00;

RTC_DS3231 rtc;

char dayOfTheWeek[7][12] = {
  "MINGGU",
  "SENIN",
  "SELASA",
  "RABU",
  "KAMIS",
  "JUMAT",
  "SABTU"
};

void setup () {
  Serial.begin(9600);

  pinMode(triggerRelay, OUTPUT);
  pinMode(dataKelembaban, INPUT);
  pinMode(dataPH, INPUT);
  pinMode(dataSuhu, INPUT);

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("RTC is Unavailable");
    while (1);
  }

  // set waktu otomatis
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // set waktu manual
  // format (tahun, bulan, hari, jam, 0, 0)
  // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));

}

void loop () {
  DateTime now = rtc.now();

  if (now.hour() == jam0 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
    
  }else if(now.hour() == jam3 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
    
  }else if(now.hour() == jam6 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
  
  }else if(now.hour() == jam9 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");

  }else if(now.hour() == jam12 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
    
  }else if(now.hour() == jam15 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");

  }else if(now.hour() == jam18 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
    
  }else if(now.hour() == jam21 && now.minute() == menit){
    digitalWrite(triggerRelay, HIGH);
    Serial.println("relay on");
    delay(15000);
    digitalWrite(triggerRelay, LOW);
    Serial.println("relay off");
  }
  
  printTime(now);
}

void printTime(DateTime time) {
  Serial.print(time.year(), DEC);
  Serial.print('/');
  Serial.print(time.month(), DEC);
  Serial.print('/');
  Serial.print(time.day(), DEC);
  Serial.print(" (");
  Serial.print(dayOfTheWeek[time.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(time.hour(), DEC);
  Serial.print(':');
  Serial.print(time.minute(), DEC);
  Serial.print(':');
  Serial.println(time.second(), DEC);
}
