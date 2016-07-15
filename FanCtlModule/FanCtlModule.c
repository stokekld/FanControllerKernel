#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static struct kset *fc_kset;

// Inicio del modulo
int fan_init(void)
{

	printk(KERN_INFO "FanCtlModule: Se cargo el modulo\n");

	// Creando kset para FanController en /sys/fan_controller
	fc_kset = kset_create_and_add("fan_controller", NULL, NULL);
	if (!fc_kset)
		return -ENOMEM;

	return 0;
}

// Salida del modulo
void fan_cleanup(void)
{
	// Destruyendo kset
	kset_unregister(fc_kset);

    printk(KERN_INFO "FanCtlModule: Se libero el modulo\n");
}

// Especificando las funciones de inicio y fin del modulo
module_init(fan_init);
module_exit(fan_cleanup);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Carlos Acosta,Jesus Flores,Roberto Guerrero <joy_warmgun@hotmail.com>");