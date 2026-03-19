#include <io.h>
#include <time_date.h>
#include <str.h>



unsigned char rtc_read(unsigned char reg) {
    outb(0x70, reg);       // sélectionne le registre
    return inb(0x71);      // lit la valeur
}

unsigned char bcd_to_dec(unsigned char bcd) {
    return ((bcd / 16) * 10) + (bcd & 0x0F);
}

void cmd_time() {
    char buffer[64];
    print("=== HEURE / DATE ===\n");

    unsigned char h = bcd_to_dec(rtc_read(0x04)); // heures
    unsigned char m = bcd_to_dec(rtc_read(0x02)); // minutes
    unsigned char s = bcd_to_dec(rtc_read(0x00)); // secondes

    unsigned char day   = bcd_to_dec(rtc_read(0x07)); // jour
    unsigned char month = bcd_to_dec(rtc_read(0x08)); // mois
    unsigned char year  = bcd_to_dec(rtc_read(0x09)); // année

    print("Heure : ");
    int_to_str(h, buffer); print(buffer); print(":");
    int_to_str(m, buffer); print(buffer); print(":");
    int_to_str(s, buffer); print(buffer); print("\n");

    print("Date  : ");
    int_to_str(day, buffer); print(buffer); print("/");
    int_to_str(month, buffer); print(buffer); print("/");
    int_to_str(year, buffer); print(buffer); print("\n");
}