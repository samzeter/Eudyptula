# Task 2

Now that you have written your first kernel module, it's time to take
off the training wheels and move on to building a custom kernel.  No
more distro kernels for you, for this task you must run your own kernel.
And use git!  Exciting isn't it!  No, oh, ok...

The tasks for this round is:
  - download Linus's latest git tree from git.kernel.org (you have to
    figure out which one is his, it's not that hard, just remember what
    his last name is and you should be fine.)
  - build it, install it, and boot it.  You can use whatever kernel
    configuration options you wish to use, but you must enable
    CONFIG_LOCALVERSION_AUTO=y.
  - show proof of booting this kernel.  Bonus points for you if you do
    it on a "real" machine, and not a virtual machine (virtual machines
    are acceptable, but come on, real kernel developers don't mess
    around with virtual machines, they are too slow.  Oh yeah, we aren't
    real kernel developers just yet.  Well, I'm not anyway, I'm just a
    script...)  Again, proof of running this kernel is up to you, I'm
    sure you can do well.

Hint, you should look into the 'make localmodconfig' option, and base
your kernel configuration on a working distro kernel configuration.
Don't sit there and answer all 1625 different kernel configuration
options by hand, even I, a foolish script, know better than to do that!

After doing this, don't throw away that kernel and git tree and
configuration file.  You'll be using it for later tasks, a working
kernel configuration file is a precious thing, all kernel developers
have one they have grown and tended to over the years.  This is the
start of a long journey with yours, don't discard it like was a broken
umbrella, it deserves better than that.

## How to compile and install the kernel in Fedora

N.B. `make help` has a good list of options.

1. Clean the repo:

	`make mrproper`

2. Use the current system's configuration as it'll probably work:

	`cp /boot/config-$version $location_of_kernel_source_tree/.config` 

3. Use the old .config and set all default values to the new options:

	`make olddefconfig`

	(`make oldconfig` does the same but makes you set the options).

4. Disable all modules not currently loaded on your machine: 

	`make localmodconfig`

5. `make menuconfig` 

	then and go to "Load an alternate configuration file" and use the .config in your source repo. Make any final adjustments here.

6. `$EDITOR Makefile` Change the EXTRAVERSION line to add something on the end. For example, if it reads "EXTRAVERSION = -rc5" change it to "EXTRAVERSION = -rc5-dave" (what you choose is only relevant when cleaning up the kernel install later) 

7. `make -j$(nproc) bzImage`

8. `make modules_install`

9. `make install`

10. Reboot


## Cleaning up (this is why the extra version info is handy)

`rm -f /boot/config-2.6.*dave* /boot/initrd-2.6.*dave* /boot/vmlinuz-*dave* /boot/System.map-*dave* /boot/loader/entries/*dave*`

`rm -rf /lib/modules/2.6*dave*`

Finally, you will need to remove the kernel as an option to your bootloader. This will change from architecture to architecture. For x86, (as root), edit /boot/grub2/grub.cfg or /boot/efi/EFI/fedora/grub.cfg if you have EFI enabled and delete the four lines relating to your kernel (They should be easy to spot, they'll be the ones with your tag). They'll look something like this..

	title Fedora Core (2.6.22-rc3-dave)
	root (hd0,0)
	kernel /vmlinuz-2.6.22-rc3-dave ro root=/dev/md0
	initrd /initrd-2.6.22-rc3-dave.img


## Extra steps:

This will show what's in the initramfs:

	sudo lsinitrd /boot/initramfs-``make kernelrelease``.img

