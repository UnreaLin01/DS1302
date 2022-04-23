#ifndef DS1302_h
#define DS1302_h

#include "Arduino.h"

class DS1302{
    public:
        DS1302(byte sclk, byte io, byte ce);

        void enable();
        void disable();

        void setYear(byte year);
        void setMonth(byte month);
        void setDate(byte date);
        void setDay(byte day);
        void setHours(byte hours);
        void setMinutes(byte minutes);
        void setSeconds(byte seconds);

        byte getYear();
        byte getMonth();
        byte getDate();
        byte getDay();
        byte getHours();
        byte getMinutes();
        byte getSeconds();

        void setHoursMode(boolean mode);
        boolean getHoursMode();

    private:
        byte bcdToDec(byte bcd);
        byte decToBcd(byte dec);
        void nextBit();
        void write(byte targetRegister, byte data);
        byte read(byte targetRegister);

        byte _SCLK = 0;
        byte _IO = 0;
        byte _CE = 0;

};

#endif
