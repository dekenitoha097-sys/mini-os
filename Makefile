all: os.iso

kernel.bin:
	nasm -f elf32 boot/multiboot.asm -o multiboot.o
	gcc -m32 -ffreestanding -I kernel/include -c kernel/kernel.c -o kernel.o
	ld -m elf_i386 -T linker.ld -o kernel.bin multiboot.o kernel.o

os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

run: os.iso
	qemu-system-x86_64 -cdrom os.iso

clean:
	rm -rf *.o *.bin *.iso iso
