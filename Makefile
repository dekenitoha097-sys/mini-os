all: os.iso

# Compilation
kernel.o: kernel/src/kernel.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/kernel.c -o kernel.o

screen.o: kernel/src/screen.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/screen.c -o screen.o

kbd.o: kernel/src/kbd.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/kbd.c -o kbd.o

shell.o: kernel/src/shell.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/shell.c -o shell.o

time_date.o: kernel/src/time_date.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/time_date.c -o time_date.o

str.o: kernel/src/str.c
	gcc -m32 -ffreestanding -I kernel/include -c kernel/src/str.c -o str.o


# Boot
multiboot.o:
	nasm -f elf32 boot/multiboot.asm -o multiboot.o

# Link
kernel.bin: multiboot.o kernel.o screen.o kbd.o shell.o time_date.o str.o
	ld -m elf_i386 -T linker.ld -o kernel.bin multiboot.o kernel.o screen.o kbd.o shell.o time_date.o str.o

# ISO
os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

# Run
run: os.iso
	qemu-system-x86_64 -cdrom os.iso

# Clean
clean:
	rm -rf *.o *.bin *.iso iso