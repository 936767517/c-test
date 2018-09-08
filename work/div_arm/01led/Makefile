# 外部模块的Makefile
# Author: zht
# Date: 2015-08-24
obj-m := led_test05.o
KERNEL := /root/Desktop/kernel4412/kernel/linux35_tiny4412/
all:
	make -C $(KERNEL) M=`pwd` modules
install:
	adb remount
	adb push led_test05.ko /system/lib/modules/
install-elf:
	adb remount
	arm-linux-gcc -static -o timer01 timer01.c
	adb push timer01 /system/bin/
clean:
	make -C $(KERNEL) M=`pwd` clean

