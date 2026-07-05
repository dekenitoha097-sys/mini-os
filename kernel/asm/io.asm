global outb
global inb

section .text

; void outb(uint16_t port, uint8_t value);
outb:
    mov dx, [esp + 4]     ; port
    mov al, [esp + 8]     ; valeur
    out dx, al
    ret

; uint8_t inb(uint16_t port);
inb:
    mov dx, [esp + 4]     ; port
    xor eax, eax
    in al, dx
    ret