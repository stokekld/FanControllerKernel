#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/thermal.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


struct thermal_zone_device *pos = NULL, *tz;
extern struct list_head thermal_tz_list;

// kset
static struct kset *fc_kset;

// kobject
static struct kobject *thermal_kobj;

// Archivo dentro de kobject
static int zone0;

// Funcion para leer del archivo
static ssize_t zone0_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%d\n", zone0);
}

// Funcion para agregar al archivo
static ssize_t zone0_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	int ret;

	ret = kstrtoint(buf, 10, &zone0);
	if (ret < 0)
		return ret;

	return count;
}

// Propiedades del archivo
static struct kobj_attribute zone0_attribute =
	__ATTR(zone0, 0664, zone0_show, zone0_store);


// Inicio del modulo
int fan_init(void)
{
	int retval, temp;
	//struct thermal_zone_device *pos = NULL;

	printk(KERN_INFO "FanCtlModule: Se cargo el modulo\n");

	// Creando kset para FanController en /sys/fan_controller
	fc_kset = kset_create_and_add("fan_controller", NULL, NULL);
	if (!fc_kset)
		return -ENOMEM;

	// Creando kobject dentro de kset
	thermal_kobj = kobject_create_and_add("thermal", &fc_kset->kobj);
	if (!thermal_kobj)
		return -ENOMEM;

	// Creando archivo dentro de kobject
	retval = sysfs_create_file(thermal_kobj, &zone0_attribute.attr);
	if (retval)
		kobject_put(thermal_kobj);

	list_for_each_entry(pos, &thermal_tz_list, node)
	{
		tz = pos;
		break;
	}

	thermal_zone_get_temp(tz, &temp);

	//printk(KERN_INFO "FanCtlModule: Hay un error\n");
	printk(KERN_INFO "FanCtlModule: name = %s\n", tz->type);
	printk(KERN_INFO "FanCtlModule: temp = %d\n", temp);

	return 0;
}

// Salida del modulo
void fan_cleanup(void)
{
	// Destruyendo kobject
	kobject_put(thermal_kobj);
	// Destruyendo kset
	kset_unregister(fc_kset);

    printk(KERN_INFO "FanCtlModule: Se libero el modulo\n");
}

// Especificando las funciones de inicio y fin del modulo
module_init(fan_init);
module_exit(fan_cleanup);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Carlos Acosta,Jesus Flores,Roberto Guerrero <joy_warmgun@hotmail.com>");
