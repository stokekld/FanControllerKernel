#include <linux/sysfs.h>
#include <linux/kobject.h>
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

// Funcion para agregar al archivo
static ssize_t temp_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	int ret;

	ret = kstrtoint(buf, 10, &temp);
	if (ret < 0)
		return ret;

	return count;
}

// Propiedades del archivo
static struct kobj_attribute temp_attribute =
	__ATTR(temp, 0664, temp_show, temp_store);


int crea_arbol_sysfs()
{
	int retval;

	// Creando kset para FanController en /sys/fan_controller
	fc_kset = kset_create_and_add("fan_controller", NULL, NULL);
	if (!fc_kset)
		return -ENOMEM;

	// Creando kobject dentro de kset
	sensor_kobj = kobject_create_and_add("sensor", &fc_kset->kobj);
	if (!sensor_kobj)
		return -ENOMEM;

	// Creando archivo dentro de kobject
	retval = sysfs_create_file(sensor_kobj, &temp_attribute.attr);
	if (retval)
		kobject_put(sensor_kobj);

	return 0;
}

int destruye_arbol_sysfs()
{
	// Destruyendo kobject
	kobject_put(sensor_kobj);
	// Destruyendo kset
	kset_unregister(fc_kset);

	return 0;
}