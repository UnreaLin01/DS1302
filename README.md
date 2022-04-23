# DS1302
DS1302 RTC Communication Library For Arduino By William Lin\
The DS1302 Chip Do Include Further RAM Memory\
But This Library Doesn't include RAM Access Function\


### Initialize Function
```
DS1302 RTC(byte SCLK, byte IO, byte CE);
```
### Chip Setting/Reading Function
```
void enable();
void disable();
void setHoursMode(boolean mode);
boolean getHoursMode();
```

### Time Setting Function
```
void setYear(byte year);
void setMonth(byte month);
void setDate(byte date);
void setDay(byte day);
void setHours(byte hours);
void setMinutes(byte minutes);
void setSeconds(byte seconds);
```
### Time Reading Function
```
byte getYear();
byte getMonth();
byte getDate();
byte getDay();
byte getHours();
byte getMinutes();
byte getSeconds();
```
