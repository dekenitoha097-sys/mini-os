CC = gcc
AS = nasm

CFLAGS = -m32 -ffreestanding -I kernel/include
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# Tous les fichiers C et ASM
C_SOURCES := $(wildcard kernel/src/*.c)
ASM_SOURCES := $(wildcard kernel/asm/*.asm)

# Objets générés
C_OBJECTS := $(patsubst kernel/src/%.c,%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst kernel/asm/%.asm,%.o,$(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

all: os.iso

# Compilation des fichiers C
%.o: kernel/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers ASM du kernel
%.o: kernel/asm/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Compilation du bootloader
multiboot.o: boot/multiboot.asm
	$(AS) $(ASFLAGS) $< -o $@

# Édition de liens
kernel.bin: multiboot.o $(OBJECTS)
	ld $(LDFLAGS) -o $@ multiboot.o $(OBJECTS)

# Création de l'ISO
os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

# Lancement dans QEMU
run: os.iso
	qemu-system-x86_64 -cdrom os.iso

# Nettoyage
clean:
	rm -f *.o *.bin *.iso
	rm -rf iso