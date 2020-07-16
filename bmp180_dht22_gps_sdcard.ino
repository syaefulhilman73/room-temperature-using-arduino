//DHT22
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22

//BMP180
#include <SFE_BMP180.h>
#include <Wire.h>
#define ALTITUDE 1655.0

//GPS
#include <SoftwareSerial.h>
#include <TinyGPS.h>

//SD Card
#include <SD.h>
#include <SPI.h>

DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 pressure;
TinyGPS gps;
SoftwareSerial ss(4, 3);
File sensorData;

const int CSpin = 10;
String dataString ="";
float t,h,a,p,flat,flon,ti,ar,cep;

void saveData(){
   if(SD.exists("data.csv")){
     sensorData = SD.open("data.csv", FILE_WRITE);
     if (sensorData){
         sensorData.println(dataString);
         sensorData.close();
     }
   }
     else{
     Serial.println("Proses penulisan data gagal !");
     }
}

void sensor(){
  t = dht.readTemperature();
  h = dht.readHumidity();
  a = pressure.startTemperature();
  p = pressure.startPressure(3);
}

void modulgps(){
  gps.f_get_position(&flat, &flon);
  flat = TinyGPS::GPS_INVALID_F_ANGLE, 10, 6;
  flon = TinyGPS::GPS_INVALID_F_ANGLE, 11, 6;
  ti = gps.f_altitude();
  ar = gps.f_course();
  cep = gps.f_speed_kmph();
}
void setup() {
   Serial.begin(9600);
   pinMode(CSpin, OUTPUT);
}

void loop(){
   sensor();
   static char ts [8];
   static char hs [8];
   static char ps [8];
   static char lats [10];
   static char lons [10];
   static char tis [10];
   static char ars [10];
   static char ceps [10];
   dtostrf(t,3,2,ts);
   dtostrf(h,3,2,hs);
   dtostrf(p,3,2,ps);
   dtostrf(flat,3,2,lats);
   dtostrf(flon,3,2,lons);
   dtostrf(ti,3,2,tis);
   dtostrf(ar,3,2,ars);
   dtostrf(cep,3,2,ceps);
   dataString = String(ts) + "," + String(hs) + "," + String(ps) + "," + String(lats) + "," + String(lons) + "," + String(tis) + "," + String(ars) + "," + String(ceps);
   saveData();
   delay(1000);
}
