obj-m := q1.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -o write write.c
	gcc -o read read.c
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
	rm -rf write
	rm -rf read
