# obj-m means module object as opposed to obj-y for builtin object
obj-m += hello.o

all:
#if LINUXSRC  environment variable is set, use that kernel tree
#otherwise build using the system's kernel.
ifeq ($(LINUXSRC),)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
else
	make -C $(LINUXSRC) SUBDIRS=$PWD modules
endif

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	# minus sign means to ignore the error if it's not loaded
	-sudo rmmod hello
	# Clear the kernel log without echo
	sudo dmesg -C
	#Insert the module
	sudo insmod hello.ko
	#Display the kernel log
	dmesg
	sudo rmmod hello
	dmesg
