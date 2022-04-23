#include "DS1302.h"

//RTC(SCLK, IO, CE)
DS1302 RTC(11, 12, 13);

void setup() {
  Serial.begin(9600);
  /*
  RTC.setYear(22);
  RTC.setMonth(4);
  RTC.setDate(23);
  RTC.setDay(6);
  
  RTC.setHoursMode(1);
  RTC.setSeconds(30);
  RTC.setMinutes(11);
  RTC.setHours(2);
  */
  RTC.enable();
}

void loop() {
  Serial.print("20");
  Serial.print(RTC.getYear());
  Serial.print("/");
  Serial.print(RTC.getMonth());
  Serial.print("/");
  Serial.print(RTC.getDate());
  Serial.print("  ");
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.println(RTC.getSeconds());
  delay(50);

}
