#ifndef TIME_DATE_H
#define TIME_DATE_H

unsigned char rtc_read(unsigned char reg);
unsigned char bcd_to_dec(unsigned char bcd);
void cmd_time();


#endif