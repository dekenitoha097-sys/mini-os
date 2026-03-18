// Lit un octet (byte) depuis un port matériel
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    // Instruction assembleur 'inb'
    __asm__ __volatile__("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Écrit un octet (byte) vers un port matériel
static inline void outb(unsigned short port, unsigned char data) {
    // Instruction assembleur 'outb'
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}
