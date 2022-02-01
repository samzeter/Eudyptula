This is Task 05 of the Eudyptula Challenge
------------------------------------------

Yeah, you survived the coding style mess!  Now, on to some "real"
things, as I know you are getting bored by these so far.

So, simple task this time around:
  - take the kernel module you wrote for task 01, and modify it so that
    when a USB keyboard is plugged in, the module will be automatically
    loaded by the correct userspace hotplug tools (which are implemented
    by depmod / kmod / udev / mdev / systemd, depending on what distro
    you are using.)

Yes, so simple, and yet, it's a bit tricky.  As a hint, go read chapter
14 of the book, "Linux Device Drivers, 3rd edition."  Don't worry, it's
free, and online, no need to go buy anything.



# Notes

## tldr; How the patch works

A netlink socket connects the kernel to udev when USB insertion takes place, and it's udev that fishes for info about what modules to load.

The macro `MODULE_DEVICE_TABLE` does some magic (sets info on what device or device types it supports), which eventuates in an alias being made in the file: `/lib/modules/``uname -r``/modules.alias`.

Whenever you run `depmod -a` the modules.alias file is updated. It's depmod that reads the modules in the kernel, and updates this table.

Finally, the modules are loaded by a udev rule:

`DRIVER!="?*", ENV{MODALIAS}=="?*", RUN{builtin}="kmod load $env{MODALIAS}"`

Which means udev runs that code which parses the modules.alias file, and loads the corresponding module based on the newly inserted driver's information (based on MODULE_DEVICE_TABLE).


## Commands when working with modules 

To load a built module: 

`insmod modulename.ko`

Then:

`depmod -a` # update modules

To see module info:

`modinfo moduleName.ko`

To unload a module:

`rmmod moduleName.ko`


## Commands when working with USB devices:

Check inserted USB info:

`lsusb`

`Bus 002 Device 003: ID 0e0f:0002 VMware, Inc. Virtual USB Hub` (From VM Fusion) where 0e0f:0002 is vendorId:productId.

`sudo lsusb -t`

`/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=uhci_hcd/2p, 12M
    |__ Port 1: Dev 2, If 0, Class=Human Interface Device, Driver=usbhid, 12M
    |__ Port 2: Dev 3, If 0, Class=Hub, Driver=hub/7p, 12M
        |__ Port 1: Dev 4, If 0, Class=Wireless, Driver=btusb, 12M
        |__ Port 1: Dev 4, If 1, Class=Wireless, Driver=btusb, 12M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/6p, 480M`

On my Mac `Bus 002 Device 011: ID 0c45:652f Sonix Technology Co., Ltd. USB DEVICE`

`lsusb -v`

    MaxPower                0mA
    Interface Descriptor:
      bLength                 9
      bDescriptorType         4
      bInterfaceNumber        0
      bAlternateSetting       0
      bNumEndpoints           1
      bInterfaceClass         3 Human Interface Device
      bInterfaceSubClass      1 Boot Interface Subclass
      bInterfaceProtocol      2 Mouse
      iInterface              1 VMware


## Emacs configuration for kernel navigation

### Kernel
So, just go to the directory where the kernel source code is:

	$ cd /path/to/linux/source/code

and to create the cscope database execute:

	$ make cscope

and to create the etags database

	$ make TAGS

Use cscope and etags from Emacs

Once the databases are created, to use it from Emacs just open a source file that is inside the kernel source directory (whose symbols are already in the databases).

To use cscope, you have to add this line to your ~/.emacs config file

	(require 'xcscope)

Then to navigate trough the symbols just put your cursor over a symbol and use one of these commands:

	C-c s s Find symbol.
	C-c s d Find global definition.
	C-c s g Find global definition (alternate binding).
	C-c s G Find global definition without prompting.
	C-c s c Find functions calling a function.
	C-c s C Find called functions (list functions called from a function).
	C-c s t Find text string.
	C-c s e Find egrep pattern.
	C-c s f Find a file.
	C-c s i Find files #including a file.

For a complete list of commands refer to the file: xcscope.el.

To use the etags database, first you have to tell emacs where the symbol database is, for example:

	M-x visit-tag-table /path/to/linux/source/code/TAGS

to navigate, go to a function an do:

	M-.

to go back

	M-*

### Other projects

To manually create the index for cscope, first you have to list all the files that have symbols that you want to add to the index, you can do this using the find or whatever command line utility is best for you:

	$ find . -name "*.c" -o -name "*.h" > cscope.files

then to build the database:

	$ cscope -qkRv

and finally to browse the database:

	$ cscope -d

A similar procedure is needed to build the database for etags:

	$ etags `find . -name "*.c" -o -name "*.h"`



## Good links

[Interface classes, subclasses and protocols are defined here](https://www.usb.org/sites/default/files/hid1_11.pdf)

[A very thorough write up for task 5](https://sebastianfricke.me/eudyptula-challenge-Part-5/)

[A deeper dive into modalias](http://people.skolelinux.org/pere/blog/Modalias_strings___a_practical_way_to_map__stuff__to_hardware.html)
