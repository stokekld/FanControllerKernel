#include <linux/thermal.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "sysfs.h"

struct thermal_zone_device *pos = NULL, *tz;
extern struct list_head thermal_tz_list;

// Inicio del modulo
int fan_init(void)
{
	int temp;

	printk(KERN_INFO "FanCtlModule: Se cargo el modulo\n");

	crea_arbol_sysfs();

	list_for_each_entry(pos, &thermal_tz_list, node)
	{
		tz = pos;
		break;
	}

	thermal_zone_get_temp(tz, &temp);

	printk(KERN_INFO "FanCtlModule: name = %s\n", tz->type);
	printk(KERN_INFO "FanCtlModule: temp = %d\n", temp);

	return 0;
}

// Salida del modulo
void fan_cleanup(void)
{
	destruye_arbol_sysfs();
	
    printk(KERN_INFO "FanCtlModule: Se libero el modulo\n");
}

// Especificando las funciones de inicio y fin del modulo
module_init(fan_init);
module_exit(fan_cleanup);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Carlos Acosta,Jesus Flores,Roberto Guerrero <joy_warmgun@hotmail.com>");
