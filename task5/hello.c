#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>
MODULE_AUTHOR("Samuel Zeter");
MODULE_LICENSE("GPL");

static int my_probe(struct usb_interface *usb_interface, const struct usb_device_id *id)
{
	pr_debug("hello my probe is here\n");
	dev_info(&usb_interface->dev, " In %s: Vendor ID:%02x\t"
		"Product ID:%02x\n", __func__, id->idVendor, id->idProduct);
	return -ENODEV; /* Don't manage the device */
}

static void cleanup_my_module(struct usb_interface *intf)
{
	pr_debug("Disconected USB\n");
}

static const struct usb_device_id device_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
				USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{ }						/* Terminating entry */
};


static struct usb_driver hello_driver = {
	.name =     "Hello USB",
	.probe =    my_probe,
	.disconnect =   cleanup_my_module,
	.id_table = device_table
};
MODULE_DEVICE_TABLE(usb, device_table);
module_usb_driver(hello_driver);
