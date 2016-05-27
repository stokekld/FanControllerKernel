#include <linux/thermal.h>

#include "thermal_zone.h"

struct thermal_zone_device *fcm_tz;
extern struct list_head thermal_tz_list;

int obtiene_thermal_zone()
{
	struct thermal_zone_device *pos = NULL;

	list_for_each_entry(pos, &thermal_tz_list, node)
	{
		fcm_tz = pos;
		break;
	}

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
		thermal_zone_get_temp(fcm_tz, &temp);

	return temp;
}
