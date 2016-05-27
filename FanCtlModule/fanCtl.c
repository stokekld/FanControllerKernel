#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "sysfs.h"
#include "thermal_zone.h"

// Inicio del modulo
int fan_init(void)
{

	printk(KERN_INFO "FanCtlModule: Se cargo el modulo\n");

	crea_arbol_sysfs();
	obtiene_thermal_zone();

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
