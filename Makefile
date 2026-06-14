CC = gcc
CFLAGS = -m32 -ffreestanding -I kernel/include
LDFLAGS = -m elf_i386 -T linker.ld

# Tous les fichiers C du noyau
C_SOURCES := $(wildcard kernel/src/*.c)

# Les fichiers .o correspondants
OBJECTS := $(patsubst kernel/src/%.c,%.o,$(C_SOURCES))

all: os.iso

# Compilation automatique des .c en .o
%.o: kernel/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation du bootloader
multiboot.o: boot/multiboot.asm
	nasm -f elf32 boot/multiboot.asm -o multiboot.o

# Édition de liens
kernel.bin: multiboot.o $(OBJECTS)
	ld $(LDFLAGS) -o kernel.bin multiboot.o $(OBJECTS)

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