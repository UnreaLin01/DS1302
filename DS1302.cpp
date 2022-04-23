#include "Arduino.h"
#include "DS1302.h"

DS1302::DS1302(byte sclk, byte io, byte ce){
    _SCLK = sclk;
    _IO = io;
    _CE = ce;

    pinMode(_SCLK, OUTPUT);
    pinMode(_CE, OUTPUT);
    digitalWrite(_SCLK, LOW);
    digitalWrite(_CE, LOW);
}

byte DS1302::bcdToDec(byte bcd){
    return (bcd >> 4) * 10 + (bcd & 0b00001111);
}

byte DS1302::decToBcd(byte dec){
    dec = constrain(dec, 0, 99);
    return ((dec / 10) << 4) | (dec % 10);
}

void DS1302::nextBit(){
    digitalWrite(_SCLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(_SCLK, LOW);
    delayMicroseconds(1);
}

void DS1302::write(byte targetRegister, byte data){
    digitalWrite(_CE, HIGH);
    delayMicroseconds(1);

    pinMode(_IO, OUTPUT);
    delayMicroseconds(1);
    for(int x = 0; x < 8; x++){
        digitalWrite(_IO, (targetRegister & 0x0b00000001) == 1);
        targetRegister = targetRegister >> 1;
        nextBit();
    }

    for(int x = 0; x < 8; x++){
        digitalWrite(_IO, (data & 0x0b00000001) == 1);
        data = data >> 1;
        nextBit();
    }

    digitalWrite(_CE, LOW);
    delayMicroseconds(1);
}

byte DS1302::read(byte targetRegister){
    digitalWrite(_CE, HIGH);
    delayMicroseconds(1);
    
    pinMode(_IO, OUTPUT);
    delayMicroseconds(1);
    for(int x = 0; x < 8; x++){
        digitalWrite(_IO, (targetRegister & 0x0b00000001) == 1);
        targetRegister = targetRegister >> 1;
        nextBit();
    }

    byte data = 0;
    pinMode(_IO, INPUT);
    delayMicroseconds(1);
    for(int x = 0; x < 8; x++){
        if(digitalRead(_IO)){data = data | (0b00000001 << x);}
        nextBit();
    }
    
    digitalWrite(_CE, LOW);
    delayMicroseconds(1);

    return data;
}

void DS1302::enable(){
    write(0b10000000, (read(0b10000001) & 0b01111111));
}

void DS1302::disable(){
    write(0b10000000, (read(0b10000001) & 0b01111111) | 0b10000000);
}

void DS1302::setHoursMode(boolean mode){
    if(mode){
        write(0b10000100, (read(0b10000101) & 0b01111111) | 0b10000000);
    }else{
        write(0b10000100, (read(0b10000101) & 0b01111111));
    }
}

void DS1302::setSeconds(byte seconds){
    seconds = constrain(seconds, 0, 59);
    write(0b10000000, ((read(0b10000001) & 0b10000000) | decToBcd(seconds)));
}

void DS1302::setMinutes(byte minutes){
    minutes = constrain(minutes, 0, 59);
    write(0b10000010, decToBcd(minutes));
}

void DS1302::setHours(byte hours){
    if(getHoursMode()){
        hours = constrain(hours, 1, 12);
        write(0b10000100, 0b10000000 | decToBcd(hours));
    }else{
        hours = constrain(hours, 0, 23);
        write(0b10000100, decToBcd(hours));
    }
}

void DS1302::setDay(byte day){
    day = constrain(day, 1, 7);
    write(0b10001010, decToBcd(day));
}

void DS1302::setDate(byte date){
    date = constrain(date, 1, 31);
    write(0b10000110, decToBcd(date));
}

void DS1302::setMonth(byte month){
    month = constrain(month, 1, 12);
    write(0b10001000, decToBcd(month));
}

void DS1302::setYear(byte year){
    year = constrain(year, 0, 99);
    write(0b10001100, decToBcd(year));
}

boolean DS1302::getHoursMode(){
    return (read(0b10000101) & 0b10000000) == 0b10000000;
}

byte DS1302::getSeconds(){
    return bcdToDec((read(0b10000001) & 0b01111111));
}

byte DS1302::getMinutes(){
    return bcdToDec(read(0b10000011));
}

byte DS1302::getHours(){
    if(getHoursMode()){
        return bcdToDec(read(0b10000101) & 0b00011111);
    }else{
        return bcdToDec(read(0b10000101) & 0b00111111);
    }
}

byte DS1302::getDay(){
    return bcdToDec(read(0b10001011));
}

byte DS1302::getDate(){
    return bcdToDec(read(0b10000111));
}

byte DS1302::getMonth(){
    return bcdToDec(read(0b10001001)); 
}

byte DS1302::getYear(){
    return bcdToDec(read(0b10001101));
}
