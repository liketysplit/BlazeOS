C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 


CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

CFLAGS = -g -ffreestanding -Wall -Wextra -fno-exceptions -m32


blaze-os.bin: boot/bootsect.bin kernel.bin
	cat $^ > blaze-os.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: blaze-os.bin
	qemu-system-i386 -m 1G -fda blaze-os.bin

debug: blaze-os.bin kernel.elf
	qemu-system-i386 -s -fda blaze-os.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o blaze-os.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o libc/*.o
