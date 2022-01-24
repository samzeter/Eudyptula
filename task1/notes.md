# Task 1

## Instructions
Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

The Makefile should build the kernel module against the source for the
currently running kernel, or, use an environment variable to specify
what kernel tree to build it against.

Please show proof of this module being built, and running, in your
kernel.  What this proof is is up to you, I'm sure you can come up with
something.  Also be sure to send the kernel module you wrote, along with
the Makefile you created to build the module.

## Notes

### Using current systems config for kernel build

For Fedora 35:
An exploded source tree is not required to build a kernel module, such as your own device driver,
against the currently in-use kernel. Only the kernel-devel package is required to build external modules :
`sudo dnf install kernel-devel-$(uname -r)`

For example, to build the foo.ko module, create the following Makefile in the directory containing the foo.c file:
    obj-m := foo.o 

    KDIR  := /lib/modules/$(shell uname -r)/build
    PWD   := $(shell pwd)
    
    default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
Issue the make command to build the foo.ko module.

####

Building the kernel tree out of system

Clone kernel git

`cp /boot/config-5.14.10-300.fc35.x86_64 ~/dev/tip/.config`

In kernel root dir accept all defaults:
`yes "" | make oldconfig`

Then issue `make`
