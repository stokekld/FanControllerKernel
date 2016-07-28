#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include "sysfs.h"


// kset
static struct kset *fc_kset;

// kobject
static struct kobject *sensor_kobj;

// Archivo dentro de kobject
static int temp;

// Funcion para leer del archivo
static ssize_t temp_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%d\n", temp);
}

// Propiedades del archivo
static struct kobj_attribute temp_attribute =
	__ATTR(temp, 0444, temp_show, NULL);


int crea_arbol_sysfs()
{
	int retval;

	// Creando kset para FanController en /sys/fan_controller
	fc_kset = kset_create_and_add("fan_controller", NULL, NULL);
	if (!fc_kset)
	{
		printk(KERN_INFO "FanCtlModule: Kset no creado\n");
		return 0;
	}

	// Creando kobject dentro de kset
	sensor_kobj = kobject_create_and_add("sensor", &fc_kset->kobj);
	if (!sensor_kobj)
	{
		printk(KERN_INFO "FanCtlModule: Kobject no creado\n");
		return 0;
	}

	// Creando archivo dentro de kobject
	retval = sysfs_create_file(sensor_kobj, &temp_attribute.attr);
	if (retval)
	{
		printk(KERN_INFO "FanCtlModule: Archivo sensor no creado\n");
		kobject_put(sensor_kobj);
		return 0;
	}

	printk(KERN_INFO "FanCtlModule: Arbol sysfs creado\n");

	return 1;
}

int destruye_arbol_sysfs()
{
	// Destruyendo kobject
	kobject_put(sensor_kobj);
	// Destruyendo kset
	kset_unregister(fc_kset);

	return 1;
}


int actualizando_archivo_temp(int temperatura)
{
	// Actualiza el dato del archivo temp
	temp = temperatura;

	return 1;
}