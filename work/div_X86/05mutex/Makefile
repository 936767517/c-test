# Makefile for external module
obj-m := mutex_test01.o
KERNEL := /lib/modules/`uname -r`/build

all:
	make -C $(KERNEL) M=`pwd` modules
clean:
	make -C $(KERNEL) M=`pwd` clean

