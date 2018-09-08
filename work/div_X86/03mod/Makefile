#Makefile
obj-m:= char01.o
KERNEL:=/usr/src/kernels/2.6.32-358.el6.x86_64/

all:
	make -C $(KERNEL) M=`pwd` modules
install:
	make -C $(KERNEL) M=`pwd` modules_install
	depmod -A
	
clean:
	make -C $(KERNEL) M=`pwd` clean
