#include <linux/thermal.h>

#include "thermal_zone.h"

// Estructura del thermal zone que se usara en el modulo
struct thermal_zone_device *fcm_tz;

// Lista enlazada que exporte en el archivo drivers/thermal/thermal_core.c
extern struct list_head thermal_tz_list;

int obtiene_thermal_zone()
{
	//struct thermal_zone_device *pos = NULL;
	/*
	// recorriendo la lista para sacar el primer elemento
	list_for_each_entry(pos, &thermal_tz_list, node)
	{
		fcm_tz = pos;
		break;
	}
	*/
	// Si no se encontro el thermal zone
	fcm_tz=thermal_zone_get_zone_by_name ("imx_thermal_zone");
	if (IS_ERR(fcm_tz))
	{		
		printk(KERN_INFO "FanCtlModule: No se encontro una thermal_zone\n");
		return 0;
	}

	printk(KERN_INFO "FanCtlModule: Thermal_zone encontrada, %s\n", fcm_tz->type);

	return 1;

}

int obtiene_temp()
{
	int temp = 0;

	if (!IS_ERR(fcm_tz))
	{
		thermal_zone_get_temp(fcm_tz, &temp);
	}

	return temp;
}
